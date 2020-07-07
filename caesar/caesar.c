//Encrypts plaintext to cyphertext via a given key
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Receive command line arguments
int main(int argc, string argv[])
{

    // Check input is valid number of strings
    if (argc != 2)
    {
        printf("usage : ./caesar k \n");
        return 1;
    }

    // Convert string to interger (ASCII to int)
    int k = atoi(argv[1]);

    //Prompt user for plaintext
    string p = get_string("plaintext: ");

    // Start encryption process
    printf("ciphertext: ");

    // Operate on each letter individually
    for (int i = 0; i < strlen(p); i++)
    {
        if (isalpha(p[i]))
        {
            // Check for case
            if (isupper(p[i]))
            {
                // Check to see whether 'wrap-around' is neseccary
                if (p[i] + (k % 26) <= 'Z')
                {
                    printf("%c", p[i] + (k % 26));
                }
                else
                    // Count forwards from 'A'
                {
                    printf("%c", ((p[i] + (k % 26)) - 90) + 64);
                }
            }
            else if (islower(p[i]))
            {
                // Same process for lower case
                if (p[i] + (k % 26) <= 'z')
                {
                    printf("%c", p[i] + (k % 26));
                }
                else
                {
                    printf("%c", ((p[i] + (k % 26)) - 122) + 96);
                }
            }
        }
        // If char is not alphabetical
        else
        {
            printf("%c", p[i]);
        }
    }
    // New line
    printf("\n");
    return 0;
}