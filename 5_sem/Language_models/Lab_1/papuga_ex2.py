from transformers import AutoTokenizer, AutoModelForCausalLM
import torch
from itertools import permutations


def all_perms(sentece):
    return [i for i in permutations(sentece)]


# data_1 = "babuleńka miała dwa rogate koziołki"
# data_2 = "wiewiórki w parku zaczepiają przechodniów"

data_1 = ["babuleńka", "miała", "dwa", "rogate", "koziołki"]
data_2 = ["wiewiórki", "w", "parku", "zaczepiają", "przechodniów"]

model_name = "flax-community/papuGaPT2"

tokenizer = AutoTokenizer.from_pretrained(model_name)
model = AutoModelForCausalLM.from_pretrained(model_name)


def score_sentence(sentence):
    inputs = tokenizer(sentence, return_tensors="pt")
    # with torch.no_grad():
    outputs = model(**inputs, labels=inputs["input_ids"])
    loss = outputs.loss
    return loss.item()


def concat_lst(sentence):
    sentence = " ".join(sentence)
    return sentence.capitalize() + "."


def run_model(data):
    return [
        [sentence := concat_lst(sent), score_sentence(sentence)]
        for sent in all_perms(data)
    ]


def print_scores(data, cut=10):
    print(f"Przykład dla {concat_lst(data)}")
    results = run_model(data)[:cut]
    it = 1
    for score in results:
        print(f"{it}. {score[0]}: {round(score[1], 4)}")
        it += 1
    print()


# a)
print_scores(data_1)

# b)
print_scores(data_2)
