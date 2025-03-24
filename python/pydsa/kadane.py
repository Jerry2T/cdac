"""
Kadane's algorithm is used to find the maximum contiguous sum in an array.
The logic is simple. Take the first element in the sum and then find current max num.
Curr max = max(arr[i], curr_max + arr[i]) - we add this number if it increases the sum,
otherwise we take the number if it is more than the sum
Then keep track of max of this value
"""

def max_sum(arr):
    max_so_far = arr[0]
    curr_max = arr[0]
    for i in range(1, len(arr)):
        curr_max = max(arr[i], curr_max + arr[i])
        max_so_far = max(max_so_far, curr_max)

    return max_so_far

if __name__ == "__main__":
    arr = [-2, -3, 4, -1, -2, 1, 5, -3]
    print(max_sum(arr))