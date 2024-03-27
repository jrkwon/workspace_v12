

/**
 * main.c
 */
int main(void)
{
    int total = 100;
    float max;
    char ch;
    char str[] = "This is a string";
    int int_size, float_size, char_size;
    int long_int_size, double_size;
    char same = 0;
    char test = 0xEA;   /* 1100 1010 */
    char output;
    int i;
    int table[10];

    /* for loop */
    for (i = 0; i < 10; i++) {
        table[i] = i;
    }
    // result will be
    // table[[] = { 0, 1, 2, 3, ... 9 }




    /* bitwise operation */
    output = test | 0x33;      /* (1100 1010) Bit OR (0011 0011) output = 1111 1011 (0xFB) */
    /* output is now 0xFB   1111 1011 */
    /* new output should be 0110 0010  0x62 */
    /* clear 0**0 0**0: 0x99 1001 1001  ~0x99 --> ~(1001 1001) ==> 0110 0110 */
    output = output & ~0x99;
    /* output &= ~0x99 */

    max = 3.141529;
    ch = 'A';

    /* comments */
    // C++ comments
    total = total + 10; // 110
    total += 10;        // 120
    total++;            // 121
    ++total;            // 122
    if (total++ == 122) {    // 122 == 122 and 123
        same = 1;
    }

    same = 0;
    if (++total == 123) {    // 124 != 123
        same = 1;
    }

    int_size = sizeof(int);
    float_size = sizeof(float);
    long_int_size = sizeof(long int);
    double_size = sizeof(double);
    char_size = sizeof(char);

	return 0;
}
