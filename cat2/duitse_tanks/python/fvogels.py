def next():
    return int(input())


def read_numbers():
    ns = []
    n = next()

    while n >= 0:
        ns.append(n)
        n = next()

    return ns


def solve(index):
    ns = read_numbers()
    m = max(ns)
    n = len(ns)
    t = round(((n + 1) * m) / n + 0.001) - 1
    print(f"{index} {t}")


n = next()
for index in range(0, n):
    solve(index + 1)
