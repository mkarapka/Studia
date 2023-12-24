from itertools import permutations

def perms(word1, word2, op, result):
    words = [list(word1), list(word2), list(result)]
    digits = [str(i) for i in range(10)]
    dict_lets = dict.fromkeys(word1 + word2 + result)
    
    permut = permutations(digits, len(dict_lets))
    for el in permut:
        i = 0
        current_dict = dict_lets.copy()

        for letter in dict_lets:
            current_dict[letter] = el[i]
            i+=1
        if set_nums(words, current_dict, op):
            yield set_nums(words, current_dict, op)

def set_nums(lst, dictionary, op):
    converted_words = []
    
    def conv(arr):
        return int("".join(arr))

    for word in lst:
        if dictionary[word[0]] == '0':
            return None  
        converted_word = [dictionary[l] for l in word]
        converted_words.append(conv(converted_word))

    if (fun(op))(converted_words[0], converted_words[1]) == converted_words[-1]:
        return converted_words

def fun(op):
    if op == '+':
        return lambda x, y: x + y
    elif op == '-':
        return lambda x, y: x - y
    elif op == '*':
        return lambda x, y: x * y
    elif op == '/':
        return lambda x, y: x // y

# Przykład użycia
p = perms("ROZUM", "DUŻO", '-', "MOŻE")

for i in p:
    print(i)
