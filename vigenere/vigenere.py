from cs50 import get_string
import sys


def main():
    # Check input
    if not len(sys.argv) == 2:
        print("usage : python vigenere.py k")
        exit(1)
    if not sys.argv[1].isalpha():
        print("usage : python vigenere.py k")
        exit(1)

    # Get inputs
    plaintext = get_string("plaintext: ")
    key = sys.argv[1].upper()

    # Calculate cyphertext
    ciphertext = []
    travkey = 0
    for i in range(len(plaintext)):
        if plaintext[i].isalpha():
            ciphertext.append(determine(plaintext[i], ord(key[travkey % len(key)]) - 65))
            travkey += 1
        else:
            ciphertext.append(plaintext[i])
    print("ciphertext: " + ''.join(ciphertext))

    exit(0)


# Function to process char
def determine(letter, key):
    if letter.isupper():
        if ord(letter) + (key % 26) <= 90:
            return chr(ord(letter) + (key % 26))
        else:
            return chr(ord(letter) + (key % 26) - 26)
    elif ord(letter) + (key % 26) <= 122:
        return chr(ord(letter) + (key % 26))
    else:
        return chr(ord(letter) + (key % 26) - 26)


if __name__ == "__main__":
    main()