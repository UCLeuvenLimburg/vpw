import cProfile
import functools


alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
inverse_alphabet = { alphabet[i] : i for i in range(len(alphabet)) }

def partition(xs, pivot, pred):
    left = []
    right = []

    for x in xs:
        if pred(x, pivot):
            left.append(x)
        else:
            right.append(x)

    return (left, right)

def quicksort(xs, pred):
    if len(xs) < 2:
        return xs
    else:
        left, right = partition(xs[1:], xs[0], pred)

        return quicksort(left, pred) + [xs[0]] + quicksort(right, pred)


class InfiniteString:
    '''
    Infinitely long string. Used to represent 'no solution possible'.
    '''
    
    def __len__(self):
        return 99999

    def __gt__(self, other):
        return True

    def __str__(self):
        return "onmogelijk"

    
def first(predicate, xs, default):
    for x in xs:
        if predicate(x):
            return x

    return default


def common_prefix_length(s1, s2):
    return first(lambda i: s1[i] != s2[i], range(0, len(s1)), len(s1))


def ndiffs(x, y):
    return sum(1 for i in range(len(x)) if x[i] != y[i])

def better(t1, t2):
    h1 = len(t1.delta) + ndiffs(t1.s1, t1.s2)
    h2 = len(t2.delta) + ndiffs(t2.s1, t2.s2)

    if h1 < h2:
        return True
    elif h1 > h2:
        return False
    else:
        return t1.delta < t2.delta

# @total_ordering
class Triplet:
    def __init__(self, s1, s2, delta):
        prefix_length = common_prefix_length(s1, s2)
        
        self.s1 = s1[prefix_length:]
        self.s2 = s2[prefix_length:]
        self.delta = delta

    def __lt__(self, other):
        return better(other, self)

    
def swap(s, i, j):
    cs = list(s)

    temp = cs[i]
    cs[i] = cs[j]
    cs[j] = temp

    return "".join(cs)


def code(i, j):
    return alphabet[i] + alphabet[j]


def shortest(strings):
    strings = strings + [ InfiniteString() ]
    smallest_length = min(len(s) for s in strings)
    smallest_strings = [ s for s in strings if len(s) == smallest_length ]
    return sorted(smallest_strings)[0]


def concat(s1, s2):
    '''String concatenation, but with support for InfiniteStrings'''
    
    if type(s1) is InfiniteString or type(s2) is InfiniteString:
        return InfiniteString()
    else:
        return s1 + s2
        

def solve(string1, string2):
    queue = [ Triplet(string1, string2, '') ]

    while queue:
        current = queue.pop()
        # print(current.delta)

        if current.s1 == '':
            return current.delta
        else:
            for i in range(1, len(current.s1)):
                s1 = swap(current.s1, 0, i)
                s2 = current.s2
                delta = current.delta + code(len(string1) - len(s1), len(string1) - len(s1) + i)
                queue.append(Triplet(s1, s2, delta))

            # print(f"queue size = {len(queue)}")
            # queue = quicksort(queue, better)
            # queue.reverse()

            queue.sort()

    return 'onmogelijk'


def counts(s):
    return ( s.count('L'), s.count('R'), s.count('S') )

def possible(s1, s2):
    (l1, r1, s1) = counts(s1)
    (l2, r2, s2) = counts(s2)

    return l1 == l2 and r1 == r2 and s1 == s2


def pairs(xs):
    return [ (xs[2*i], xs[2*i+1]) for i in range(len(xs) // 2) ]

def verify(s1, s2, delta):
    for (i, j) in [ (inverse_alphabet[x], inverse_alphabet[y]) for (x, y) in pairs(delta) ]:
        s1 = swap(s1, i, j)

    return s1 == s2


def go():
    n = int(input())

    for index in range(1, n + 1):
        s1 = input()
        s2 = input()

        if s1 == s2:
            solution = 'correct'
        elif possible(s1, s2):
            solution = solve(s1, s2)
            
            if not verify(s1, s2, solution):
                print('--> error!!!')
        else:
            solution = "onmogelijk"

        print("{} {}".format(index, solution), flush=True)


# cProfile.run('go()')

go()

# a = 'LLLSRRRRRLLRSSRLLSS'
# b = 'LLRSSRRLRLLRSRSLLSR'
# print(solve(a, b))


# print(quicksort([1,3,5,7,9,8,4,6,2], lambda x, y: x <= y))
