import random
from transformers import pipeline

# Inicjalizacja modelu (np. GPT-2)
model = pipeline("text-generation", model="gpt2", pad_token_id=50256)

random.seed(42)


# Definicja funkcji do testowania wyrażeń arytmetycznych
def test_model(prompt, true_answer):
    # Generowanie odpowiedzi modelu
    output = model(prompt, max_new_tokens=2, num_return_sequences=1)
    response = output[0]["generated_text"].split("=")[-1].strip()

    # Sprawdzenie poprawności
    # print(f'response = {response}, true_value = {true_answer}')

    try:
        model_answer = int(response)
        return model_answer == true_answer
    except ValueError as error:
        print(str(error))
        return False  # Jeśli model nie zwróci liczby


def read_pairs_from_file(filename):
    pairs = []
    with open(filename, "r") as file:
        for line in file:
            # Rozdzielenie linii na wyrażenie i wynik
            expression, result = line.strip().split(",")
            # Usunięcie ewentualnych spacji i konwersja wyniku na liczbę całkowitą
            expression = expression.strip()
            result = int(result.strip())
            # Dodanie krotki do listy
            pairs.append((expression, result))
    return pairs


# Testowanie modeli na różnych wyrażeniach
test_data_paths = [
    "data/addition_lines.txt",
    "data/substraction_lines.txt",
    "data/multiplication_lines.txt",
    "data/division_lines.txt",
]

positives = {"addition": [], "substraction": [], "multiplication": [], "division": []}

for path in test_data_paths:
    operation = path.replace("data/", "").replace("_lines.txt", "")

    data = read_pairs_from_file(path)
    random.shuffle(data)

    split_index = int(len(data) * 0.4)
    few_shot_learning_data = data[:split_index]
    examples = data[split_index:]

    few_shot_prompt = ""

    for ecuation, result in few_shot_learning_data:
        few_shot_prompt += f"{ecuation}{result}\n"

    results = []

    for expr, answer in examples:
        prompt = few_shot_prompt + expr
        result = test_model(prompt, answer)
        results.append(result)
        if result:
            positives[operation].append(expr)

    # Analiza wyników
    accuracy = sum(results) / len(results)
    print(f"Model Accuracy for {operation}:", accuracy)


print(positives["addition"])
print(positives["substraction"])
print(positives["multiplication"])
print(positives["division"])
