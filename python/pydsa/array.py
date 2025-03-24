class my_array():
    def __init__(self):
        self.length = 0 
        self.data = {} 

    def __str__(self):
        print(self.data.values())
        return str(self.__dict__)

    def get(self, index):
        return self.data[index] 

    def push(self, item):
        self.length += 1
        self.data[self.length - 1] = item 

    def pop(self):
        last_item = self.data[self.length-1] 
        del self.data[self.length - 1] #Deletes the last element from the array
        self.length -= 1 #Decrements the length attribute of the array by 1
        return last_item #Returns the popped element. O(1) time

    def insert(self, index, item):
        self.length += 1
        for i in range(self.length-1, index, -1):
            self.data[i] = self.data[i-1] 
        self.data[index] = item #Adds the element at the given index. O(n) operation


    def delete(self,index):
        for i in range(index, self.length-1):
            self.data[i] = self.data[i+1]
        del self.data[self.length - 1] #The last element which remains two times in the array is deleted
        self.length -= 1 #The lenght is decremented by 1. O(n) operation

arr = my_array()
print(arr)
print("-"*100)
arr.push(6)
#{'length': 1, 'data': {0: 6}}

arr.push(2)
#{'length': 2, 'data': {0: 6, 1: 2}}

arr.push(9)
#{'length': 3, 'data': {0: 6, 1: 2, 2: 9}}

arr.pop()
#{'length': 2, 'data': {0: 6, 1: 2}}

arr.push(45)
arr.push(12)
arr.push(67)
#{'length': 5, 'data': {0: 6, 1: 2, 2: 45, 3: 12, 4: 67}}

arr.insert(3,10)
#{'length': 6, 'data': {0: 6, 1: 2, 2: 45, 3: 10, 4: 12, 5: 67}}

arr.delete(4)
#{'length': 5, 'data': {0: 6, 1: 2, 2: 45, 3: 10, 4: 67}}

print(arr.get(1))

print(arr)