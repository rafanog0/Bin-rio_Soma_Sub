#include <stdio.h>
#include <stdint.h>
#include <math.h>

int NAND(int a, int b)
{
    if(a == 1)
    {
        if(b == 1)
            return 0;
        else
            return 1;
    }
    else
        return 1;
}

int NOT(int a) { return NAND(a, a); }

int AND(int a, int b) { return !(NAND(a,b)); }

int OR(int a, int b)
{
    int not_a = NOT(a);
    int not_b = NOT(b);
    int and_not_a_not_b = AND(not_a, not_b);
    return NOT(and_not_a_not_b);
}

int XOR(int a, int b)
{
    int or_ab = OR(a, b);
    int and_ab = AND(a, b);
    int not_and_ab = NOT(and_ab);
    return AND(or_ab, not_and_ab);
}

void half_adder(int a, int b, int *sum, int *carry)
{
    *sum = XOR(a, b);
    *carry = AND(a, b);
}

void full_adder(int a, int b, int carry_in, int *sum, int *carry_out)
{
    int sum1, carry1, carry2;
    half_adder(a, b, &sum1, &carry1);
    half_adder(sum1, carry_in, sum, &carry2);
    *carry_out = OR(carry1, carry2);
}

int add(int a, int b)
{
    unsigned int a_u = (unsigned int)a;
    unsigned int b_u = (unsigned int)b;
    int result = 0;
    int carry = 0;
    int power_of_two = 1;

    for (int i = 0; i < 32; i++)
    {

        int bit_a = (a_u / power_of_two) % 2;
        int bit_b = (b_u / power_of_two) % 2;
        int sum_bit, carry_out;

        full_adder(bit_a, bit_b, carry, &sum_bit, &carry_out);
        result += sum_bit * power_of_two;
        carry = carry_out;
        power_of_two *= 2;
    }

    return result;
}

int invert_bits(int a)
{
    unsigned int a_u = (unsigned int)a;
    int result = 0;
    int power_of_two = 1;

    for (int i = 0; i < 32; i++)
    {
        int bit = (a_u / power_of_two) % 2;
        int inverted_bit = NOT(bit);
        result += inverted_bit * power_of_two;
        power_of_two *= 2;
    }

    return result;
}

int sub(int a, int b)
{
    int inverted_b = invert_bits(b);
    int negative_b = add(inverted_b, 1);
    return add(a, negative_b);
}

int main()
{
    int num1, num2;

    printf("Primeiro inteiro: ");
    scanf("%d", &num1);

    printf("Segundo inteiro: ");
    scanf("%d", &num2);

    int sum = add(num1, num2);
    int difference = sub(num1, num2);

    printf("Soma: %d\n", sum);
    printf("Subtração: %d\n", difference);

    return 0;
}
