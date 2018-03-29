def contains_loop(hoops):
    return any( x == y for x, y in hoops )

def solve(boxes):
    current = boxes[0] | { (y, x) for x, y in boxes[0] }
    longest = 0
    
    for i in range(1, len(boxes)):
        table = { x: set() for (_, x) in current }

        for x, y in boxes[i]:
            if x in table:
                table[x].add(y)
                
            if y in table:
                table[y].add(x)
        
        if contains_loop(current):
            longest = i

        current = set( (x, z) for x, y in current for z in table[y] )

        if not current:
            return longest
        
        
    if contains_loop(current):
        longest = len(boxes)

    return longest


def read_arc():
    x, y = input().split(' ')

    return (int(x), int(y))


n = int(input())

for index in range(1, n + 1):
    d = int(input())
    a = int(input())
    boxes = [ set( read_arc() for _ in range(a) ) for _ in range(d) ]
    solution = solve(boxes)
    print(solution)
