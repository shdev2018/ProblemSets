from cs50 import get_int

# check for input
while True:
    height = get_int("Height: ")
    if (height >= 0) and (height < 24):
        break

# Prepare lists
counter = 1

# Print lines
for k in range(height):
    print(' ' * (height - counter) + '#' * (counter + 1))
    counter += 1