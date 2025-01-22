from transformers import AutoTokenizer, AutoModel
import torch

class HerbertDistance:

    model_name = "allegro/herbert-base-cased"
    device = 'cpu'

    tokenizer = AutoTokenizer.from_pretrained(model_name)
    model = AutoModel.from_pretrained(model_name).to(device)

    def __init__(self):
        # self.positive_words = [
        #     "doskonały", "wspaniały", "piękny", "świetny", "znakomity", "komfortowy", 
        #     "pomocny", "uprzejmy", "przyjemny", "czysty", "nowoczesny", "smaczny", 
        #     "malowniczy", "klimatyczny", "zadbany", "solidny", "estetyczny", "profesjonalny", "pozytywna", 
        #     "pozytywnie", "pozytywny"
        # ]
        self.positive_words = ["pozytywna", "pozytywny", "pozytywnie"]

    def cosine_similarity(self, u, v):
        dot_product = torch.dot(u, v)

        u_norm = torch.norm(u)
        v_norm = torch.norm(v)

        return dot_product / (u_norm * v_norm + 1e-9) # dodajemy epsilon, żeby nie było dzzielenie przez 0

    def euclidean_distance(self, u, v):
        return torch.norm(u - v)
    
    def calculate_words_embeding(self):
        token_ids = self.tokenizer(" ".join(self.positive_words), return_tensors='pt')['input_ids'][0]

        # tokens = [self.tokenizer.decode(idx) for idx in token_ids]
        outputs = self.model(token_ids.unsqueeze(0))
        
        embeddings = outputs.last_hidden_state[0][1:-1]
        return torch.sum(embeddings, dim=0) # obliczamy sumę po współrzędnych

    def calculate_sentence_embeding(self, sentence: str):
        token_ids = self.tokenizer(sentence, return_tensors='pt')['input_ids'][0]

        tokens = [self.tokenizer.decode(idx) for idx in token_ids]
        outputs = self.model(token_ids.unsqueeze(0))
        
        embeddings = outputs.last_hidden_state[0][0]

        # for token, embedding in zip(tokens, embeddings):
        #     print(f"\nToken: '{token}'")
        #     print(f"Embedding: {embedding}")

        return embeddings

    def get_distance_to_positive_words(self, review: str):
        words_embeding = self.calculate_words_embeding()

        review_embeding = self.calculate_sentence_embeding(review)

        similarity = self.euclidean_distance(review_embeding, words_embeding)
        print(f"Distance: {similarity.item()}")
        return similarity.item()

        


        

if __name__ == "__main__":
    p = HerbertDistance()
    # rev = 'Hotel jest położony prawie nad samym jeziorem, u jego początku. Ale było beznadziejnie.'
    # Distance: 9.232253074645996 <- pozywyne 573.91845703125
    rev = "Hotel był piękny, wszędzie czysto."
    p.get_distance_to_positive_words(rev)