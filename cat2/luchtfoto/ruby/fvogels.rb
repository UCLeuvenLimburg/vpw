class UnionFind
    def initialize(parent = nil)
        @parent = parent || self
    end

    def root
        if root?
            self
        else
            @parent = @parent.root
        end
    end

    def root?
        @parent == self
    end

    def link(other)
        if root?
            @parent = other.root
        else
            root.link other
        end
    end

    def inspect
        "UF[#{object_id}]"
    end
end

Position = Struct.new(:x, :y) do
    def eql?(other)
        x == other.x and y == other.y
    end

    def hash
        x.hash ^ y.hash
    end

    def move(dx, dy)
        Position.new(x + dx, y + dy)
    end

    def inspect
        "(#{x},#{y})"
    end

    def to_s
        inspect
    end
end

def solve(grid)
    width = grid[0].size
    height = grid.size

    positions = (0...width).flat_map do |x|
        (0...height).map do |y|
            Position.new(x, y)
        end
    end

    land_positions = positions.select do |pos|
        grid[pos.y][pos.x] == '+'
    end

    table = land_positions.each_with_object({}) do |pos, acc|
        acc[pos] = UnionFind.new
    end

    land_positions.each do |pos|
        [ [-1, 0], [1, 0], [0, -1], [0, 1] ].each do |dx, dy|
            q = pos.move(dx, dy)

            if 0 <= q.x and 0 <= q.y and q.x < width and q.y < height and grid[q.y][q.x] == '+'
                table[pos].link(table[q])
            end
        end
    end

    roots = table.values.map(&:root).uniq


end


def main
    n = gets.to_i

    (1..n).each do |index|
        height = gets.to_i
        width = gets.to_i

        grid = (1..height).map do
            gets.strip.split(//)
        end

        solution = solve grid

        puts "#{index}"
    end
end


main

# xs = (0...4).map { UnionFind.new }
# xs[0].link(xs[1])
# xs[2].link(xs[3])
# xs[1].link(xs[0])

# p xs.map(&:root).uniq.size