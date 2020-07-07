import crypt
import sys


def main():
    # Check input
    if not len(sys.argv) == 2:
        print("usage : python crack.py k")
        exit(1)

    # Get data
    yourhash = sys.argv[1]
    salt = sys.argv[1][:2]
    alpha = [""]
    cracked = ["", "", "", "", ""]

    # Alphabet list
    for i in range(26):
        alpha.append(chr(65 + i))
    for i in range(26):
        alpha.append(chr(97 + i))

    # Crack
    for i in range(53):
        cracked[4] = alpha[i]
        for j in range(53):
            cracked[3] = alpha[j]
            for k in range(53):
                cracked[2] = alpha[k]
                for l in range(53):
                    cracked[1] = alpha[l]
                    for m in range(52):
                        cracked[0] = alpha[m + 1]
                        if crypt.crypt(''.join(cracked), salt) == yourhash:
                            print(''.join(cracked))
                            exit(0)
    # Something's wrong
    exit(1)


# End main
if __name__ == "__main__":
    main()