import torch
from itertools import permutations

# device = torch.device("cpu")
# for i in range(torch.cuda.device_count()):
#     print(f"GPU: {i}: {torch.cuda.get_device_name(i)}")
# torch.cuda.is_available = lambda: False
# device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
# print("Używanie urządzenia: ", device)

print(torch.cuda.get_device_name(0))


def make_duos(sentence):
    return list(permutations(sentence.split(" "), 2))


sentence = "Mama dała bułke naspmarowanym masłem wiejskim"

print(" ".join(make_duos(sentence)[0]))
# napis = "wczoraj wieczorem spotkałem pewną wspaniałą kobietę która z pasją opowiadała o modelach językowych."

# # print(napis.split(" "))
