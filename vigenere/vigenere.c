//Encrypts plaintext to cyphertext via a given key
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Receive command line arguments
int main(int argc, string argv[])
{

    string k;
    int q;

    // Check input is valid number of strings
    if (argc == 2)
    {
        //Check input is entirely alphabetical
        k = (argv[1]);
        q = 0;

        for (int h = 0; h < strlen(k); h++)
        {
            if (isalpha(k[h]))
            {
                q++;
            }
        }
    }

    // Check input meets criterea
    if (argc != 2 || q < strlen(k))
    {
        printf("usage : ./vigenere k \n");
        return 1;
    }

    //Prompt user for plaintext
    string p = get_string("plaintext: ");

    int o;

    // Start encryption process
    printf("ciphertext: ");

    // Operate on each letter individually
    for (int i = 0, n = 0; i < strlen(p); i++)
    {
        if (isalpha(p[i]))
        {
            // Check for key case
            if (isupper(k[n]))
            {
                o = (int)k[n] - 65;
            }
            else
            {
                o = (int)k[n] - 97;
            }
            // Check for plaintext case
            if (isupper(p[i]))
            {
                // Check to see whether 'wrap-around' is neseccary
                if ((p[i] + o) <= 'Z')
                {
                    printf("%c", p[i] + o);
                }
                else
                    // Count forwards from 'A'
                {
                    printf("%c", ((p[i] + o) - 90) + 64);
                }
            }
            else if (islower(p[i]))
            {
                // Same process for lower case
                if ((p[i] + o) <= 'z')
                {
                    printf("%c", p[i] + o);
                }
                else
                {
                    printf("%c", ((p[i] + o) - 122) + 96);
                }
            }
            n++;
        }
        // If char is not alphabetical
        else
        {
            printf("%c", p[i]);
        }
        // If exhausted length of key, start over again
        if (n >= strlen(k))
        {
            n = (n - strlen(k));
        }
    }
    // New line
    printf("\n");
    return 0;
}