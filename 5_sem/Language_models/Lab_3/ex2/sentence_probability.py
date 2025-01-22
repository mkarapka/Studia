import torch
from transformers import AutoTokenizer, AutoModelForCausalLM
from torch.nn import functional as F
import numpy as np

model_name = "flax-community/papuGaPT2"
device = "cuda" if torch.cuda.is_available() else "cpu"

tokenizer = AutoTokenizer.from_pretrained(model_name)
model = AutoModelForCausalLM.from_pretrained(model_name).to(device)


def log_probs_from_logits(logits, labels):
    logp = F.log_softmax(logits, dim=-1)
    logp_label = torch.gather(logp, 2, labels.unsqueeze(2)).squeeze(-1)
    return logp_label


def sentence_prob(sentence_txt):
    input_ids = tokenizer(sentence_txt, return_tensors="pt")["input_ids"].to(device)
    with torch.no_grad():
        output = model(input_ids=input_ids)
        log_probs = log_probs_from_logits(output.logits[:, :-1, :], input_ids[:, 1:])
        seq_log_probs = torch.sum(log_probs)
    return seq_log_probs.cpu().numpy()


def determitive_prob(review: str) -> float:
    pos_tag = "Ta opinia wskazuje na wysoką jakość"
    neg_tag = "Ta opinia wskazuje na niską jakość"
    prob_pos = sentence_prob(review + pos_tag)
    prob_neg = sentence_prob(review + neg_tag)

    ppos, pneg = np.exp(prob_pos), np.exp(prob_neg)
    denominator = ppos + pneg
    if denominator == 0:
        return 0.5
    return ppos / denominator
