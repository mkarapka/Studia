def text_stats(txt):
    letters_dict = {}
    all_let = 0
    for letter in range(ord("a"), ord("z")+1):
        letters_dict[chr(letter)] = 0

    for row in txt:
        for word in row.rstrip().split():
            for letter in word.lower():

                if ord(letter) >= ord("a") and ord(letter) <= ord("z"):
                    all_let += 1
                    letters_dict[letter] += 1

    for key in letters_dict:
        letters_dict[key] /= all_let

    return letters_dict

def possible_lang(txt, langs_lst):
    lang = text_stats(txt)
    res = [0,0,0]

    for key in lang:
        lst = [abs(lang[key] - langs_lst[i][key]) for i in range(3)]
        mini = min(lst)
        res[lst.index(mini)] += 1

    maxi = max(res)

    return chose_lang(res.index(maxi))

def chose_lang(ind):
    if ind == 0:
        return "Polski"
    if ind == 1:
        return "Hiszpański"
    return "Włoski"

with open("teksty/txt_pl.txt", "r") as txt_pl:
    with open("teksty/txt_es.txt", "r") as txt_esp:
        with open("teksty/txt_it.txt", "r") as txt_it:
            with open("testy/test_pl.txt", "r") as test_pl:
                with open("testy/test_esp.txt", "r") as test_esp:
                    with open("testy/test_it.txt", "r") as test_it:

                        pol = text_stats(txt_pl)
                        esp = text_stats(txt_esp)
                        it = text_stats(txt_it)
                        langs = [pol,esp,it]

                        # Testy

                        # Test dla polskiego tekstu
                        print(possible_lang(test_pl, langs))

                        # Test dla hiszpańskiego tekstu
                        print(possible_lang(test_esp, langs))

                        # Test dla włoskiego tekstu
                        print(possible_lang(test_it, langs))
