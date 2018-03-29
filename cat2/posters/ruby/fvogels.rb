(1..gets.to_i).each do |index|
  posters = (1..gets.to_i).map.with_index do |i, j|
    [j] + gets.split(/ /).map(&:to_i)
  end

  wall_size = posters.map { |index, start, length| start + length }.max

  wall = [nil] * wall_size

  posters.each do |index, start, length|
    (start...start+length).each do |i|
      wall[i] = index
    end
  end

  set = Hash.new false

  wall.each do |index|
    if index then
      set[index] = true
    end
  end

  puts set.size
end
