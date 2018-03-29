def solve(grid):
    width = len(grid[0])
    height = len(grid)
    result = {}
    
    def inside(pos):
        x, y = pos
        return x >= 0 and y >= 0 and x < width and y < height

    def around(pos):
        x, y = pos
        return [ p for p in [ (x-1, y), (x+1, y), (x, y-1), (x, y+1) ] if inside(p) ]
    
    def flood(pos):
        x, y = pos
        
        if grid[y][x] == '+':
            grid[y][x] = '.'

            return sum( flood(p) for p in around((x, y)) ) + 1
        else:
            return 0

    def register(size):
        if size in result:
            result[size] += 1
        else:
            result[size] = 1
            
    for y in range(height):
        for x in range(width):
            if grid[y][x] == '+':
                register(flood((x,y)))

    return result



def main():
    for index in range(0, int(input())):
        height = int(input())
        width = int(input())

        lines = [ list(input()) for _ in range(height) ]
        solution = solve(lines)
        sizes = sorted(solution.keys())
        
        print( " ".join( [str(index + 1)] + [ "{} {}".format(k, solution[k]) for k in sizes ] ) )

            
if __name__ == '__main__':
    main()
