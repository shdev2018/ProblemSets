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
    int p = 1;
    int q = (n - p);

    // Returns
    for (int i = 0; i < n; i++)
    {

        // Spaces
        for (int j = 0; j < q; j++)
        {
            printf(" ");
        }

        // 1st Hashes
        for (int k = 0; k < p; k++)
        {
            printf("#");
        }

        // Centre Column
        {
            printf("  ");
        }

        // 2nd Hashes
        for (int l = 0; l < p; l++)
        {
            printf("#");
        }

        printf("\n");
        p++;
        q--;
    }
}