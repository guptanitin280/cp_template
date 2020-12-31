//1. it generate every possible subset of a set , ex:- 1001  :- 0000,0001,1001,1000
int ss=0;
do{
	//process subset ss of x
}while(ss=(ss-x)&x);

//2. remove last bit of a number
 n=n&(n-1); //ex:- 101100 -> 101000

 //3. get the lowest bit
a) i&-i
b) i&~(i-1)

