from polka_generator import PolkaGenerator
import random

FILENAME = "prefiksy.txt"


def sample_text_lines(num_samples=3):
    with open(FILENAME, "r", encoding="utf-8") as file:
        lines = [line.strip().lower() for line in file if line.strip()]
    return random.sample(lines, num_samples)


if __name__ == "__main__":
    polka = PolkaGenerator()
    prompts = sample_text_lines(3)  # Pobieramy 3 prefiksy
    with open("output.txt", "w", encoding="utf-8") as file:
        for prompt in prompts:
            best_variant = polka.find_best_variant(5, prompt)
            file.write(f"{prompt}\n{best_variant}\n")
