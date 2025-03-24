def swap(string, a, b): #Function which swaps two characters of a string
    string = list(string)
    temp = string[a]
    string[a] = string[b]
    string[b] = temp
    return ''.join(string)

def smarter_reverse(string):
    for i in range(len(string)//2):
        string = swap(string, i, len(string)-i-1)
    return string

string='abhishek'
print(smarter_reverse(string))

string1 = 'abcde'
string2 = reversed(string1)
print(''.join(string2))

list1 = list(string1)
list1.reverse()
print(''.join(list1))