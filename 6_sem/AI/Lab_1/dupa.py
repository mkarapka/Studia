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

for square, piece in board.piece_map().items():
    print(chess.square_name(square), piece)