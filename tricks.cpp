/*
 if in a set you have initially (1e6) ranges (eg: [p,q]) and when you update for [l,r] to a value x then you combine all those range which comes in [l,r]
 completely and left and right part can be spilt in two so ranges can increase atmost by 2 in set and we combined them (or destory those to which we iterated)
 then over the q queries (1e6) the total segments you destroyed can't be more than created (n+2*m) so we can maintain ranges having same value and update
 them when needed by simply doing first by binary search and then iterating overy which we have to combine and break left and right part.
 */
/*
 nearest minimum element in left side of array can be done by stak
 */
/*
 farthest minimum element in left side of array can be done by first creating prefix minimum
 and then apply binary search
 */
/*
 bound on number of divisors is n^(1/3)
 */
/*
    set of {floor(n/i)} i from 1 to n can have at max 2*sqrt(n) size
    and left i be the max value such that floor(n/i)=x
    then upto j=n/n/(i+1) the value from n/(i+1) to n/j remain same
 */
/*

 floor(floor(a,b),c)=floor(a,b*c)

 */