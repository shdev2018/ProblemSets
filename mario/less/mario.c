#include <stdio.h>
#include <cs50.h>

int main(void)

// Prompt user for Height
{
    int n;
    do
    {
        n = get_int("Height: ");
    }

    // Set input conditions
    while (n < 0 || n > 23);

    // Initialize variables
    int p = (n + 1);
    int q = 2;
    int r = (p - q);

    // Returns
    for (int i = 0; i < n; i++)
    {

        // Spaces
        for (int j = 0; j < r; j++)
        {
            printf(" ");
        }

        // Hashes
        for (int k = 0; k < q; k++)
        {
            printf("#");
        }

        printf("\n");
        q++;
        r--;
    }
}