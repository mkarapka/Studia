with open("reviews_for_task3.txt", "r") as file:
    lines = file.readlines()
    from sentence_probability import sentence_prob

    def concat_lst(sentence):
        sentence = " ".join(sentence)
        return sentence.capitalize() + "."

    # a = "Polecam"
    # b = "Nie polecam"

    # a = "To była pozytywna opinia"
    # b = "To była negatywna opinia"

    a = "To był przykład pozytywnej opinii"
    b = "To był przykład negatywnej opinii"

    a = "ta opinia wskazuje na wysoką jakość"
    b = "ta opinia wskazuje na niską jakość"

    # a = "Podsumowując, polecam"
    # b = "Podsumowując, nie polecam"

    sentences = [
        f"Lokalizacja w centrum - przy głównym deptaku, po sąsiedzku Biedronka : ) MINUSYDługie schody do pokonania ( od wejścia głównego hotelu do recepcji ). {a}.",
        f"Lokalizacja w centrum - przy głównym deptaku, po sąsiedzku Biedronka : ) MINUSYDługie schody do pokonania ( od wejścia głównego hotelu do recepcji ). {b}.",
    ]

    choices = [f" {a}.", f" {b}."]

    # print()
    # for s in sentences:
    #     print(s, sentence_prob(s))

    opinions = []
    for line in lines:
        word = ""
        if line.startswith("GOOD"):
            splited = line.rstrip().split("GOOD")
            word = "GOOD"
        else:
            splited = line.rstrip().split("BAD")
            word = "BAD"
        opinions.append([word, splited[1][1:]])

    # print(opinions[0])
    # print(opinions[-1])

    corrects = 0
    misses = 0
    lst_of_misses = []
    for op, sentence in opinions:

        var_good = sentence + choices[0]
        var_bad = sentence + choices[1]

        prob_var_good = sentence_prob(var_good)
        prob_var_bad = sentence_prob(var_bad)
        if op == "GOOD":
            if prob_var_good > prob_var_bad:
                corrects += 1
            else:
                misses += 1
                lst_of_misses.append(
                    [[var_good, prob_var_good], [var_bad, prob_var_bad]]
                )
        else:
            if prob_var_bad > prob_var_good:
                corrects += 1
            else:
                misses += 1
                lst_of_misses.append(
                    [[var_good, prob_var_good], [var_bad, prob_var_bad]]
                )

    print(
        f"Skuteczność: {corrects}/{corrects+misses} = {round(corrects/(corrects+misses),4)}"
    )
    # print(lst_of_misses)
