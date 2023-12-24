def is_palindrom(text):
    txt = ""
    for letter in text:
        if ord(letter) < ord(" ") or ord(letter) > ord("/"):
            if ord(letter) < ord(":") or ord(letter) > ord("@"):
                if ord(letter) < ord("[") or ord(letter) > ord("`"):
                    if ord(letter) < ord("{") or ord(letter) > ord("~"):
                        txt += letter.lower()
    # print(txt)
    for i in range(len(txt)//2):
        if txt[i] != txt[-1 - i]:
            return False
    return True

print(is_palindrom("Eine güldne, gute Tugend: Lüge nie!"))
print(is_palindrom("Míč omočím."))
