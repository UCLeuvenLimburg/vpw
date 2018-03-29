def pairs(xs):
    for i in range(len(xs)):
        for j in range(i + 1, len(xs)):
            yield (xs[i], xs[j])

def solve(goal, weights):
    return any(x + y == goal for x, y in pairs(weights))


n = int(input())

for index in range(n):
    input()
    weights = [ int(x) for x in input().split(' ') ]
    goal = int(input())
    
    if solve(goal, weights):
        result = "JA"
    else:
        result = "NEEN"

    print("{} {}".format(goal, result))
