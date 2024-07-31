text = input("Text: ")
scentence = 0
word = 1
letter = 0
for i in text:
    if i.isalpha():
        letter = letter + 1
    elif i == ' ':
        word = word + 1
    elif i == '.' or i == '?' or i == '!':
        scentence = scentence + 1

print(f"{letter},{word},{scentence}")
L = (letter/word)*100
S = (scentence/word)*100

index = (0.0588 * L) - (0.296 * S) - 15.8
index = round(index)

if index <= 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
