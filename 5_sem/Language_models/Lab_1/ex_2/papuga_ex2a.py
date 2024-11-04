from itertools import permutations
from transformers import AutoTokenizer, AutoModelForCausalLM
import torch


def all_perms(sentece):
    return list(permutations(sentece))


# Computing loglikehood function
def score_sentence(sentence):
    inputs = tokenizer(sentence, return_tensors="pt")
    outputs = model(**inputs, labels=inputs["input_ids"])
    loss = outputs.loss
    return loss.item()


# Separating opinion from sentence
def concat_lst(sentence):
    sentence = " ".join(sentence)
    return sentence.capitalize() + "."


# Running model on formatted data
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


# data_1 = "babuleńka miała dwa rogate koziołki"
# data_2 = "wiewiórki w parku zaczepiają przechodniów"

data_1 = ["babuleńka", "miała", "dwa", "rogate", "koziołki"]
data_2 = ["wiewiórki", "w", "parku", "zaczepiają", "przechodniów"]

MODEL_NAME = "flax-community/papuGaPT2"

tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME)
model = AutoModelForCausalLM.from_pretrained(MODEL_NAME)


print(torch.cuda.get_device_name())
# a)
print_scores(data_1)

# b)
print_scores(data_2)
