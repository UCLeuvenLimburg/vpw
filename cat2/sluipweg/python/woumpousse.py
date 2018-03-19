class Vector2D:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, other):
        return Vector2D(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        return Vector2D(self.x - other.x, self.y - other.y)

    def __neg__(self):
        return Vector2D(-self.x, -self.y)

    def __eq__(self, other):
        return other and self.x == other.x and self.y == other.y

    def __str__(self):
        return f"({self.x}, {self.y})"

    def __repr__(self):
        return str(self)


class PathNode:
    def __init__(self):
        self.previous = None
        self.next = None

    def __repr__(self):
        return str( (self.previous, self.next) )

class Grid:
    def __init__(self, width, height, initializer = lambda p: None):
        self.__items = [ [ initializer(Vector2D(x, y)) for y in range(height) ] for x in range(width) ]
        self.width = width
        self.height = height

    def __getitem__(self, position):
        return self.__items[position.x][position.y]

    def __setitem__(self, position, value):
        self.__items[position.x][position.y] = value

    def map(self, func):
        return Grid(self.width, self.height, lambda p: func(self[p]))

    def __str__(self):
        def show(x, y):
            return str(self[Vector2D(x, y)])
        
        return "\n".join( "".join(show(x, y) for x in range(self.width)) for y in range(self.height) )

    def inside(self, position):
        return 0 <= position.x < self.width and 0 <= position.y < self.height


def parse_direction(x):
    if x == 1 or x == 'W':
        return Vector2D(-1, 0)
    elif x == 2 or x == 'E':
        return Vector2D(1, 0)
    elif x == 3 or x == 'N':
        return Vector2D(0, -1)
    else:
        return Vector2D(0, 1)

    
def parse_grid(size, start, path):
    grid = Grid(size, size)
    p = start
    grid[p] = PathNode()

    for step in path:
        d = parse_direction(step)
        grid[p].next = d
        p += d
        node = PathNode()
        grid[p] = node
        node.previous = -d

    return grid


def show(grid):
    def aux(x):
        if x:
            return '*'
        else:
            return '.'
        
    return str(grid.map(aux))


def find_corners(grid):
    for x in range(grid.width):
        for y in range(grid.height):
            pos = Vector2D(x, y)
            node = grid[pos]

            if node and ((not node.next) or (not node.previous) or (node.next != -node.previous)):
                yield pos


def find_shortcut_at(grid, position, direction):
    if grid[position] and (direction == grid[position].next or direction == grid[position].previous):
        return (None, None, float('inf'))
    
    p = position + direction
    n = 1

    while grid.inside(p) and not grid[p]:
        p += direction
        n += 1

    if grid.inside(p):
        return (position, p, n)
    else:
        return (None, None, float('inf'))

def find_shortcuts_at(grid, position):
    for direction in [ Vector2D(x, y) for x, y in [ (-1, 0), (1, 0), (0, -1), (0, 1) ] ]:
        (a, b, d) = find_shortcut_at(grid, position, direction)
        if d < float('inf'):
            yield (a, b, d)

def forward_length(grid, start):
    p = start
    length = 0

    while grid[p] and grid[p].next:
        p += grid[p].next
        length += 1

    return length

def backward_length(grid, start):
    p = start
    length = 0

    while grid[p] and grid[p].previous:
        p += grid[p].previous
        length += 1

    return length

def find_shortcuts(grid):
    for corner in find_corners(grid):
        for (a, b, d) in find_shortcuts_at(grid, corner):
            yield (a, b, d)
    
def shortest_path(grid):
    best = float('inf')
    
    for (a, b, d) in find_shortcuts(grid):
        total = backward_length(grid, a) + d + forward_length(grid, b)

        if total < best:
            best = total

    return best
            

# grid = parse_grid(10, Vector2D(1, 1), 'ZZEEENNEESSSSSSWWWW')
# print(show(grid))
# print(shortest_path(grid))

n = int(input())

for index in range(1, n+1):
    size, x, y = map(int, input().split(' '))
    path = list(map(int, input().split(' ')[1:]))
    start = Vector2D(x, y)
    grid = parse_grid(size, start, path)
    solution = shortest_path(grid)

    if index == 5:
        print(x, y)
        print(path)
        print(show(grid))
        print(index, solution)
