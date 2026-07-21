from cs50 import get_string

def main():
    text = get_string("Text: ")
    l = 0
    w = 0
    s = 0
    for i in text:
        if i.isalpha():
            l += 1

            if w == 0:
                w += 1

        if i == " ":
            w += 1

        if i == "." or i == "!" or i == "?":
            s += 1

    L = (l / w) * 100
    S = (s / w) * 100

    grade = round(0.0588 * L - 0.296 * S - 15.8)

    if grade >= 1 and grade < 16:
        print(f"Grade {grade}")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print("Grade 16+")


if __name__ == "__main__":
    main()
