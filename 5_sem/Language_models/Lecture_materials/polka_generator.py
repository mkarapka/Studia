import torch
from transformers import AutoModelForCausalLM, AutoTokenizer
import re

device = "cuda" if torch.cuda.is_available() else "cpu"


class PolkaGenerator:
    def __init__(self):
        self.model_name = "eryk-mazus/polka-1.1b"
        self.device = "cuda" if torch.cuda.is_available() else "cpu"
        self.tokenizer = AutoTokenizer.from_pretrained(self.model_name)
        self.model = AutoModelForCausalLM.from_pretrained(self.model_name).to(
            self.device
        )

    def generate(self, prompt: str, letter: str) -> str:
        model_inputs = self.tokenizer(prompt, return_tensors="pt").to(self.device)
        biased_processor = BiasLogitsProcessor(letter, tokenizer=self.tokenizer)

        generated_ids = self.model.generate(
            model_inputs["input_ids"],
            max_length=50,  # Generujemy całe zdanie
            do_sample=True,
            top_k=10,
            top_p=0.90,
            logits_processor=[biased_processor],
        ).to(self.device)

        return self.tokenizer.decode(generated_ids[0], skip_special_tokens=True)

    def find_best_variant(self, variants_quantity: int, prefix: str) -> str:
        letter = prefix[0]
        sentences = [self.generate(prefix, letter) for _ in range(variants_quantity)]
        return max(
            sentences, key=lambda x: len(x) if self.valid_sentence(x, letter) else 0
        )

    def valid_sentence(self, sentence: str, letter: str) -> bool:
        words = re.findall(r"\b\w+\b", sentence)
        return all(word.lower().startswith(letter.lower()) for word in words)


class BiasLogitsProcessor:
    def __init__(self, letter: str, tokenizer) -> None:
        self.letter = letter
        self.tokenizer = tokenizer

    def __call__(self, input_ids, logits):
        logits = logits.to(device)
        vocab_size = logits.shape[-1]
        all_tokens = [self.tokenizer.decode(i) for i in range(vocab_size)]
        mask = torch.tensor(
            [1.0 if token.startswith(self.letter) else 0.0 for token in all_tokens]
        ).to(device)
        logits += mask * 5.0  # Dodajemy większe wzmocnienie dla odpowiednich liter
        return logits
