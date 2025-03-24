def smart_duplicate_search(array):
    dictionary = dict()
    if len(array)<2:
        return False
    else:
        for i in range(len(array)):
            if array[i] in dictionary:
                return True
            else:
                dictionary[array[i]] = True
    return False

array= [1,2,46,32,98,61,34,46]

print(smart_duplicate_search(array))