#loketten solution

class Time
  def initialize(hours, minutes)
    @hours = hours
    @minutes = minutes
  end

  attr_reader :hours, :minutes

  def add(minutes)
    @minutes += minutes
      while @minutes >= 60
        @minutes -= 60
        @hours += 1
      end
  end

  def <(other)
    if(@hours == other.hours)
        @minutes < other.minutes
    else
        @hours < other.hours
    end
  end

  def >(other)
    if(@hours == other.hours)
      @minutes > other.minutes
    else
      @hours > other.hours
    end
  end

  def <=(other)
    not self > other
  end

  def >=(other)
    not self < other
  end

  def ==(other)
    @hours == other.hours and @minutes == other.minutes
  end

  def <=>(other)
    if self < other
      -1
    elsif self == other
      0
    else
      1
    end
  end

  def -(other)
    (@hours - other.hours) * 60 + @minutes - other.minutes 
  end
                
  def to_s
    "#{@hours} #{@minutes}"
  end
end


def main
  (1..gets.to_i).each do |index|
    result = "#{index} "
    longest = 0
    ls = (1..gets.to_i).to_a.map { Time.new(8,0) }
    

    gets.to_i.times do

      h, m = gets.strip.split(/ /)
      h, m = h.to_i, m.to_i
      time = Time.new(h, m)
      l = gets.to_i

      first = ls.shift
      wait = first - time

     

      first = time if first < time
      longest = wait if wait > longest


      result += "#{first} "
      first.add(l)
      ls.push(first)
      ls.sort!

    end

    result += "#{longest}" 
    puts result
  end
end

main