class Solver
  def initialize(words)
    @words = Hash.new do |hash, key|
      hash[key] = []
    end

    words.each do |word|
      @words[word[0]] << word
    end
    
    @results = [ "" ]
  end

  def register(result)
    case
    when @results[0].size == result.size
    then @results << result
    when @results[0].size < result.size
    then @results = [ result ]
    end
  end
  
  def solve
    @words.keys.each do |first_letter|
      solve_aux(first_letter, "", 0)
    end
  end

  def solve_aux(first_letter, acc, n)
    words = @words[first_letter]

    register acc if n > 1

    (0...words.length).each do |index|
      word = words[index]
      
      if word
      then
        bcc = acc + word
        words[index] = nil
        solve_aux(word[-1], bcc, n + 1)
        words[index] = word
      end
    end
  end

  attr_reader :results
end


def solve(words)
  solver = Solver.new(words)
  solver.solve
  
  solver.results.uniq.sort
end


def main
  (1..gets.to_i).each do |i|
    words = gets.strip.split(/ /)[1..-1]

    result = solve(words)
    
    if result[0].empty?
    then puts "#{i} geen oplossing"
    else puts "#{i} #{result.join(' ')}"
    end
  end
end

main
