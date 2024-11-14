import re


def main():
    card_number = input("Enter Credit-Card Number :")
    card_check(card_number)
    length_card = len(card_number)
    pattern2 = re.compile("^5[1-5]")
    pattern3 = re.compile("^3[4,7]")
    if card_number[0] == '4' and (length_card == 13 or length_card == 16):
        print("VISA")
    elif pattern2.match(card_number) and length_card == 16:
        print("MASTERCARD")
    elif pattern3.match(card_number) and length_card == 15:
        print("AMEX")
    else:
        print("INVALID")
        return 3


def card_check(card_number):

    pattern = re.compile("^[0-9]{13}|^[0-9]{15}|^[0-9]{16}$")
    while True:
        if pattern.search(card_number) == None:
            print("INVALID")
            return 1
        else:
            break
    check_for_validity(card_number)


def check_for_validity(card):
    sum1 = 0
    sum2 = 0
    length = len(card)
    for i in range(length-2, -1, -2):
        cardx2 = int(card[i])*2
        if cardx2 > 9:
            sum1 = sum1 + cardx2 % 10 + 1
        else:
            sum1 = sum1 + cardx2
    for i in range(length-1, -1, -2):
        sum2 = sum2 + int(card[i])
    if (sum1 + sum2) % 10 != 0:
        print("INVALID")
        return 2


main()
