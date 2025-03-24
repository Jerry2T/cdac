def kadane(array):
    maximum = maxarray = array[0]
    for i in range(1,len(array)):
        maxarray = max(array[i], maxarray+array[i])
        maximum = max(maxarray, maximum)
    return maximum

array = [-2,1,-3,4,-1,2,1,-5,4]
print(kadane(array))
