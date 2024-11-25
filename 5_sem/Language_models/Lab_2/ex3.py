import os

os.environ["TF_ENABLE_ONEDNN_OPTS"] = "0"
import torch
from transformers import AutoTokenizer, AutoModelForCausalLM


model_name = "flax-community/papuGaPT2"
tokenizer = AutoTokenizer.from_pretrained(model_name)
model = AutoModelForCausalLM.from_pretrained(model_name)


# Funkcja generująca warianty słów
def generate_variants(text):
    tokens = text.split()
    variants = [token.split("|") for token in tokens]
    return variants


# Funkcja oceniająca prawdopodobieństwo sekwencji słów
def sequence_log_probability(sequence):
    text = " ".join(sequence)
    inputs = tokenizer(text, return_tensors="pt")
    with torch.no_grad():
        outputs = model(**inputs, labels=inputs["input_ids"])
        log_likelihood = -outputs.loss.item() * inputs["input_ids"].size(1)
    return log_likelihood


# Funkcja wykonująca beam search
def beam_search(variants, beam_width=3):
    sequences = [([], 0.0)]

    for variant in variants:
        all_candidates = []

        for seq, score in sequences:
            for word in variant:
                candidate = (
                    seq + [word],
                    score + sequence_log_probability(seq + [word]),
                )
                all_candidates.append(candidate)

        all_candidates = sorted(all_candidates, key=lambda x: x[1], reverse=True)
        sequences = all_candidates[:beam_width]

    best_sequence = max(sequences, key=lambda x: x[1])[0]
    return " ".join(best_sequence)


text = "wprost|wyprosty|wyprostu|wyprost uwielbiała|wielbił|wielbiła|uwielbił|wielbiło|uwielbiał|uwielbiało|uwielbiały słuchać|osłuchać|słychać|usłuchać o|i|e|a|ó|ę|y|ą|u wartościach własnych|owłosionych macierzy|mocarz|macierzą|macierze|mocarza|mocarze|mocarzy|macierz"
variants = generate_variants(text)
best_sentence = beam_search(variants)
print(best_sentence)
