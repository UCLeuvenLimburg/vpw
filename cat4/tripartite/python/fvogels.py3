from sys import stdin


n = int(stdin.readline())



for index in range(1, n + 1):
    n = int(stdin.readline())
    cs = [ 0 ]

    for _ in range(n):
        cs.append(cs[-1] + int(stdin.readline()))

    solution = 0
    acc = 0

    if cs[-1] % 3 == 0:
        a = cs[-1] // 3
        b = a * 2

        for c in cs:
            if c == a:
                acc += 1

            if c == b:
                solution += acc

    print(f"{index} {solution}")
