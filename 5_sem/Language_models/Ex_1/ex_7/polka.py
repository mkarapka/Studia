from transformers import AutoTokenizer, AutoModelForCausalLM, pipeline

MODEL_NAME = "eryk-mazus/polka-1.1b"
# Załaduj tokenizer i model Polka
tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME)
model = AutoModelForCausalLM.from_pretrained(MODEL_NAME)

# Stwórz pipeline do generacji tekstu
text_generator = pipeline("text-generation", model=model, tokenizer=tokenizer)

# Użycie modelu do generacji tekstu
input_text = "Polska jest"
output = text_generator(input_text, max_length=50, num_return_sequences=1)

# Wyświetl wygenerowany tekst
print(output[0]["generated_text"])
