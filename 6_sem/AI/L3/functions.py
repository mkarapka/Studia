def generate_sensible_block_moves_combinations(last_index, blocks, max_free_space):
    def generate_all_possible_moves_from_that_position(
        start_position, end_position, remaining_free_space
    ):
        moves = []
        if len(blocks) > 1:
            sub_moves = generate_sensible_block_moves_combinations(
                end_position + 2, blocks[1:], remaining_free_space
            )
            for sub_move in sub_moves:
                moves.append([(start_position, end_position)] + sub_move)
        else:
            moves.append([(start_position, end_position)])
        return moves

    moves = []
    if not blocks:
        return []

    current_block = blocks[0]
    steps = [0, max_free_space] if max_free_space > 0 else [0]

    for s in steps:
        start_position = last_index + s
        end_position = start_position + current_block - 1

        moves.extend(
            generate_all_possible_moves_from_that_position(
                start_position, end_position, max_free_space - s
            )
        )
    return moves


def find_cells_which_are_in_every_combination(combinations_of_cells, sure_filled, line):
    amount_of_combinations = len(combinations_of_cells)
    for comb in combinations_of_cells:
        for st, end in comb:
            for i in range(st, end + 1):
                sure_filled[i] += 1
                if line[i] == 'X':
                    for j in range(st, end + 1):
                        sure_filled[j] = -1
                    break
    return [i for i, c in enumerate(sure_filled) if c == amount_of_combinations]
