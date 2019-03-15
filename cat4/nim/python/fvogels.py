from sys import stdin, argv

# Probably requires XOR trick
# This implementation leads to a stack overlow due do the large number of possibilities

def is_odd(n):
    return n % 2 == 1

def is_even(n):
    return n % 2 == 0

def canonical(ns):
    return sorted(n for n in ns if n > 0)

def successors(ns):
    def aux(i, remove):
        copy = ns[:]
        copy[i] -= remove
        return copy

    return [ aux(i, j) for i in range(len(ns)) for j in range(1, ns[i]+1) ]

def all_equal(ns):
    return not ns or all(ns[0] == n  for n in ns)

class Node:
    def __init__(self, value, children):
        self.value = value
        self.children = children

    def __str__(self):
        return f'({self.value}:{self.children})'

    def __repr__(self):
        return str(self)


cache = Node(None, [])

def fetch(ns):
    current = cache
    last = 0
    for n in ns:
        delta = n - last
        while delta >= len(current.children):
            current.children.append(Node(None, []))
        current = current.children[delta]
        last = n
    return current

fetch([]).value = True

for n in range(2, 20):
    for x in range(2, 1000):
        fetch([x] * n).value = is_odd(n)

def losing(ns):
    global cache
    ns = canonical(ns)
    node = fetch(ns)

    if node.value == None:
        node.value = not all( winning(s) for s in successors(ns) )

    return not node.value

def winning(ns):
    global cache
    ns = canonical(ns)
    node = fetch(ns)

    if node.value == None:
        node.value = any( losing(s) for s in successors(ns) )

    return node.value

def main():
    n = int(input())

    for index in range(1, n+1):
        ns = list(map(int, input().split(' ')[1:]))
        solutions = [ s for s in successors(ns) if losing(s) ]

        if solutions:
            for solution in solutions:
                print(f'{index} {" ".join(map(str, solution))}', flush=True)
        else:
            print(f'{index} HOPELOOS', flush=True)

def interactive():
    print(winning([int(x) for x in argv[1:]]))

# interactive()
main()