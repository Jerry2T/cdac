def max_ones(arr):
    max = 0
    count = 0
    for i in arr:
        if i == 1:
            count += 1
        if count > max:
            max = count
        if i == 0:
            count = 0
    return max

if __name__ == "__main__":
    arr = [1, 1, 0, 1, 1, 1, 1, 0, 1, 1]
    print("Max consecutive ones:", max_ones(arr))