def add_word(seq)
	last_letter = seq[-1][-1]
	# roep voor elke combinatie de methode opnieuw op
	mogelijkheden = $first.include?(last_letter) ? ($first[last_letter] - seq).each{|name| add_word(seq + [name])} : []
	prev, curr = $sequences.last, seq.join 
	if mogelijkheden.empty? && seq.size > 1 && (prev.nil? || prev.size <= curr.size) # vul de beste mogelijkheden aan (sequences)
		# bij gelijke lengte: voeg toe, een [langere combinatie] vervangt de array
		(prev.nil? || prev.size == curr.size) ? $sequences << curr : $sequences = [curr]
	end
end

for i in 1..STDIN.readline.to_i 
	$first = (words = STDIN.readline.split(" ")[1..-1]).group_by{|word| word[0]} # groepeer op eerste letter
    $sequences = [] # array van beste oplossingen
    words.each {|name| add_word [name]} # zet elk woord als begin en kijk welke combi's er zijn (add_word)
	puts  "#{i} #{$sequences.any? ? $sequences.sort.join(" ") : "geen oplossing"}"
end