def get_input():
    try:
        h = int(input("Height: "))
    except ValueError:
        h = get_input()
    if h <= 0 or h >= 9:
        h = get_input()
        error = 1
    return h

h = get_input()

# Print the squares
for i in range(h, 0, -1):
    for j in range(i - 1):
        print(" ", end="")
    for j in range(i - 1, h, 1):
        print("#", end="")
    print("  ", end="")
    for j in range(i - 1, h, 1):
        print("#", end="")
    print()

