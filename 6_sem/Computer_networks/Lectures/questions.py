import os
import random
import copy

def load_questions_from_file(file_name):
    with open("Questions/" + file_name, "r", encoding="utf-8") as read_file:
        lines = [l.rstrip() for l in read_file.readlines()]
        return file_name, lines

def load_questions_from_all_files(files):
    dict = {}

    for fn in files:
        name, quetions = load_questions_from_file(fn)
        dict[name] = quetions

    return dict

def is_all_empty(d):
    for v in d.values():
        if v != []:
            return False
    return True

def pick_lecture(d, prefix):
    for k in d.keys():
        if k.startswith(prefix):
            return k
    return None

def search_for_files_with_questions(dir):
    files = os.listdir(dir)
    return [f for f in files if ".txt" in f and "L" in f]


FILES = search_for_files_with_questions("Questions")

print(FILES)


d = load_questions_from_all_files(FILES)

certain_lecture = False
user = input("Certain lecture - 1 or all - 2?. Pick 1 or 2.")
lecture = ""
if user.startswith("1"):
    certain_lecture = True
    user = input("Write L and number of Lecture:")
    lecture = pick_lecture(d, user)
    print(lecture)

d_cp = copy.deepcopy(d)
ans = []
while True:
    if not certain_lecture:
        lecture = random.choice(FILES)

    quest = random.choice(d[lecture])
    print(len(d[lecture]), "questions remain")
    print(d_cp[lecture].index(quest) + 1, end=". ")
    d[lecture].remove(quest)
    print(quest)
    user = input("Enter to see next question")
    if user != "":
        ans.append(user)
    print()
    if not certain_lecture:
        if is_all_empty(d):
            break
    else:
        if d[lecture] == []:
            break

def conv_lst(lst):
    new_lst = []
    for num in lst:
        conv = ""
        for d in num:
            if d in "0123456789":
                conv += d
            else:
                break
        if conv.strip() != "":
            new_lst.append(int(conv))
    return new_lst

with open("answ.txt", "w") as wf:
    wf.write(", ".join(ans))
