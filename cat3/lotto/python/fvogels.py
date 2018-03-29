table = { (2, True): 3,
          (3, False): 5,
          (3, True): 8,
          (4, False): 22,
          (4, True): 218,
          (5, False): 1201,
          (5, True): 35722,
          (6, False): 1000000 }


def winnings(winning, extra, picks):
    n_correct = len(winning & picks)
    has_extra = extra in picks
    pair = (n_correct, has_extra)

    if pair in table:
        return table[pair]
    else:
        return 0



n = int(input())

for index in range(1, n+1):
    ns = list(map(int, input().split()))
    winning = set(ns[:-1])
    extra = ns[-1]

    n = int(input())
    solution = sum( winnings(winning, extra, set(map(int, input().split()))) for _ in range(n) )

    print(f"{index} {solution}")
