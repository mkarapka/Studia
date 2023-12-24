from itertools import permutations

def perms(word1, word2, op, result):
    words = [list(word1), list(word2), list(result)]
    digits = [str(i) for i in range(10)]
    dict_lets = dict.fromkeys(word1 + word2 + result)
    
    permuts = permutations(digits, len(dict_lets))
    for perm in permuts:
        tmp_words = words.copy()

        for letter, digit in zip(dict_lets, perm):
            dict_lets[letter] = digit
            
        if set_nums(tmp_words, dict_lets, op):
            yield set_nums(tmp_words, dict_lets, op)
            
def set_nums(lst, dictionary, op):
    def conv(array):
        return int("".join(array))
    
    def fun(op):
        if op == '+':
            return lambda x,y: x + y
        if op == '-':
            return lambda x,y: x - y
        if op == '*':
            return lambda x,y: x * y
        return lambda x,y: x // y
    
    conv_words = []
    for word in lst:
        if dictionary[word[0]] == '0':
            return None  
        conv_word = [dictionary[let] for let in word]
        conv_words.append(conv(conv_word))
          
    if (fun(op))(conv_words[0], conv_words[1]) == conv_words[-1]:
        return conv_words
    
count = 0       
def print_answer(generator):
    global count
    count += 1
    print(f'test nr {count}')
    
    for i in generator:
        print(i)      
                       
intput1 = perms("KIOTO", "OSAKA", '+', "TOKIO")
intput2 = perms("ROZUM", "DUŻO", '-', "MOŻE")
intput3 = perms("DOM", "DOM", '*', "MIASTO")
intput4 = perms("SUDOKU", "I", '/', "REBUS")


print_answer(intput1)
print_answer(intput2)
print_answer(intput3)
print_answer(intput4)


# Inne przykłady
# intput = perms("SEND", "MORE", '+', "MONEY")
# intput = perms("ZERO", "ZERO", '+', "JEDEN")