def rows(grid):
    return grid

def columns(grid):
    return [ [ grid[y][x] for y in range(len(grid)) ] for x in range(len(grid)) ]

def valid_values(grid):
    return all( all(x == 0 or x == 1 for x in row ) for row in rows(grid) )

def no_triplets(grid):
    def no_triplets_in(xs):
        last = None
        count = 0

        for x in xs:
            if last == x:
                count += 1

                if count > 2:
                    return False
            else:
                count = 1

        return True
            
    return all( no_triplets_in(row) for row in rows(grid) ) and all( no_triplets_in(col) for col in columns(grid) )

def balanced(grid):
    return all( sum(row) == len(grid) // 2 for row in rows(grid) ) and all( sum(col) == len(grid) // 2 for col in columns(grid) )

def no_dups(grid):
    def contains_no_duplicates(xs):
        xs = list(xs)
        return len(set(xs)) == len(xs)

    return contains_no_duplicates( tuple(row) for row in rows(grid) ) and contains_no_duplicates( tuple(col) for col in columns(grid) )


def solve(grid):
    return valid_values(grid) and no_triplets(grid) and balanced(grid) and no_dups(grid)


n = int(input())

for index in range(n):
    size = int(input())
    grid = [ [ int(x) for x in input() ] for _ in range(size) ]
    if solve(grid):
        solution = 'juist'
    else:
        solution = 'fout'

    first_row = "".join( str(x) for x in grid[0] )
    print( f"{first_row} {solution}" )
