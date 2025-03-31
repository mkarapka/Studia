import gzip


def read_ai_file():
    with gzip.open("words_for_AI.gz", "rt", encoding="utf-8") as file:
        return {l.rstrip() for l in file.readlines()}


dict_words = read_ai_file()


def stupid_split(text):
    dp = [0 for _ in range(len(text) + 1)]
    prev = [0 for _ in range(len(text) + 1)]

    for i in range(len(text)):
        for e in range(i + 1, len(text) + 1):
            if text[i:e] in dict_words:
                # print(text[i:e])
                if dp[e] < len(text[i:e]) ** 2 + dp[i]:
                    dp[e] = len(text[i:e]) ** 2 + dp[i]
                    prev[e] = i

        # print(dp)
    stack = []
    i = len(prev) - 1
    while i > 0:
        # print("i=", i)
        p = prev[i]
        stack.append(text[p:i])
        i = p
    return stack


def write_line(stack, file):
    while stack:
        file.write(f"{stack.pop()} ")
    file.write("\n")


with open("zad2_input.txt", "r", encoding="utf-8") as file:
    lines = [l.rstrip() for l in file.readlines()]
    with open("zad2_output.txt", "w", encoding="utf-8") as write_file:
        for l in lines:
            stack = stupid_split(l)
            write_line(stack, write_file)

# if __name__ == "__main__":
#     test_txt = "litwoojczyznomojatyjesteśjakzdrowie"
#     print("ojczyznom" in dict_words)
#     stack = stupid_split(test_txt)

#     while stack:
#         print(stack.pop())
