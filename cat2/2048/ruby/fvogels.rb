Position = Struct.new(:x, :y) do
  def to_s
    "(#{x},#{y})"
  end

  def xy
    [x, y]
  end

  def south
    Position.new(x, y + 1)
  end

  def north
    Position.new(x, y - 1)
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

  def [](position)
    @items[position.y][position.x]
  end

  def []=(position, c)
    @items[position.y][position.x] = c
  end

  def width
    @items[0].length
  end

  def height
    @items.length
  end

  def rotate_ccw
    Grid.new(height, width) do |position|
      x, y = position.xy

      self[Position.new(width-y-1, x)]
    end
  end

  def rotate_cw
    rotate_ccw.rotate_ccw.rotate_ccw
  end

  def rows
    @items
  end

  def inside?(position)
    0 <= position.x and position.x < width and 0 <= position.y and position.y < height
  end

  def dup
    Grid.new(width, height) do |pos|
      self[pos]
    end
  end

  def shift_south!
    copy = Grid.new(width, height) { nil }
    score = 0
    
    (0...width).each do |x|
      p = Position.new(x, height - 1)

      while inside? p
        q = p.north

        while inside? q and not self[q]
          q = q.north
        end

        if inside? q
        then
          case
          when !self[p]
          then
            self[p] = self[q]
            self[q] = nil

          when self[p] == self[q]
          then
            self[p] *= 2            
            self[q] = nil
            score += self[p]
            p = p.north

          else
            p = p.north
          end          
        else
          p = Position.new(-1,-1)
        end
       
      end
    end

    score
  end

  def shift_south
    copy = dup
    score = copy.shift_south!
    [score, copy]
  end
  
  def shift_north
    score, grid = rotate_ccw.rotate_ccw.shift_south
    [ score, grid.rotate_ccw.rotate_ccw ]
  end

  def shift_east
    score, grid = rotate_cw.shift_south
    [ score, grid.rotate_ccw ]
  end

  def shift_west
    score, grid = rotate_ccw.shift_south
    [ score, grid.rotate_cw ]
  end

  def to_s
    rows.map { |row| row.map { |x| if x then x.to_s.ljust(3) else '.  'end }.join(' ') }.join("\n")
  end
end

def parse(rows)
  Grid.new(4, 4) do |position|
    c = rows[position.y][position.x]

    if c == '.'
    then nil
    else c.to_i
    end
  end
end


def main
  (1..gets.to_i).each do |index|    
    rows = (1..4).map { gets.strip.split(/ /) }
    
    grid = parse rows

    total_score = 0
    
    (1..gets.to_i).each do
      dir, val, y, x = gets.strip.split(/ /)
      val = val.to_i
      x = x.to_i
      y = y.to_i

      case dir
      when "O"
      then score, grid = grid.shift_south

      when "B"
      then score, grid = grid.shift_north

      when "R"
      then score, grid = grid.shift_east

      when "L"
      then score, grid = grid.shift_west
      end

      grid[ Position.new(x - 1, y - 1) ] = val
      total_score += score
    end

    puts "#{index} #{total_score}"
  end
end


main

# data = <<END.lines.map { |line| line.strip.split(/ /) }
# . 8 2 .
# . . 8 2
# 4 4 8 2
# . . 4 4
# END

# data = <<END.lines.map { |line| line.strip.split(/ /) }
# 8 2 . .
# 8 2 . .
# 8 8 2 .
# 8 . . .
# END


# g = parse(data)
# puts g

# score, g = g.shift_west
# puts score
# puts g

# score, g = g.shift_south
# puts score
# puts g
