import re
import random

def load_text(file_name):
    with open(file_name, "r", encoding="utf-8") as f:
        text = f.read()
    return text

def return_qestions_answers_explanations(text):
    blocks = re.split(r'\n(?=\d+\.)', text.strip())

    questions = []
    answers = []
    explanations = []

    for block in blocks:
        # Pytanie: pierwsza linia z podwójnym **
        q_match = re.search(r'\d+\.\s*\*\*(.*?)\*\*', block, re.DOTALL)
        # Odpowiedź: linia z **a. ...**, **b. ...** itd.
        a_match = re.search(r'\*\*([a-d]\..*?)\*\*', block)
        # Wyjaśnienie: linia zaczynająca się od "Wyjaśnienie:"
        e_match = re.search(r'Wyjaśnienie:\s*(.*)', block, re.DOTALL)
        if q_match and a_match and e_match:
            questions.append(q_match.group(1).strip())
            answers.append(a_match.group(1).strip())
            explanations.append(e_match.group(1).strip())
    return questions, answers, explanations

def return_questions_and_possible_answers(text):
    blocks = re.split(r'(?=\n?\d+\.)', text.strip())
    questions_and_answers = []

    for block in blocks:
        # Pytanie: pierwsza linia (do dwukropka lub końca linii)
        q_match = re.match(r'^(.*?):\s*', block.strip(), re.DOTALL)
        if not q_match:
            continue
        question = q_match.group(1).strip()
        # Odpowiedzi: linie zaczynające się od a., b., c., d.
        answers = re.findall(r'([a-d]\..*?)(?=\n[a-d]\.|$)', block, re.DOTALL)
        answers = [ans.replace('\n', ' ').strip().rstrip(',') for ans in answers]
        questions_and_answers.append({
            "pytanie": question,
            "odpowiedzi": answers
        })
    return questions_and_answers


def print_question_and_answers(qa):
    print(qa["pytanie"][2:])
    for odp in qa["odpowiedzi"]:
        print("-", odp)
    print()

questions = load_text("questions.txt")
solutions = load_text("solutions.txt")

def shuffle(questions, solutions):
    quest_and_answ = return_questions_and_possible_answers(questions)
    _, answ, exp = return_qestions_answers_explanations(solutions)

    combined = list(zip(quest_and_answ, list(range(1, 58))))

    random.shuffle(combined)

    quest_and_answ_shuffled, nums = zip(*combined)

    return quest_and_answ_shuffled, nums


quest_and_answ_shuffled, nums = shuffle(questions, solutions)

user_answers = []
print(len(quest_and_answ_shuffled))

print(len(nums))
with open("turn_qest.txt", "w", encoding="utf-8") as wf:
    qi = 0
    for i, qa in zip(nums, quest_and_answ_shuffled):
        print(qi)
        print(f"Zadanie {i}")
        print_question_and_answers(qa)
        usr_answ = input("Napisz litere jako odpowiedź:")
        try:
            wf.write(f"Zadanie {i} - {qa["pytanie"][2:]} \n {qa["odpowiedzi"][ord(usr_answ) - ord("a")]}\n")
        except:
            wf.write(f"Zadanie {i} - {qa["pytanie"][2:]} \n")

        wf.write(f"Odp: {usr_answ}\n")
        wf.write("\n")
        user_answers.append(usr_answ)
        qi += 1


# for i, (ans, exp) in enumerate(zip(answ_shuffled, exp_shuffled)):
#     print(f"Zadanie {i}")
#     print(quest_and_answ_shuffled[i]["pytanie"])
#     print(ans)
#     print(f"Twoja odpowiedź: {user_answers[i]}")
#     print("Wyjaśnienie:", end=" ")
#     print(exp)
#     print()

for q in quest_and_answ_shuffled:
    print(q["pytanie"])
    print(q["odpowiedzi"])
    print()
