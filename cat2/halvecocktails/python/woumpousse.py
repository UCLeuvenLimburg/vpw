def time(order):
    T1 = 0
    T2 = 0

    for t1, t2 in order:
        T1 = T1 + t1
        T2 = max(T1, T2) + t2
    
    return T2

def solve(pairs):
    first = sorted([ (t1, t2) for t1, t2 in pairs if t1 <= t2 ], key = lambda x: x[0])
    second = sorted([ (t1, t2) for t1, t2 in pairs if t1 > t2 ], key = lambda x: x[1], reverse=True)

    return time(first + second)

n = int(input())

for index in range(n):
    n = int(input())
    recipes = {}

    for _ in range(n):
        id, t1, t2 = input().split(' ')
        recipes[id] = (int(t1), int(t2))

    input()
    order = [ recipes[id] for id in input() ]
    solution = solve(order)

    print(f"{index+1} {solution}")
