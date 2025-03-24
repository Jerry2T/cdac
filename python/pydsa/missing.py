def find(arr):
    n = len(arr)
    index = 0
    for i in range(n):
        index = abs(arr[i]) - 1
        arr[index] = -(abs(arr[index]))
    return [i+1 for i in range(len(arr)) if arr[i] > 0]

if __name__ == "__main__":
    arr = [0,1,2,3,5,6]
    missing_numbers = find(arr)
    print("Missing numbers:", missing_numbers)