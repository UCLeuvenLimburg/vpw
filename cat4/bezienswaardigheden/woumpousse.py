# Slow, but working

class Pos:
    def __init__(self, x, y):
        self.__x = x
        self.__y = y

    @property
    def x(self):
        return self.__x

    @property
    def y(self):
        return self.__y

    def __str__(self):
        return "({}, {})".format(self.x, self.y)

    def __repr__(self):
        return str(self)

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y
    

def distance(p, q):
    dx = p.x - q.x
    dy = p.y - q.y
    return (dx ** 2 + dy ** 2) ** 0.5
    

def total_distance(path):
    return sum( distance(p, q) for p, q in zip(path, path[1:]) )


def compare_paths(ps, qs):
    if ps[0] == qs[0] and ps[-1] == qs[-1]:
        dp = total_distance(ps)
        dq = total_distance(qs)

        if dp <= dq:
            return -1
        elif dp > dq:
            return 1
        else:
            return 0
    elif ps == reversed(qs):
        if ps[0].x < qs[0].x:
            return -1
        else:
            return 1
    else:
        return 0


def remove_suboptimal(paths):
    return [ path for path in paths if all( compare_paths(path, other_path) != 1 for other_path in paths ) ]


def add_node(paths, node):
    prefixed = [ [ node ] + path for path in paths ]
    suffixed = [ path + [ node ] for path in paths ]

    return remove_suboptimal(prefixed + suffixed)
    

def build_bitonic_tour(nodes):
    nodes = sorted(nodes, key=lambda node: node.x)
    paths = [ [nodes[0]] ]

    for node in nodes[1:-1]:
        paths = add_node(paths, node)

    paths = [ [ nodes[-1] ] + path + [ nodes[-1] ] for path in paths ]

    return min(paths, key=total_distance)


if __name__ == '__main__':
    for i in range(int(input())):
        index = i + 1

        nodes = []
        for _ in range(int(input())):
            coords = map(int, input().split(' '))
            nodes.append( Pos(*coords) )

        bitonic_tour = build_bitonic_tour(nodes)
        print("{} {}".format(index, round(total_distance(bitonic_tour))))

