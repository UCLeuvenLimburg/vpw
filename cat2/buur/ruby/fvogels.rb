require 'set'


Position = Struct.new :x, :y do
    def move(dx, dy)
        Position.new(x + dx, y + dy)
    end
end


class Grid
    def initialize(width, height)
        @elts = (0...height).map do |y|
            (0...width).map do |x|
                yield Position.new(x, y)
            end
        end
    end

    def [](pos)
        @elts[pos.y][pos.x]
    end

    def width
        @elts[0].size
    end

    def height
        @elts.size
    end

    def inside?(position)
        0 <= position.x and position.x < width and 0 <= position.y and position.y < height
    end

    def around(position)
        [ [-1, 0], [1, 0], [0, -1], [0, 1] ].map do |dx, dy|
            pos = position.move(dx, dy)
            pos if inside? pos
        end.compact
    end

    def all_positions
        (0...width).flat_map do |x|
            (0...height).map do |y|
                Position.new(x, y)
            end
        end
    end

    def map
        Grid.new(width, height) do |p|
            yield self[p]
        end
    end

    def rows
        (0...height).map do |y|
            (0...width).map do |x|
                self[Position.new(x, y)]
            end
        end
    end
end


def solve(grid)
    neighbors = {}

    grid.all_positions.each do |pos|
        a = grid[pos]
        neighbors[a] ||= Set.new

        grid.around(pos).each do |q|
            b = grid[q]

            unless a == b
                neighbors[a].add(b)
            end
        end
    end

    grid.map do |a|
        neighbors[a].size
    end.rows.map do |row|
        row.map(&:to_s).join(' ')
    end.join("\n")
end


def main
    n = gets.to_i

    (1..n).each do |index|
        width, height = gets.strip.split(/ /).map(&:to_i)

        elts = (1..height).map do
            gets.strip.chars
        end

        grid = Grid.new(width, height) do |p|
            elts[p.y][p.x]
        end

        solution = solve grid

        solution.lines.each do |line|
            puts "#{index} #{line}"
        end
    end
end

main

# lines = <<END.lines.map(&:strip).map(&:chars)
# AAAAA
# BBBBB
# CCCCC
# END

# grid = Grid.new(lines[0].size, lines.size) do |p|
#     lines[p.y][p.x]
# end

# sol = solve(grid)

# puts sol