from cs50 import get_string

# Check input
card_number = ''
while not card_number.isdigit():
    card_number = get_string("Number: ")

# Check valid length
cardlength = len(card_number)
if not cardlength in {13, 15, 16}:
    print("INVALID")
else:
    # Convert to list
    numberlist = [int(i) for i in card_number]

    # Slice list, multiply & sum
    penultlist = ''.join([str(i * 2) for i in numberlist[-2::-2]])
    penultnumber = sum([int(i) for i in penultlist])
    ultnumber = sum(numberlist[::-2])
    checksum = penultnumber + ultnumber

    # Check checksum then cardtype criterea
    if not checksum % 10 == 0:
        print("INVALID")
    elif cardlength in {13, 16} and card_number[0] == '4':
        print("VISA")
    elif cardlength == 15 and card_number[:2] in {'34', '37'}:
        print("AMEX")
    elif cardlength == 16 and card_number[:2] in {'51', '52', '53', '54', '55'}:
        print("MASTERCARD")
    else:
        print("INVALID")