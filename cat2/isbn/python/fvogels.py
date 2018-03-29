def as_digits(n):
    return [ int(k) for k in n ]

def is_valid(isbn):
    weights = [1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1]
    return sum( d * w for d, w in zip(as_digits(isbn), weights) ) % 10 == 0

def corrections(isbn):
    for i in range(0, 14):
        for k in range(0, 10):
            correction = isbn[:i] + str(k) + isbn[i:]
            if is_valid(correction):
                yield correction

def solve(isbn):
    return sum(int(x) for x in set(corrections(isbn)))

n = int(input())

for index in range(n):
    isbn = input()
    solution = solve(isbn)

    print("{} {}".format(index + 1, solution))