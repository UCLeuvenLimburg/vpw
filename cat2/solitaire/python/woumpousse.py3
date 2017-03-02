import array

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

    stones_left_stack = [ None for i in range(n_stones) ]
    index_stack = [ None for i in range(n_stones) ]
    direction_stack = [ None for i in range(n_stones) ]
    done_stack = [ None for i in range(n_stones) ]

    stones_left_stack[0] = n_stones
    index_stack[0] = 0
    direction_stack[0] = -1
    done_stack[0] = False
    si = 0

    while si >= 0:
        n_stones = stones_left_stack[si]
        index = index_stack[si]
        direction = direction_stack[si]
        done = done_stack[si]

        if not done:
            if n_stones == 1:
                leftmost = min(leftmost, next(i for i in range(length) if ns[i]))
                si -= 1

                if si >= 0:
                    done_stack[si] = True
                else:
                    return leftmost

            else:
                if index == length:
                    si -= 1

                    if si >= 0:
                        done_stack[si] = True
                    else:
                        return leftmost
                        
                elif direction == -1:
                    if index >= 2 and ns[index] and ns[index-1] and not ns[index-2]:
                        ns[index] = False
                        ns[index-1] = False
                        ns[index-2] = True
                        si += 1
                        stones_left_stack[si] = n_stones - 1
                        index_stack[si] = 0
                        direction_stack[si] = -1
                        done_stack[si] = False
                    else:
                        stones_left_stack[si] = n_stones
                        index_stack[si] = index
                        direction_stack[si] = 1
                        done_stack[si] = False

                else:
                    if index + 2 < length and ns[index] and ns[index+1] and not ns[index+2]:
                        ns[index] = False
                        ns[index+1] = False
                        ns[index+2] = True
                        si += 1
                        stones_left_stack[si] = n_stones - 1
                        index_stack[si] = 0
                        direction_stack[si] = -1
                        done_stack[si] = False
                    else:
                        stones_left_stack[si] = n_stones
                        index_stack[si] = index + 1
                        direction_stack[si] = -1
                        done_stack[si] = False
        else:
            si -= 1

            ns[index] = True
            ns[index + direction] = True
            ns[index + 2 * direction] = False
            
            if direction == -1:
                si += 1
                stones_left_stack[si] = n_stones
                index_stack[si] = index
                direction_stack[si] = 1
                done_stack[si] = False
            elif index == length:
                done_stack[si] = True
            else:
                si += 1
                stones_left_stack[si] = n_stones
                index_stack[si] = index + 1
                direction_stack[si] = -1
                done_stack[si] = False

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


