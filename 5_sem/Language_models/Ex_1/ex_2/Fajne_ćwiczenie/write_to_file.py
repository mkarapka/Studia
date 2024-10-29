with open("quest.txt", "r") as read_file:
    with open("answ.txt", "r+") as write_file:
        # Formatowanie danych (usuwanie '\n')
        read_lines = [line.rstrip() for line in read_file.readlines()]
        write_lines = [line.rstrip() for line in write_file.readlines()]

        answ_nums = [int(line.split("-")[-1]) - 1 for line in read_lines]
        answ = [write_lines[num] for num in answ_nums]

        # Ustawienie wskaźnika na początek pliku
        write_file.seek(0)
        for word in answ:
            write_file.write(word + "\n")

        # Ucięcie reszty pliku
        write_file.truncate()
        print(answ)
