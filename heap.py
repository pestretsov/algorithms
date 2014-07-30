class Heap:
    def __init__(self, arguments=None):
        self.arr = []
        self.make_heap(arguments)

    def make_heap(self, arguments):
        if arguments:
            if type(arguments) != list:
                self.arr.append(arguments)
            else:
                [self.insert(i) for i in arguments]

    def parent(self, i):
        return (i-1)//2

    def left(self, i):
        return (i*2)+1

    def right(self, i):
        return (i*2)+2

    def size(self):
        return len(self.arr)

    def min_child(self, i):
        l = self.left(i)
        r = self.right(i)
        s = self.size()-1
        if l >= s:
            return -1
        else:
            return r if (self.arr[l][1] > self.arr[r][1]) else l

    def bubble_up(self, i):
        p = self.parent(i)
        while (p >= 0) and (self.arr[i][1] < self.arr[p][1]):
            self.arr[i], self.arr[p] = self.arr[p], self.arr[i]
            i = p
            p = self.parent(i)

    def sift_down(self, i):
        t = self.min_child(i)
        while (t > -1) and (self.arr[t][1] < self.arr[i][1]):
            self.arr[i], self.arr[t] = self.arr[t], self.arr[i]
            i = t
            t = self.min_child(i)

    def insert(self, node):
        i = self.size()
        self.arr.append(node)
        self.bubble_up(i)

    def extract_min(self):
        if self.empty():
            return None
        else:
            min = self.arr[0]
            self.arr[0] = self.arr[self.size()-1]
            del self.arr[self.size()-1]
            self.sift_down(0)
            return min

    def decrease_key(self, f, t):
        i = [x[0] for x in self.arr].index(f[0])
        self.arr[i] = (f[0],t)
        self.bubble_up(i)

    def empty(self):
        return not(self.size())

    def print_heap(self):
        print(self.arr)
