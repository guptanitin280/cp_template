bool is(int a,int b){
    if(a==0 || b==0)
        return false;
    int result=a*b;
    if(a==result/b)
        return false;
    return true;
}