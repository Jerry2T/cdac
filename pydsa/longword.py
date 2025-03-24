import re

def regex(string):
    string = re.findall('\w+', string)
    maximum = max([len(item) for item in string])
    for item in string:
        if len(item) == maximum:
            return item
        
sss = "Hello there how are you kittycat"
print(regex(sss))