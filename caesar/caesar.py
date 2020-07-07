from cs50 import get_string
import sys


def main():
    # Check input
    if not len(sys.argv) == 2:
        print("usage : python caesar.py k")
        exit(1)

    key = int(sys.argv[1])

    # Get plaintext
    plaintext = get_string("plaintext: ")

    # Calculate cyphertext
    ciphertext = []
    for i in range(len(plaintext)):
        ciphertext.append(determine(plaintext[i], key))
    print("ciphertext: " + ''.join(ciphertext))

    exit(0)


# Function to process char
def determine(letter, key):
    if letter.isalpha():
        if letter.isupper():
            if ord(letter) + (key % 26) <= 90:
                return chr(ord(letter) + (key % 26))
            else:
                return chr(ord(letter) + (key % 26) - 26)
        elif ord(letter) + (key % 26) <= 122:
            return chr(ord(letter) + (key % 26))
        else:
            return chr(ord(letter) + (key % 26) - 26)
    else:
        return letter


# End main
if __name__ == "__main__":
    main()