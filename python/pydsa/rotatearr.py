def reverse(array, start, end): #Function to reverse the elements of array from index start to index end
    while start<end:
        print(start, end)
        array[start], array[end] = array[end], array[start]
        start += 1
        end -= 1
    return array

def reverse_rotate(array, k):
    array = reverse(array,0,len(array)-1)
    print(array) #At this stage, the entire array would be reverse. Output : [9,8,7,6,5,4,3,2,1]
    array = reverse(array,0,k%len(array)-1)
    print(array) #By now, the first k elements would be reverse. Output : [8,9,7,6,5,4,3,2,1]
    array = reverse(array,k%len(array),len(array)-1)
    print(array) #Finally the last k%len(array) - n items would be reverse. Output: [8,9,1,2,3,4,5,6,7]
    return array

a = [1,2,3,4,5,6,7,8,9]
k=11
print(reverse_rotate(a,k))