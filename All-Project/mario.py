from cs50 import get_int

while True:
    height = get_int('Height: ')

    if 1 <= height <= 8:
        break

for c in range(height):
    c += 1
    print(' ' * (height - c) + '#' * c + '  ' + '#' * c)
