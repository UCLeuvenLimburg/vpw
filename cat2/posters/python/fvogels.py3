from sys import stdin


n = int(stdin.readline())

for _ in range(1, n+1):
    n = int(stdin.readline())

    posters = [ tuple( int(x) for x in stdin.readline().strip().split(' ') ) for _ in range(n) ]
    rightmost = max(x + size for x, size in posters)
    wall = [None] * (rightmost + 1)

    for (i, (left, size)) in enumerate(posters):
        for j in range(left, left + size):
            wall[j] = i

    solution = len(set(wall)) - 1

    print(f"{solution}")
