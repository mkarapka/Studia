import random
import re
import os
import time


class Memo:
    def __init__(self, year, result_file_name):
        self.year = year
        self.QUESTIONS_FILE = os.path.join("Questions", f"{year}_questions.txt")
        self.ANSWERS_FILE = f"{result_file_name}.txt"
        self.CORRECT_ANSWERS_FILE = os.path.join("Questions", f"{year}_answers.txt")

    def return_permutation(self):
        nums = [0, 1, 2, 3]
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
                while (
                    i < len(lines)
                    and not lines[i].strip().startswith("-")
                    and not lines[i].strip().startswith("## Pytanie")
                ):
                    q_text += lines[i].strip() + " "
                    i += 1
                # Find possible answers
                answers = []
                while i < len(lines) and lines[i].strip().startswith("-"):
                    answers.append(lines[i].strip()[2:])
                    i += 1
                questions.append(
                    {
                        "number": q_number,
                        "text": q_text.strip(),
                        "answers": answers,
                        "correct_answers": correct_answers[qn],
                        "permutation": self.return_permutation(),
                    }
                )
                qn += 1
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
            print(f"  {chr(65 + i)}. {question['answers'][question['permutation'][i]]}")
        user_ans = input("Twoja odpowiedź: ").strip().upper()
        return user_ans

    def save_answer(self, q, user_ans):
        n = 1
        with open(self.ANSWERS_FILE, "a", encoding="utf-8") as f:
            to_write = []
            f.write(f"Pytanie {q['number']}: ")
            to_write.append(f"{q['text']}\n")
            to_write.append(f"Twoje odpowiedzi: {user_ans}\n")
            to_write.append("Poprawne odpowiedzi:\n")
            for i in range(4):
                to_write.append(
                    f"{q['answers'][q['permutation'][i]]} - {q['correct_answers'][q['permutation'][i]]}\n"
                )
                if (
                    user_ans == ""
                    or user_ans[i] != q["correct_answers"][q["permutation"][i]]
                ):
                    n = 0
            if n == 0:
                f.write("- Źle")
            f.write("\n")
            for line in to_write:
                f.write(line)
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

            while len(user_ans) < 4:
                print("Odpowiedz jeszcze raz. Przykładowy format odpowiedzi: TTNT")
                user_ans = self.ask_question(q)

            correct += self.save_answer(q, user_ans)
            cont = input("Wylosować kolejne pytanie? (enter/n): ").strip().lower()
            if cont == "n":
                break
        print(f"Poprawnych {correct} na 40 = {round(correct / 40, 2) * 100}%")


if __name__ == "__main__":
    m_2013 = Memo(2013, "user_answers_2013")
    m_2019 = Memo(2019, "user_anwers_2019")
    memos = (m_2013, m_2019)

    select_year = input("Wybierz rok: 1 - 2013, 2 - 2019")

    if "1" in select_year:
        m_2013.main()
    elif "2" in select_year:
        m_2019.main()
    else:
        print("Chuj, masz losowy")
        m_rand = random.choice(memos)
        time.sleep(0.5)
        print("tiriri")
        time.sleep(0.5)
        print("tralala")
        time.sleep(0.5)
        print("Wybrany egzamin to:", m_rand.year)
        time.sleep(0.5)
        m_rand.main()
