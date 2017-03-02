from array import array

def solve(ns):    
    leftmost = float('Inf')
    length = len(ns)
    indices = list(range(length))
    visited = set()

    def jump_left(n, i):
        if i > 1 and ns[i] and ns[i-1] and not ns[i-2]:
            ns[i] = False
            ns[i-1] = False
            ns[i-2] = True
            jump(n - 1)
            ns[i] = True
            ns[i-1] = True
            ns[i-2] = False

    def jump_right(n, i):
        if i + 2 < length and ns[i] and ns[i+1] and not ns[i+2]:
            ns[i] = False
            ns[i+1] = False
            ns[i+2] = True
            jump(n - 1)
            ns[i] = True
            ns[i+1] = True
            ns[i+2] = False
    
    def jump(n):
        nonlocal leftmost
        nonlocal visited

        t = tuple(ns)

        if t not in visited:
            visited.add(t)
            
            if n > 1:
                for i in indices:
                    jump_left(n, i)
                    jump_right(n, i)

            else:
                leftmost = min(leftmost, next(i for i in range(length) if ns[i]))

                if leftmost == 0:
                    raise RuntimeError()
    
    n = len([ 1 for n in ns if n ])    
            
    try:
        jump(n)
    except RuntimeError:
        pass
    
    return leftmost


def main():
    n = int(input())

    for index in range(1, n + 1):
        ns = [ n == '1' for n in input().split(' ')[1:] ]
        result = solve(ns)

        if result == float('inf'):
            result = 'ONMOGELIJK'
        else:
            result += 1

        print("{} {}".format(index, result))

if __name__ == '__main__':
    main()


