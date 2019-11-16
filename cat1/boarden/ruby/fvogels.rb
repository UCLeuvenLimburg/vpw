def solve(passengers)
    result = 0
    last = -1.0 / 0.0

    passengers.each do |passenger|
        result += 1 if passenger > last
        last = passenger
    end

    result
end

def main
    n = gets.to_i

    (1..n).each do |index|
        passenger_count = gets.to_i
        passengers = (1..passenger_count).map do
            gets.to_i
        end

        solution = solve passengers

        puts "#{index} #{solution}"
    end
end

main