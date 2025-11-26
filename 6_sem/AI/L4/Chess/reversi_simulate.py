import random

from tqdm import tqdm
from validator.ai_dueler_2023 import Reversi
from reversi_agent import Reversi_Agent, Random_Reasoner, Alpha_Beta_Reasoner, MCTSReasoner, material_advantage, positional_heuristic, combined_heuristic

# def check_board(board1, board2):
#     flat_b1 = [elem for row in board1 for elem in row]
#     flat_b2 = [elem for row in board2 for elem in row]

#     return str(flat_b1) != str(flat_b2)

num_simulations = 100

# reasoning_agent = Reversi_Agent(Alpha_Beta_Reasoner(combined_heuristic, 3))
reasoning_agent = Reversi_Agent(MCTSReasoner(time_limit=1.0))
random_agent = Reversi_Agent(Random_Reasoner())

game = Reversi()

results = {
    "reasoning": 0,
    "random": 0,
    "tie": 0
}

for i in tqdm(range(num_simulations)):
    turn = 0
    starting_player = random.choice(["reasoning", "random"])
    starting_players_turn = 0 if starting_player == "reasoning" else 1
    reasoning_agent.set_player(starting_players_turn)
    random_agent.set_player((1 - starting_players_turn))

    while not game.terminal():
        move = None

        if turn % 2 == starting_players_turn:
            move = reasoning_agent.make_move()
            random_agent.update(move)
        else:
            move = random_agent.make_move()
            reasoning_agent.update(move)
        
        game.do_move(move, turn % 2)

        turn += 1

    if game.result() < 0:
        results[starting_player] += 1
    elif game.result() > 0:
        second_player = "random" if starting_player == "reasoning" else "reasoning"
        results[second_player] += 1
    else:
        results["tie"] += 1 

    game.reset()
    reasoning_agent.reset()
    random_agent.reset()

print(f'Reasoning wins: {results["reasoning"]}')
print(f'Random wins: {results["random"]}')
print(f'Ties: {results["tie"]}')