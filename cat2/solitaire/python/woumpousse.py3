def solve(ns):
    leftmost = float('Inf')
    length = len(ns)
    indices = list(range(length))
    
    def jump(n):
        nonlocal leftmost
        if n > 1:
            for i in indices:
                if i > 1 and ns[i] and ns[i-1] and not ns[i-2]:
                    ns[i] = False
                    ns[i-1] = False
                    ns[i-2] = True
                    jump(n - 1)
                    ns[i] = True
                    ns[i-1] = True
                    ns[i-2] = False

                if i + 2 < length and ns[i] and ns[i+1] and not ns[i+2]:
                    ns[i] = False
                    ns[i+1] = False
                    ns[i+2] = True
                    jump(n - 1)
                    ns[i] = True
                    ns[i+1] = True
                    ns[i+2] = False

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

def solve2(ns):
    leftmost = float('Inf')
    length = len(ns)
    indices = list(range(length))

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


def solve3(ns):
    leftmost = float('Inf')
    length = len(ns)
    indices = list(range(length))
    
    queue = [ ns ]

    while queue:
        ns = queue[-1]
        del queue[-1]

        if sum(ns) > 1:        
            for i in indices:
                if i > 1 and ns[i] and ns[i-1] and not ns[i-2]:
                    ms = list(ns)
                    ms[i] = False
                    ms[i-1] = False
                    ms[i-2] = True
                    queue.append(ms)

                if i + 2 < length and ns[i] and ns[i+1] and not ns[i+2]:
                    ms = list(ns)
                    ms[i] = False
                    ms[i+1] = False
                    ms[i+2] = True
                    queue.append(ms)

        else:
            leftmost = min(leftmost, next(i for i in range(length) if ns[i]))

    return leftmost

def solve4(ns):
    leftmost = float('Inf')
    length = len(ns)
    indices = list(range(length))
    n_stones = len( [ 1 for n in ns if n ] )
    
    stack = [ (n_stones, 0, -1, False) ]

    while stack:
        n_stones, index, direction, done = stack[-1]

        if not done:
            if n_stones == 1:
                leftmost = min(leftmost, next(i for i in range(length) if ns[i]))
                stack.pop()

                if stack:
                    n_stones, index, direction, done = stack.pop()
                    stack.append((n_stones, index, direction, True))
                else:
                    return leftmost

            else:
                if index == length:
                    stack.pop()

                    if stack:
                        n_stones, index, direction, done = stack.pop()
                        stack.append( (n_stones, index, direction, True) )
                    else:
                        return leftmost
                        
                elif direction == -1:
                    if index >= 2 and ns[index] and ns[index-1] and not ns[index-2]:
                        ns[index] = False
                        ns[index-1] = False
                        ns[index-2] = True
                        stack.append( (n_stones - 1, 0, -1, False) )
                    else:
                        stack.pop()
                        stack.append( (n_stones, index, 1, False) )

                else:
                    if index + 2 < length and ns[index] and ns[index+1] and not ns[index+2]:
                        ns[index] = False
                        ns[index+1] = False
                        ns[index+2] = True
                        stack.append( (n_stones - 1, 0, -1, False) )
                    else:
                        stack.pop()
                        stack.append( (n_stones, index + 1, -1, False) )
        else:
            stack.pop()

            ns[index] = True
            ns[index + direction] = True
            ns[index + 2 * direction] = False
            
            if direction == -1:
                stack.append( (n_stones, index, 1, False) )
            elif index == length:
                n_stones, index, direction, done = stack.pop()
                stack.append( (n_stones, index, direction, True) )
            else:
                stack.append( (n_stones, index+1, -1, False) )


    return leftmost


def main():
    n = int(input())

    for index in range(1, 100):
        ns = [ n == '1' for n in input().split(' ')[1:] ]
        result = solve4(ns)

        if result == float('inf'):
            result = 'ONMOGELIJK'
        else:
            result += 1

        print("{} {}".format(index, result))

if __name__ == '__main__':
    main()


