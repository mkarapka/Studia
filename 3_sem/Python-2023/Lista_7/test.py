with open("test.txt", "r") as f:
    fl = f.readlines()
    for i in fl:
        if "\n" in i:
            print(i)
