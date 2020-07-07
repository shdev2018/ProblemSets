from cs50 import get_float

# Check input
while True:
    change = get_float("Change owed: ")
    if change >= 0:
        break

# Convert to cents
cents = round(change, 2) * 100

# Find components
quarters = int(cents / 25)
dimes = int((cents % 25) / 10)
nickles = int(((cents % 25) % 10) / 5)
pennies = int(((cents % 25) % 10) % 5)

# Print result
print(quarters + dimes + nickles + pennies)