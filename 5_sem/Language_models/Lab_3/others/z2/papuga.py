import torch
from transformers import AutoTokenizer, AutoModelForCausalLM
from torch.nn import functional as F
from math import exp
    

class PapugaProb:
    model_name = 'flax-community/papuGaPT2'
    device = 'cuda'
    device = 'cpu'

    tokenizer = AutoTokenizer.from_pretrained(model_name)
    model = AutoModelForCausalLM.from_pretrained(model_name).to(device)

    def log_probs_from_logits(self, logits, labels):
        logp = F.log_softmax(logits, dim=-1)
        logp_label = torch.gather(logp, 2, labels.unsqueeze(2)).squeeze(-1)
        return logp_label
    
            
    def sentence_prob(self, sentence_txt):
        input_ids = self.tokenizer(sentence_txt, return_tensors='pt')['input_ids'].to(self.device)
        with torch.no_grad():
            output = self.model(input_ids=input_ids)
            log_probs = self.log_probs_from_logits(output.logits[:, :-1, :], input_ids[:, 1:])
            seq_log_probs = torch.sum(log_probs)
        return seq_log_probs.cpu().numpy()
    
    def determine_positive_probability(self, review: str) -> float:
        # deterimine bias
        prob_pos = self.sentence_prob(review + "- pozytywna")
        prob_neg = self.sentence_prob(review + "- negatywna")

        # ile dodać do ppb negatywnego, żeby pozbyć się bias'u
        # delta = prob_pos - prob_neg
        # prob_neg += delta

        ppos, pneg = exp(prob_pos), exp(prob_neg)
        # probablility that it's positive
        prob = ppos / (ppos + pneg)
        print(prob)
        # print('positve: ', exp(prob_pos))
        # print('negative:', exp(prob_neg))

if __name__ == "__main__":
    p = PapugaProb()
    rev = 'Hotel jest położony prawie nad samym jeziorem, u jego początku. Ale było beznadziejnie.'
    p.determine_positive_probability(rev)