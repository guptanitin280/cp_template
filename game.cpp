// Nim-Game:-
Piles are p1,p2,p3,..,pn 
x=p1^p2^p3...pn
the one who cant move lose
Losing state:- x=0
Winning state:- x!=0
  
// Grundy Theorm
Piles are:- p1,p2,p3...pn
Move on Pi go to k number of state:-
1. {Pi11,pi12...,}
2. {Pi21, Pi22, ... }
.
.
k. {Pik1,pik2...}
Let the G be grundy number of given states
Losing state:- G=0
Winning state:- G!=0
G=G(p1)^G(p2)^G(p3)..^G(pn)
G(pi)=mex({G(Pi11)^G(pi12)...},{G(Pi21)^G(Pi22), ... },...,{G(Pik1)^G(pik2)...})
