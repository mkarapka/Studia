def palind_tuple(word, ind):
    if len(word) > 2 and word == word[::-1]:
        return (ind, len(word))


def all_pal(txt):
    lst = []
    for j in range(len(txt)):
        width = j + j
        for i in range(0, len(txt)-width):
            tup = palind_tuple(txt[i:i+width], i)
            if tup:
                lst.append(tup)
    return lst

def longest_pal(array):
    return max(array, key=lambda x: x[1])

tekst = "abcbadeedxyyzzyyxyxdeedacba"
print("Wszystkie krotki:", all_pal(tekst))
print("Najdłuższy palindrom:", longest_pal(all_pal(tekst)))
