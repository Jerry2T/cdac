def min_product(nums):
    if not nums:
        return 0
    
    curr_max = curr_min = result = nums[0]
    
    for num in nums[1:]:
        # When multiplied by a negative number,
        # max becomes min and min becomes max.
        if num < 0:
            curr_max, curr_min = curr_min, curr_max
        
        curr_max = max(num, curr_max * num)
        curr_min = min(num, curr_min * num)
        
        result = min(result, curr_min)
    
    return result

if __name__ == '__main__':
    # Example usage:
    example_nums = [2, 3, -2, 4]
    print("The minimum product of contiguous subarray is:", min_product(example_nums))