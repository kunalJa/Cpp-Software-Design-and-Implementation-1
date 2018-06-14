#include <stdio.h>

int gcd(int, int);

int main() {
    int GCDRESULT1 = gcd(48, 18);
    printf("GCD of %d and %d is: %d \n", 48, 18, GCDRESULT1);

    int GCDRESULT2 = gcd(144, 60);
    printf("GCD of %d and %d is: %d \n", 144, 60, GCDRESULT2);

    int GCDRESULT3 = gcd(65, 12);
    printf("GCD of %d and %d is: %d \n", 65, 12, GCDRESULT3);

    int GCDRESULT4 = gcd(179, 7);
    printf("GCD of %d and %d is: %d \n", 179, 7, GCDRESULT4);
}

int gcd(int x, int y){
    if(x == y){
        return x;
    }

    else if(x > y){
        return gcd(x-y, y);
    }

    else if(y > x){
        return gcd(x, y-x);
    }
}
