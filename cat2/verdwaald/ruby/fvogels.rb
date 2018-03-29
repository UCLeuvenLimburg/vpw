class Position
  def initialize(x, y)
    @x, @y = x, y
  end

  def move(direction)
    case direction
    when 'B'
    then Position.new(x, y-1)

    when 'O'
    then Position.new(x, y+1)

    when 'L'
    then Position.new(x-1, y)

    when 'R'
    then Position.new(x+1, y)

    else
      abort "Unknown direction #{direction}"
    end    
  end
  
  attr_reader :x, :y

  def to_s
    "(#{x},#{y})"
  end

  def inc
    Position.new(x+1,y+1)
  end

  def <=>(other)
    [x, y] <=> [other.x, other.y]
  end

  def eql?(other)
    x == other.x and y == other.y
  end

  def hash
    x + y
  end
end


class Set
  def initialize
    @items = Hash.new false
  end

  def add(x)
    @items[x] = true
  end

  def remove(x)
    @items.delete x
  end

  def contains?(x)
    @items[x]
  end

  def items
    @items.keys
  end
end


class Grid
  def initialize(width, height)
    @items = (0...height).map do |y|
      (0...width).map do |x|
        yield Position.new(x, y)
      end
    end
  end

  def width
    @items[0].length
  end

  def height
    @items.length
  end

  def [](position)
    @items[position.y][position.x]
  end

  def each_position
    (0...height).each do |y|
      (0...width).each do |x|
        yield Position.new(x, y)
      end
    end
  end

  def inside? position
    0 <= position.x and position.x < width and 0 <= position.y and position.y < height
  end
end

  
class WalkSimulator
  def initialize(grid)
    @grid = grid
    @superposition = Set.new

    @grid.each_position do |pos|
      @superposition.add pos
    end
  end

  def assert(x)
    @superposition.items.each do |pos|
      unless @grid[pos] == x
        @superposition.remove pos
      end
    end
  end

  def move(direction)
    new_superposition = Set.new

    @superposition.items.each do |position|
      pos = position.move(direction)

      if @grid.inside? pos
      then new_superposition.add pos
      else new_superposition.add position
      end
    end

    @superposition = new_superposition
  end

  attr_reader :superposition
end


def solve(grid, walk)
  sim = WalkSimulator.new grid

  walk.split(//).each.with_index do |ch, i|
    if i.even?
    then sim.assert ch
    else sim.move ch
    end
  end

  sim.superposition.items
end

def main
  (1..gets.to_i).each do |index|
    height, width = gets.split(/ /).map(&:to_i)
    
    row_strings = (1..height).map { gets }
    grid = Grid.new(width, height) do |pos|
      row_strings[pos.y][pos.x]
    end

    gets
    walk = gets.strip

    solution = solve(grid, walk)

    solution.map!(&:inc)

    if solution.empty?
    then puts "#{index} ONMOGELIJK"
    else puts "#{index} #{solution.uniq.sort.map(&:to_s).join(' ')}"
    end
  end
end

main
