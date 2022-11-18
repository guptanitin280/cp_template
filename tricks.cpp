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
 ceil(ceil(a,b),c)=ceil(a,b*c)
 
 */

/*
constraints can be solved by building constraints graph
called cow-game
eg:- https://atcoder.jp/contests/abc216/tasks/abc216_g
resource:- https://www.cs.huji.ac.il/course/2002/dast/slides/BellmanFord.pdf
*/

/*
a⋅b≤c→a≤⌊c/b⌋ is correct
a⋅b<c→a<⌊c/b⌋ is incorrect
a⋅b≥c→a≥⌊c/b⌋ is correct
a⋅b>c→a>⌊c/b⌋ is correct
/*

if x*y is prefect square then there reduced form ( in which only prime are considered whose power is odd) is equal.
*/

/*
floor(x/i) where i=[1,x] take only at max 2*sqrt(x) different values, because for i=[1,sqrt(x)] -> only sqrt(x) different value, i=[sqrt(x)+1,x], this implies
n/i<=sqrt(x) again sqrt(x) value.
*/

/*
the max j for which n/j=n/i is equal to n/(n/i)
*/

/*
if X>=Y then (X/2)>=X%Y
*/

/*
For a problem, there can be a subproblem in which you are asked to compare two array/string,( and we can do some operation on strigns)so check if they belong to same equivalence classes, means if their any 
form (like lexicographically smallest) are same then we can convert both of these in each other.
*/

/*
diagonals of a parallelogram split each other in the middle
*/
