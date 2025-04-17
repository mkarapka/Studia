"""
    Rozwiązanie opiera się na przesukiwaniu wszerz - BFS.
    Jest zestaw funkcji, które sprawdzają stan gry i oprócz tego na kolejkę
    wrzucamy co się zmieniło na planszy i którą mamy turę. Pozycji już odwiedzonych (a więc
    tych samych stanów nie odwiedzamy powtórnie, bo mamy tablicę visited)
"""

# pos - i.e. e7
def convert_pos_to_idx(pos: str):
    col_idx = ord(pos[0]) - ord('a')
    row_idx = int(pos[1]) - 1

    return row_idx, col_idx

def convert_idx_to_pos(idx):
    row, col = idx
    return f"{chr(col + ord('a'))}{row + 1}"

# pos - (row, col)
def is_valid_pos(pos):
    row, col = pos
    if row < 8 and row >= 0 and col < 8 and col >= 0:
        return True
    return False

def king_moves(pos):
    row, col = pos

    # directions (row, col)
    directions = [(0, -1), (0, 1), (1, -1), (1, 0), (1, 1), (-1, -1), (-1, 0), (-1, 1)]

    for d_r, d_c in directions:
        new_pos = (row + d_r, col + d_c)
        if is_valid_pos(new_pos):
            yield new_pos

def rook_moves(pos, wk_pos):
    row, col = pos
    kings_row , kings_col = wk_pos[0], wk_pos[1]
    # przesunięcie na dowolny inny wiersz
    for i in range(8):
        if i != row:
            if col == kings_col:
                if row < kings_row:
                    if i < kings_row:
                        yield(i, col)
                else:
                    if i > kings_row:
                        yield(i, col) 
            else:    
                yield (i, col)
    
    # przesunięcie na dowolną inną kolumnę w tym wierszu
    for i in range(8):
        if i != col:
            if row == kings_row:
                if col < kings_col:
                    if i < kings_col:
                        yield (row, i)
                else:
                    if i > kings_col:
                        yield (row, i)
            else:
                yield (row, i)


def is_field_attacked_by_rook(rook_pos, king_pos):
    return rook_pos[0] == king_pos[0] or rook_pos[1] == king_pos[1]


def is_pos_attacked_king(pos, king):
    kx, ky = king
    x, y = pos
    return abs(kx - x) <= 1 and abs(ky - y) <= 1

def is_checkmate(white_king_pos, white_rook_pos, black_king_pos):

    # musi być atakowane to pole przez wierzę, inaczej się nie da zrobić mata
    if not is_field_attacked_by_rook(rook_pos=white_rook_pos, king_pos=black_king_pos):
        return False
    
    # jak istnieje jakikolwiek ruch, który nie wchodzi w króla, wieżę, albo atakowane przez nie pola
    # to nie ma mata (czarny król ma gdzie się ruszyć)
    for move in king_moves(black_king_pos):
        if not is_pos_attacked_king(pos=move, king=white_king_pos) and \
            move != white_king_pos and \
            move != white_rook_pos and \
            not is_field_attacked_by_rook(rook_pos=white_rook_pos, king_pos=move):
            return False
        
    return True

def solve_cooperative_checkmate(turn, initial_w_king, initial_w_rook, initial_b_king, turns_cnt=0, DEBUG=False):
    moves = []
    queue = [(turn, initial_w_king, initial_w_rook, initial_b_king, turns_cnt, moves)]
    visited = set((turn, initial_w_king, initial_w_rook, initial_b_king))

    while queue:
        turn, w_king, w_rook, b_king, turns_cnt, moves = queue.pop(0)

        if is_checkmate(white_king_pos=w_king, white_rook_pos=w_rook, black_king_pos=b_king):
            if DEBUG:
                # Konwertuj współrzędne na format szachowy i wypisz ruchy
                readable_moves = [move for move in moves]
                print("Ruchy:", readable_moves)
            return turns_cnt

        if turn == "white":
            for rook_move in rook_moves(pos=w_rook, wk_pos=w_king):
                if rook_move != w_king and rook_move != b_king and not is_pos_attacked_king(pos=rook_move, king=b_king):
                    new_state = ("black", w_king, rook_move, b_king)
                    if new_state not in visited:
                        move_desc = f"white rook {convert_idx_to_pos(w_rook)} -> {convert_idx_to_pos(rook_move)}"
                        queue.append(("black", w_king, rook_move, b_king, turns_cnt + 1, moves + [move_desc]))
                        visited.add(new_state)

            for wk_move in king_moves(pos=w_king):
                if wk_move != b_king and wk_move != w_rook and not is_pos_attacked_king(pos=wk_move, king=b_king):
                    new_state = ("black", wk_move, w_rook, b_king)
                    if new_state not in visited:
                        move_desc = f"white king {convert_idx_to_pos(w_king)} -> {convert_idx_to_pos(wk_move)}"
                        queue.append(("black", wk_move, w_rook, b_king, turns_cnt + 1, moves + [move_desc]))
                        visited.add(new_state)

        else:
            for bk_move in king_moves(pos=b_king):
                if bk_move != w_king and bk_move != w_rook and \
                   not is_pos_attacked_king(pos=bk_move, king=w_king) and \
                   not is_field_attacked_by_rook(rook_pos=w_rook, king_pos=bk_move):
                    new_state = ("white", w_king, w_rook, bk_move)
                    if new_state not in visited:
                        move_desc = f"black king {convert_idx_to_pos(b_king)} -> {convert_idx_to_pos(bk_move)}"
                        queue.append(("white", w_king, w_rook, bk_move, turns_cnt + 1, moves + [move_desc]))
                        visited.add(new_state)

    return -1  # Jeśli nie znaleziono rozwiązania

if __name__ == "__main__":
    # python validator.py zad1 python chess/chess.py
    input_path = "zad1_input.txt"
    output_path = "zad1_output.txt"

    # tuple (turn, white_king, white_rook, black_king)
    board_state = []

    with open(input_path, 'r') as file:
        for line in file:
            line = line.strip()
            board_state.append(line.split(" "))

    with open(output_path, 'w') as file:
        for turn, white_king, white_rook, black_king in board_state:
            white_king_pos = convert_pos_to_idx(white_king)
            white_rook_pos = convert_pos_to_idx(white_rook)
            black_king_pos = convert_pos_to_idx(black_king)
            turns = solve_cooperative_checkmate(turn, white_king_pos, white_rook_pos, black_king_pos, 0, True)
            file.write(str(turns) + "\n")
