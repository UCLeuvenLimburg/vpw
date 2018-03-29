def repeat_yield(n, x):
    for _ in range(n):
        yield x

def infinite_repeat(x):
    while True:
        yield x

def score_generator():
    yield from repeat_yield(4, 25)
    yield from repeat_yield(4, 100)
    yield from repeat_yield(4, 500)
    yield from infinite_repeat(1000)

def take(n, generator):
    for _ in range(n):
        yield next(generator)

def score(jump):
    return sum(take(jump, score_generator()))


if __name__ == '__main__':
    n = int(input())

    for index in range(n):
        n_jumps = int(input())
        jumps = [ int(n) for n in input().split(' ') ]
        solution = sum( score(jump) for jump in jumps )

        print(f"{index + 1} {solution}")