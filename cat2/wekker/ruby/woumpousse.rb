def shortest_hours(h, hh)
  [ [h, hh].max - [h, hh].min, [h, hh].min - [h, hh].max + 24 ].min
end

def solve(h, m, hh, mm)
  if m <= mm
  then
    solutions = []
  
    solutions << mm - m + shortest_hours(h, hh)
    solutions << 60 + m - mm + shortest_hours((h - 1 + 24) % 24, hh)

#    puts " #{[h,m,hh,mm]} : #{solutions}"

    solutions.min
  else
    solve(hh, mm, h, m)
  end
end


def main
  (1..gets.to_i).each do |index|
    h, m = gets.split(/ /).map(&:to_i)
    hh, mm = gets.split(/ /).map(&:to_i)

    puts "#{index} #{solve(h,m,hh,mm)}"
  end
end


main
