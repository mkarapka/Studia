import random
import re

QUESTIONS_FILE = "Questions/L_all.txt"
ANSWERS_FILE = "user_answers.txt"

def parse_questions(filename):
    with open(filename, encoding="utf-8") as f:
        lines = f.readlines()

    questions = []
    i = 0
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
                "answers": answers
            })
        else:
            i += 1
    return questions

def ask_question(question):
    print(f"\nPytanie {question['number']}: {question['text']}")
    for idx, ans in enumerate(question['answers']):
        print(f"  {chr(65+idx)}. {ans}")
    user_ans = input("Twoja odpowiedź: ").strip().upper()
    return user_ans

def save_answer(q_number, user_ans):
    with open(ANSWERS_FILE, "a", encoding="utf-8") as f:
        f.write(f"Pytanie {q_number}: {user_ans}\n")

def main():
    questions = parse_questions(QUESTIONS_FILE)
    while questions != []:
        q = random.choice(questions)
        questions.remove(q)
        user_ans = ask_question(q)
        save_answer(q["number"], user_ans)
        cont = input("Wylosować kolejne pytanie? (enter/n): ").strip().lower()
        if cont == "n":
            break

if __name__ == "__main__":
    main()
