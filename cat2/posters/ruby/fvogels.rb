(1..gets.to_i).each do |index|
  posters = (1..gets.to_i).map do
    gets.split(/ /).map(&:to_i)
  end

  wall_size = posters.map { |start, length| start + length }.max

  wall = [nil] * (wall_size + 1)

  posters.each.with_index do |poster, index|
    start, length = poster

    (start...start+length).each do |i|
      wall[i] = index
    end
  end

  puts(wall.uniq.size - 1)
end
