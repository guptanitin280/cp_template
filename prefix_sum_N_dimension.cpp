// taking prefix sum

// even a stupid chicken can see method2 scale better
int a[10][10];
void method1() {
    for (int i = 1; i < 10; i++) {
        for (int j = 1; j < 10; j++) {
            a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];
        }
    }
}
void method2() {
    for (int w = 0; w < 2; w++) {
        for (int i = 1; i < 10; i++) {
            for (int j = 1; j < 10; j++) {
                a[i][j] += a[i - (w == 0)][j - (w == 1)];
            }
        }
    }
}
