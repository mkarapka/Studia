from itertools import permutations, combinations


def concat_duos(duo, capital=False):
    duo = f"{duo[0].lower()} {duo[1].lower()}"
    return duo.capitalize() if capital else duo


def score_sentence(sentence):
    inputs = tokenizer(sentence, return_tensors="pt")
    outputs = model(**inputs, labels=inputs["input_ids"])
    loss = outputs.loss
    return loss.item()


def return_lst_of_pairs(all_pairs, length):
    lst = [
        [conc := concat_duos(all_pairs[pair], capital=True), score_sentence(conc)]
        for pair in range(len(all_pairs))
    ]
    lst = sorted(
        [item for item in lst if len(item[0].split(" ")) == length], key=lambda x: x[1]
    )

    lst = [sent for sent, _ in lst]
    return lst


def better_pairs(sentence, length):
    # Create combinations of words without repetition
    combs = combinations(sentence, 2)
    # Generate permutations for each combination
    perms = [perm for comb in combs for perm in permutations(comb)]
    return return_lst_of_pairs(perms, length)


# Example usage
data = ["babuleńka", "miała", "dwa", "rogate", "koziołki"]
length = 2

# This should call your return_lst_of_pairs with the generated perms
result = better_pairs(data, length)
print(result)
