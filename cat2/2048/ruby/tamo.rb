def shiftRow(rij, index) # schuif naar links
	return rij if index >= rij.length-1; 
	$score += rij[index] += rij.slice!(index+1) if rij[index] == rij[index+1] # neem getal er tussen uit en tel	op
	return shiftRow( rij, index+1 );
end

def updateBord(move)
	$bord.transpose if move == "O" || move == "B"; # flip rijen in kolommen bij 'onder' en 'boven'
	$bord.each_with_index do |row, index|
		row = row.select {|x| x > 0} # filter nulwaarden
		row.reverse! if move == "R" || move == "O" # links altijd begin
		$bord[index] = shiftRow(row, 0) # shift
		$bord[index].fill( 0, $bord[index].length...4 ) # opvullen met nullen
		$bord[index].reverse! if move == "R" || move == "O"; 
	end
	$bord.transpose if move == "O" || move == "B"; # re-flip
end

for $i in 1..STDIN.readline.to_i # aantal borden
	$score = 0 # init score
	$bord = Array.new(); # init bord	
	(1..4).each{ $bord.push STDIN.readline.split(" ").map(&:to_i) } # lees bord
	(1..STDIN.readline.to_i).each do # lees moves
		move = STDIN.readline.split(" ") # [richting, waarde, rij, kolom]
		updateBord(move.first)
		$bord[ move[2].to_i-1 ][ move[3].to_i-1 ] = move[1].to_i
	end
	puts "#{$i} #{$score}"
end