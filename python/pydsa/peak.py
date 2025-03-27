def find_peak(nums):
    if not nums:
        return None
    
    left, right = 0, len(nums) - 1
    while left < right:
        mid = (left + right) // 2
        if nums[mid] < nums[mid + 1]:
            left = mid + 1
        else:
            right = mid
    return left

if __name__ == '__main__':
    # Example usage:
    example_nums = [1, 3, 20, 4, 1, 0]
    peak_index = find_peak(example_nums)
    print("Peak element is:", example_nums[peak_index], "at index", peak_index)