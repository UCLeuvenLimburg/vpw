def solve(goal, ns):
    return any( goal == ns[i] + ns[j] for i in range(len(ns)) for j in range(len(ns)) if i != j )


n = int(input())

for index in range(1, n+1):
    input()
    ns = [ int(str) for str in input().split() ]
    goal = int(input())
    solution = 'JA' if solve(goal, ns) else 'NEEN'

    print(f"{goal} {solution}")
