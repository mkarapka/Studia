import chess
import queue
# Load the first game
# Iterate through the moves of the game outputting the board.
board = chess.Board("8/8/8/8/4R3/1k2K3/8/8 w - - 0 1")
board.turn = chess.BLACK
print(board)
move = chess.Move.from_uci("b3b2")
board.push(move)
print(board)

def BFS(G, queue, state):
    while queue.size() > 0:
        v = queue.pop()
        if not G.visited():
            G.visit(v)
            G[G.visited(v)] = True
            for w in G.neighbors(v):
                if not G.visited(w):
                    queue.append(w)

class BoardGraph:
    def __init__(self, state):
        self.visited = dict()
        self.neighbors = dict()
        self.state = state # wk, wr, bk
        self.rows = 8
        self.columns = "abcdefgh"
        
    def legal_moves(self):
        positions = dict()
        
        # Black king
        self.state[-1][0] > "a"
        
        
        





# class Game:
#     def __init__(self, positions , turn):
        

#     def move(self, pos1, pos2):
#         pass

      

#     def pick_figure(self):
#         pass