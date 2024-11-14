from cs50 import get_int


while True:
    height = get_int("height: ")
    if height < 9 and height > 0:
        break


for i in range(height):
    x = "#" * (i + 1)
    y = " " * (height - i - 1)
    print(f"{y}{x}  {x}")
