with open("quest.txt", "r+") as file:
    data = [line.rstrip().split("-") for line in file.readlines()]

    file.seek(0)
    for sentence in data:
        file.write(sentence[0] + "\n")

    file.truncate()
