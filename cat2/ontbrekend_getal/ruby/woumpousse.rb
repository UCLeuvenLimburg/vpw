def matches(str, n)
  while str.start_with?(n.to_s)
    str = str[n.to_s.size..-1]
    n += 1
  end

  missing = n
  n += 1

  if str.empty?
    nil
  else
    while !str.empty? and str.start_with?(n.to_s)
      str = str[n.to_s.size..-1]
      n += 1
    end

    if str.empty?
      missing
    else
      nil
    end
  end
end


def solve(str)
  (1..str.size / 2).map do |n|
    str[0...n].to_i
  end.map do |n|
    matches(str, n)
  end.detect do |x|
    x
  end
end


def main
  n = gets.to_i

  (1..n).each do |index|
    str = gets.chomp
    solution = solve str

    if solution
      puts "#{index} #{solve(str)}"
    else
      puts "#{index} geen ontbrekend getal"
    end
  end
end


main
