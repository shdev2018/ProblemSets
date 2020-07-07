//Necessary libraries
#define  _XOPEN_SOURCE
#include <unistd.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

//Gets arguments
int main(int argc, string argv[])
{

    //Check correct number of arguents submitted
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    //Get hash from argument 1
    string yourhash = argv[1];

    //Initializations
    char cracked[6];
    int counter = 0;
    string myhash = "";
    int i;
    int j;
    int k;
    int l;
    int m;

    //Get salt from hash
    char salt[3];
    salt[0] = yourhash[0];
    salt[1] = yourhash[1];
    salt[2] = '\0';



    //Block 4 / Char 5
    for (i = -1; i < 53; i++)
    {

        if (counter > 3)
        {
            if (i > 51)
            {
                counter = 5;
                break;
            }
            if (i < 26)
            {
                cracked[4] = ('A' + i);
            }
            if (i > 25 && i < 52)
            {
                cracked[4] = ('a' + (i % 26));
            }
        }
        //Block 3 / Char 4
        for (j = -1; j < 53; j++)
        {
            if (counter > 2)
            {
                if (j > 51)
                {
                    counter = 4;
                    break;
                }
                if (j < 26)
                {
                    cracked[3] = ('A' + j);
                }
                if (j > 25 && j < 52)
                {
                    cracked[3] = ('a' + (j % 26));
                }
            }
            //Block 2 / Char 3
            for (k = -1; k < 53; k++)
            {
                if (counter > 1)
                {
                    if (k > 51)
                    {
                        counter = 3;
                        break;
                    }
                    if (k < 26)
                    {
                        cracked[2] = ('A' + k);
                    }
                    if (k > 25 && k < 52)
                    {
                        cracked[2] = ('a' + (k % 26));
                    }
                }
                //Block 1 / Char 2
                for (l = -1; l < 53; l++)
                {
                    if (counter > 0)
                    {
                        if (l > 51)
                        {
                            counter = 2;
                            break;
                        }
                        if (l < 26)
                        {
                            cracked[1] = ('A' + l);
                        }
                        if (l > 25 && l < 52)
                        {
                            cracked[1] = ('a' + (l % 26));
                        }
                    }
                    //Block 0 / Char 1
                    for (m = 0; m < 53; m++)
                    {
                        if (m > 51)
                        {
                            //If gone through alphabet, trigger parent loop.
                            counter = 1;
                            break;
                        }
                        //Try upper case first...
                        if (m < 26)
                        {
                            cracked[0] = ('A' + m);
                        }
                        //...Then move on to try lower case
                        if (m > 25 && m < 52)
                        {
                            cracked[0] = ('a' + (m % 26));
                        }

                        //Encrypt current permutation of letters
                        myhash = crypt(cracked, salt);

                        //If hashes match, exit loop.
                        if (strcmp(myhash, yourhash) == 0)
                        {
                            break;
                        }
                    }
                    if (strcmp(myhash, yourhash) == 0)
                    {
                        break;
                    }
                }
                if (strcmp(myhash, yourhash) == 0)
                {
                    break;
                }
            }
            if (strcmp(myhash, yourhash) == 0)
            {
                break;
            }
        }
        if (strcmp(myhash, yourhash) == 0)
        {
            break;
        }
    }

    //Terminate new string and print
    cracked[(counter + 4)] = '\0';
    printf("%s\n", cracked);
}