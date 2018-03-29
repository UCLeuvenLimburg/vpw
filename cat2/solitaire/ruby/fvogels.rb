def register(n)
  $solution = [ $solution, n ].min
end

def solve
  unless $visited[$cfg]
    $visited[$cfg] = true
    if $cfg.count { |x| x } == 1
    then register($cfg.find_index { |x| x })
    else
      (0..$cfg.length-2).each do |i|
        if $cfg[i] and $cfg[i+1] and not $cfg[i+2]
        then
          $cfg[i] = $cfg[i+1] = false
          $cfg[i+2] = true
          solve
          $cfg[i] = $cfg[i+1] = true
          $cfg[i+2] = false
        end
      end
      
      (2..$cfg.length).each do |i|
        if $cfg[i] and $cfg[i-1] and not $cfg[i-2]
        then
          $cfg[i] = $cfg[i-1] = false
          $cfg[i-2] = true
          solve
          $cfg[i] = $cfg[i-1] = true
          $cfg[i-2] = false
        end
      end
    end
  end
end

INFINITY = 1.0/0.0

(1..gets.to_i).each do |index|
  $cfg = gets.strip.split(/ /)[1..-1].map { |x| x == '1' }
  $visited = Hash.new false
  $solution = INFINITY
  solve

  if $solution == INFINITY
  then puts "#{index} ONMOGELIJK"
  else puts "#{index} #{$solution + 1}"
  end
end
