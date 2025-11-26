import random
import re
import os

QUESTIONS_FILE = os.path.join("Questions", "2013_questions.txt")
ANSWERS_FILE = "user_answers.txt"

def parse_questions(filename):
    with open(filename, encoding="utf-8") as f:
        lines = f.readlines()
    correct_answers = load_answers(os.path.join("Questions", "2013_anwers.txt"))

    questions = []
    i = 0
    qn = 0
    while i < len(lines):
        line = lines[i].strip()
        if line.startswith("## Pytanie"):
            q_number = re.findall(r"\d+", line)
            q_number = q_number[0] if q_number else "?"
            i += 1
            # Find question text
            q_text = ""
            while i < len(lines) and not lines[i].strip().startswith("-") and not lines[i].strip().startswith("## Pytanie"):
                q_text += lines[i].strip() + " "
                i += 1
            # Find possible answers
            answers = []
            while i < len(lines) and lines[i].strip().startswith("-"):
                answers.append(lines[i].strip()[2:])
                i += 1
            questions.append({
                "number": q_number,
                "text": q_text.strip(),
                "answers": answers,
                "correct_answers": correct_answers[qn]
            })
            qn+=1
        else:
            i += 1
    return questions

def load_answers(file_name):
    with open(file_name, "r") as rf:
        lines = [l.rstrip() for l in rf.readlines()]
        answers = {}
        q = 0
        for l in lines:
            if not l.startswith("P"):
                answers[q] = [a for a in l]
                q += 1
        return answers




def ask_question(question):
    print(f"\nPytanie {question['number']}: {question['text']}")
    for idx, ans in enumerate(question['answers']):
        print(f"  {chr(65+idx)}. {ans}")
    user_ans = input("Twoja odpowiedź: ").strip().upper()
    return user_ans

def save_answer(q, user_ans):
    with open(ANSWERS_FILE, "a", encoding="utf-8") as f:
        f.write(f"Pytanie {q["number"]}:\n")
        f.write(f'{q["text"]}\n')
        f.write(f"Twoje odpowiedzi: {user_ans}\n")
        f.write("Poprawne odpowiedzi:\n")
        for i in range(4):
            f.write(f'{q["answers"][i]} - {q["correct_answers"][i]}\n')
        f.write("\n")


def main():
    with open(ANSWERS_FILE, "w") as f:
        pass
    questions = parse_questions(QUESTIONS_FILE)
    while questions != []:
        q = random.choice(questions)
        questions.remove(q)
        print(f"Zostało {len(questions)} pytań")
        user_ans = ask_question(q)
        save_answer(q, user_ans)
        cont = input("Wylosować kolejne pytanie? (enter/n): ").strip().lower()
        if cont == "n":
            break

if __name__ == "__main__":
    main()
