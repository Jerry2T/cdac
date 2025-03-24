def swap_move(array):
    z = 0
    for i in range(len(array)):
        if array[i] != 0:
            array[i], array[z] = array[z], array[i]
            z += 1
    return array

def one_liner_move(array):
    array.sort(key=bool, reverse=False) # True for end
    return array

array = [0,0,0,0,1,0,3,0,0,0,12,9,7]
print(swap_move(array))
print(one_liner_move(array))