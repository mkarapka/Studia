import random
numbers = [i for i in range(1, 41)]

print(numbers)
answers = []
for _ in range(40):
    n = random.choice(numbers)
    numbers.remove(n)
    print(f"Answer nr {n}")
    user = input("Press enter to move another question")
    answers.append([n, user])

with open("answ.txt", "w") as wf:
    for n, ans in answers:
        wf.write(f"Q: {n}\n")
        wf.write(f"ans: {ans}\n")
