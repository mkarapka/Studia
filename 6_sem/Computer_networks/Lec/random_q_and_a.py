import random
import re
import os

class Memo:
    def __init__(self, year, result_file_name):
        self.year = year
        self.QUESTIONS_FILE = os.path.join("Questions", f"{year}_questions.txt")
        self.ANSWERS_FILE = f"{result_file_name}.txt"
        self.CORRECT_ANSWERS_FILE = os.path.join("Questions", f"{year}_answers.txt")

    def return_permutation(self):
        nums = [0,1,2,3]
        random.shuffle(nums)
        return nums

    def parse_questions(self, filename):
        with open(filename, encoding="utf-8") as f:
            lines = f.readlines()
        correct_answers = self.load_answers(self.CORRECT_ANSWERS_FILE)

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
                    "correct_answers": correct_answers[qn],
                    "permutation": self.return_permutation()
                })
                qn+=1
            else:
                i += 1
        return questions

    def load_answers(self, file_name):
        with open(file_name, "r") as rf:
            lines = [l.rstrip() for l in rf.readlines()]
            answers = {}
            q = 0
            for l in lines:
                if not l.startswith("P"):
                    answers[q] = [a for a in l]
                    q += 1
            return answers




    def ask_question(self, question):
        print(f"\nPytanie {question['number']}: {question['text']}")
        for i in range(len(question["permutation"])):
            print(f"  {chr(65+i)}. {question["answers"][question["permutation"][i]]}")
        user_ans = input("Twoja odpowiedź: ").strip().upper()
        return user_ans

    def save_answer(self, q, user_ans):
        n = 1
        with open(self.ANSWERS_FILE, "a", encoding="utf-8") as f:
            f.write(f"Pytanie {q["number"]}:\n")
            f.write(f'{q["text"]}\n')
            f.write(f"Twoje odpowiedzi: {user_ans}\n")
            f.write("Poprawne odpowiedzi:\n")
            for i in range(4):
                f.write(f'{q["answers"][q["permutation"][i]]} - {q["correct_answers"][q["permutation"][i]]}\n')
                if user_ans == "" or user_ans[i] != q["correct_answers"][q["permutation"][i]]:
                    n = 0

            f.write("\n")
        return n

    def main(self):
        with open(self.ANSWERS_FILE, "w") as f:
            pass
        questions = self.parse_questions(self.QUESTIONS_FILE)
        correct = 0
        while questions != []:
            q = random.choice(questions)
            print(f"Zostało {len(questions)} pytań")
            questions.remove(q)
            user_ans = self.ask_question(q)
            correct += self.save_answer(q, user_ans)
            cont = input("Wylosować kolejne pytanie? (enter/n): ").strip().lower()
            if cont == "n":
                break
        print(f"Poprawnych {correct} na 40 = {round(correct / 40, 2)*100}%")
