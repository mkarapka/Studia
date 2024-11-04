from itertools import permutations, combinations
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


def concat_lst_b(sentence):
    index_kt = sentence.index("która")
    if index_kt > 0:
        sentence[index_kt - 1] = sentence[index_kt - 1] + ","
    return concat_lst(sentence)


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


def concat_duos(duo, capital=False):
    duo = f"{duo[0].lower()} {duo[1].lower()}"
    return duo.capitalize() if capital else duo


def return_lst_of_pairs(all_pairs):
    lst = [
        [conc := concat_duos(all_pairs[pair], capital=True), score_sentence(conc)]
        for pair in range(len(all_pairs))
    ]
    lst = sorted([item for item in lst], key=lambda x: x[1])

    return [sent for sent, _ in lst]
    # return lst


def better_pairs(sentence):
    perms = list(permutations(sentence, 2))
    return return_lst_of_pairs(perms)


def without(main, sub):
    return [item for item in main if item not in sub]


def return_sentences(sentence):
    if len(sentence) <= 1:
        return sentence
    pairs = better_pairs(sentence)


# data_1 = "babuleńka miała dwa rogate koziołki"
# data_2 = "wiewiórki w parku zaczepiają przechodniów"

data_1 = ["babuleńka", "miała", "dwa", "rogate", "koziołki"]
data_2 = ["wiewiórki", "w", "parku", "zaczepiają", "przechodniów"]
data_3 = [
    "wczoraj",
    "wieczorem",
    "spotkałem",
    "pewną",
    "wspaniałą",
    "kobietę",
    "która",
    "z",
    "pasją",
    "opowiadała",
    "o",
    "modelach",
    "językowych",
]
MODEL_NAME = "flax-community/papuGaPT2"

tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME)
model = AutoModelForCausalLM.from_pretrained(MODEL_NAME)


print(torch.cuda.get_device_name())
# a)
# print_scores(data_1)

# # b)
# print_scores(data_2)

# print(concat_lst_b(data_3))
print(return_sentences(data_1))
