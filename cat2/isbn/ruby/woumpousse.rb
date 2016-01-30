class Array
  def sum
    inject(0, :+)
  end
end


def check(isbn)
  isbn.map.with_index do |n, i|
    weight = if i.even? then 1 else 3 end
    weight * n
  end.sum % 10 == 0
end


def insertions(isbn)
  (0..isbn.length).map do |i|
    (0..9).map do |digit|
      isbn[0...i] + [digit] + isbn[i..-1]
    end
  end.flatten(1)
end

def corrections(isbn)
  insertions(isbn).select do |isbn|
    check isbn
  end
end

def to_number(ns)
  ns.inject(0) do |acc, n|
    acc * 10 + n
  end
end

(1..gets.to_i).each do |index|
  ns = gets.strip.split(//).map(&:to_i)
  
  solution = corrections(ns).map do |isbn|
    to_number(isbn)
  end.uniq.sum

  puts "#{index} #{solution}"
end




