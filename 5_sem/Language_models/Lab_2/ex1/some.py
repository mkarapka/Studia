import random


# Funkcja do generowania wyrażeń arytmetycznych
def generate_arithmetic_data(operation, count, min_value=0, max_value=100):
    """
    Generuje dane w postaci wyrażeń arytmetycznych i wyników.

    :param operation: Rodzaj operacji: 'add', 'subtract', 'multiply', 'divide'
    :param count: Liczba przykładów do wygenerowania
    :param min_value: Minimalna wartość operandu
    :param max_value: Maksymalna wartość operandu
    :return: Lista krotek (wyrażenie, wynik)
    """
    data = []

    for _ in range(count):
        a = random.randint(min_value, max_value)
        b = random.randint(min_value, max_value)

        if operation == "add":
            expression = f"{a} + {b} ="
            result = a + b
        elif operation == "subtract":
            expression = f"{a} - {b} ="
            result = a - b
        elif operation == "multiply":
            expression = f"{a} * {b} ="
            result = a * b
        elif operation == "divide":
            b = b if b != 0 else 1  # Unikaj dzielenia przez zero
            expression = f"{a} / {b} ="
            result = round(a / b, 2)  # Zaokrąglenie do dwóch miejsc po przecinku
        else:
            raise ValueError("Unsupported operation")

        data.append((expression, result))

    return data


# Generowanie danych dla każdej operacji
operations = ["divide"]
data = []

for operation in operations:
    data.extend(
        generate_arithmetic_data(operation, count=1000, min_value=1, max_value=100)
    )

# Zapisywanie do pliku
output_file = "arithmetic_data.txt"
with open(output_file, "w") as f:
    for expression, result in data:
        f.write(f"{expression} {result}\n")

print(f"Dane zostały zapisane w pliku {output_file}.")
