void foo(int a, int b)
{
    a += 10;
    b += 20;
}

// a = 10, b = 20 --> a = 20, b = 10
void swap(int a, int b)
{
    int t = a;

    a = b;
    b = t;
}

void swap_works(int *pa, int *pb)
{
    int t = *pa;

    *pa = *pb;
    *pb = t;
}

/**
 * main.c
 */
int main(void)
{
    int a = 1, b = 2;

    swap(a, b);
    swap_works(&a, &b);

    foo(a, b);
    // what are a and b values?

    return 0;

    /*
    char ch[4] = { 'a', 0x64, 100, 12 };
    char *pch;
    int i[4] = { 0x1111, 0x2222, 0x3333, 0x4444 };
    int *pi;
    int t1, t2, t3;

    pch = &ch[0];
    pch++;

    pi = &i[0];
    //pi++;
    t1 = *(pi + 1);   // pi[1]    i[1]
    t3 = *(pi + 3);   // pi[3]    i[3]

    */


    /*
    int i1 = 0x11111111;
    int i2 = 0x22222222;
    int *pi1 = &i1;
    int *pi2 = &i2;

    *pi1 = pi2;
    *pi1 = i2;
    */

    /*
    int a = 0xaaaaaaaa;
    int b = 0xbbbbbbbb;
    int *pa;
    int *pb;

    pa = &a;    // pa will have the address of a.
    pb = &b;

    *pa = 0xabababab;
    */

    /*
    int mat[2][3] = {
       { 0x1111, 0x2222, 0x3333 },
       { 0x4444, 0x5555, 0x6666 }
    };
    int mat3[6] = { 0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666 };
    int mat2[2][3];

    mat[0][3] = 0xDEADBEEF;

    mat2[0][0] = 0x1111;
    mat2[0][1] = 0x2222;
    */

    /*
    char c1 = 'A';
    int a[3] = { 0x12341234, 0xFFFFFFFF, 0xDeadBeef };
    char c2 = 'B';
    int i = 100;
    */

    /*int arr[10];
    int b = 0x12341234;

    arr[0] = 1;
    arr[9] = 2;
    arr[10] = 0xDEADBEEF;
    */

}
