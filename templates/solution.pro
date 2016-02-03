% this removes the '| :' from the prompt line 
:- prompt(_,'').

main :-
  read_line([Num_]), number_chars(Num,Num_),
  solve_puzzle(Num).

solve_puzzle(0) :- !.
solve_puzzle(NumP) :-
  read_line([Nth_, Chars]), number_chars(Nth,Nth_),
  nth1(Nth, Chars, Char), write_ln(Char),
  NNumP is NumP-1, solve_puzzle(NNumP).

read_line(Tokens) :- read_line_to_codes(current_input,Lc), atom_codes(La, Lc), atom_chars(La, Line), lexer(Line,Tokens).
lexer([],[]).
lexer([' '|Ls],Ts) :- !, lexer(Ls,Ts).
lexer(L,[T|Ts]) :- append(T,[' '|Ls],L), !, lexer(Ls,Ts).
lexer(T,[T]).