class Solver:
    def __init__(self):
        self.__table = {}
        
    def solve(self, k, n):
        if k == 1:
            return n
        elif n == 0:
            return 0
        else:
            if not (k, n) in self.__table:
                self.__table[(k, n)] = min( max([self.solve(k-1, i-1), 1 + self.solve(k, n-i)]) for i in range(1, n+1) )

            return self.__table[(k, n)]


n = int(input())
solver = Solver()

for index in range(1, n+1):
    k, n = map(int, input().split(' '))
    solution = solver.solve(k, n)

    print(index, solution)
        
