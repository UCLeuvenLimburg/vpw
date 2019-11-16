def solve(initial, transactions)
    transactions.sort.reduce(initial) do |balance, transaction|
        balance += transaction

        if balance < 0
            balance -= 35
        end

        balance
    end
end

def main
    n = gets.to_i

    (1..n).each do |index|
        init = gets.to_i
        transfers = gets.strip.split(/ /)[1..-1].map(&:to_i)
        solution = solve(init, transfers)

        puts "#{index} #{solution}"
    end
end

main