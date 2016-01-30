def solve(ns, goal)
  ns.sort!

  i = 0
  j = ns.length - 1

  while i < j
    case
    when ns[i] + ns[j] < goal
    then i += 1

    when ns[i] + ns[j] > goal
    then j -= 1

    else return 'JA'
    end
  end
  
  'NEEN'
end

(1..gets.to_i).each do |index|
  gets
  weights = gets.split(/ /).map(&:to_i)
  goal = gets.to_i

  puts "#{goal} #{solve(weights, goal)}"
end
