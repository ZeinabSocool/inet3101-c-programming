#include <stdio.h>

void to_base_n(int number, int base)
{
    char symbols[] = "0123456789!@#$%^";
    int remainder;
    int digits[100];
    int count = 0;

    if (base < 2 || base > 16)
    {
        printf("Error: Base must be between 2 and 16.\n");
        return;
    }

    if (base == 8)
        printf("0");
    else if (base == 16)
        printf("0x");

    if (number == 0)
    {
        printf("0");
        return;
    }

    while (number > 0)
    {
        remainder = number % base;
        digits[count] = remainder;
        number = number / base;
        count++;
    }

    while (count > 0)
    {
        count--;
        printf("%c", symbols[digits[count]]);
    }
}

int main()
{
    int number;
    int base;

    printf("Enter a decimal number: ");
    scanf("%d", &number);

    printf("Enter a base (2-16): ");
    scanf("%d", &base);

    printf("Result: ");
    to_base_n(number, base);
    printf("\n");

    return 0;
}