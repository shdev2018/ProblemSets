#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)

// Prompt user for 'Change Owed'
{
    float n;
    do
    {
        n = get_float("Change owed: ");
    }

    // Set input conditions
    while (n < 0);

    // Represent change in cents
    n = (n * 100);

    // Round float to last interger place
    float p = roundf(n);

    // Returns minimum number of quarters
    int q = (p / 25);

    // Returns minimum number of dimes
    int r = (int) p;
    int s = (r % 25);
    int t = (s / 10);

    // Returns minimum number of nickles
    int u = (s % 10);
    int v = (u / 5);

    // Returns minimum number of pennies
    int w = (u % 5);

    // Calculate total coins required
    int x = (q + t + v + w);

    {
        printf("%d\n", x);
    }
}