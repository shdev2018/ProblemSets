#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)

{
    long card_number;
    int num_digits = 0;


    // Prompt user for number
    {
        card_number = get_long("Number: ");
    }
    long n = card_number;

    // Return length of card number
    while (n != 0)
    {
        n /= 10;
        ++num_digits;
    }

    // Number of times to perform calculation
    int c = (num_digits / 2);

    // Initiate variables
    long g = card_number;
    long first_digits = card_number;
    int sum2 = 0;
    int sum3 = 0;
    int sum4;
    int h;
    int j;
    int k;

    // Return first digits of card number
    while (first_digits > 99)
    {
        first_digits = (first_digits / 10);
    }
    j = first_digits;
    k = first_digits / 10;

    // Take every other, multiply by 2, then add digits together.
    for (int i = 0; i < c; i++)
    {
        h = ((g % 100) / 10);
        h = (h * 2);
        if (h > 9)
        {
            h = ((h / 10) + (h % 10));
        }
        sum2 = (sum2 + h);
        g = trunc(g / 100);
    }

    g = card_number;

    // Sum of all remaining digits in card number.
    {
        h = (g % 10);
        sum3 = (sum3 + h);
        g = trunc(g / 10);
    }

    for (int i = 0; i < c; i++)
    {
        h = ((g % 100) / 10);
        sum3 = (sum3 + h);
        g = trunc(g / 100);
    }

    // Final checksum number
    sum4 = ((sum2 + sum3) % 10);

    // Check agaist VISA requirements
    if (k == 4 && (num_digits == 13 || num_digits == 16) && sum4 == 0)
    {
        printf("VISA\n");
    }

    // Check agaist AMEX requirements
    else if (num_digits == 15 && (j == 34 || j == 37) && sum4 == 0)
    {
        printf("AMEX\n");
    }

    // Check agaist MASTERCARD requirements
    else if (num_digits == 16 && (j > 50 && j < 56) && sum4 == 0)
    {
        printf("MASTERCARD\n");
    }

    // Card requirements unmet
    else
    {
        printf("INVALID\n");
    }

    return 0;
}
