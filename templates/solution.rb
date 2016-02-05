for i in 1..STDIN.readline.to_i
    pos,word = STDIN.readline.split(' ')
    puts word[pos.to_i - 1]
end