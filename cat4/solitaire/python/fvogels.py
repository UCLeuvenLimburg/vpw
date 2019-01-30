from itertools import chain
from math import inf, isinf
from sys import stdin

cache = {}


def compute(bs):
    if sum(bs) == 1:
        return bs.index(1)
    else:
        result = inf
        left = ((i, -1) for i in range(2, len(bs)) if bs[i-2:i+1] == [0, 1, 1])
        right = ((i, 1) for i in range(0, len(bs)-2) if bs[i:i+3] == [1, 1, 0])

        for (i, di) in chain(left, right):
            bs[i] = 0
            bs[i + di] = 0
            bs[i + 2 * di] = 1
            result = min(result, solve(bs))
            bs[i] = 1
            bs[i + di] = 1
            bs[i + 2 * di] = 0

        return result


def solve(bs):
    t = tuple(bs)

    if t in cache:
        return cache[t]
    else:
        r = compute(bs)
        cache[t] = r
        return r


n = int(stdin.readline())

for index in range(1, n+1):
    bs = [ int(x) for x in stdin.readline().strip().split(' ')[1:] ]
    solution = solve(bs)

    if isinf(solution):
        print(f'{index} ONMOGELIJK')
    else:
        print(f'{index} {solution + 1}')
