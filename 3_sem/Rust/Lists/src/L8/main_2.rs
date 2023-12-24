fn grid_to_string(grid: &Vec<Vec<u8>>) -> String {
    let rows_as_strings: Vec<String> = grid.iter()
        .map(|row| {
            let row_as_string: String = row.iter()
                .map(|&cell| if cell == 0 { '0' } else { '1' })
                .collect();
            row_as_string
        })
        .collect();
    let grid_as_string = rows_as_strings.join("\r\n");
    grid_as_string
}

fn interpreter(code: &str, iterations: usize, width: usize, height: usize) -> String {
    let mut grid = vec![vec![0; width]; height];
    let mut x = 0;
    let mut y = 0;
    let mut iter_count = 0;
    let code_chars: Vec<char> = code.chars().collect();
    let mut i = 0;
    let mut stack = Vec::new();

    while i < code_chars.len() && iter_count < iterations {
        match code_chars[i] {
            'n' => { y = if y == 0 { height - 1 } else { y - 1 }; iter_count += 1; },
            'e' => { x = (x + 1) % width; iter_count += 1; },
            's' => { y = (y + 1) % height; iter_count += 1; },
            'w' => { x = if x == 0 { width - 1 } else { x - 1 }; iter_count += 1; },
            '*' => { grid[y][x] ^= 1; iter_count += 1; },
            '[' => {
                if grid[y][x] == 0 {
                    let mut bracket_count = 1;
                    while bracket_count != 0 {
                        i += 1;
                        if code_chars[i] == '[' { bracket_count += 1; }
                        if code_chars[i] == ']' { bracket_count -= 1; }
                    }
                } else {
                    stack.push(i);
                }
                iter_count += 1;
            },
            ']' => {
                if grid[y][x] != 0 {
                    i = *stack.last().unwrap();
                } else {
                    stack.pop();
                }
                iter_count += 1;
            },
            _ => {}
        }
        i += 1;
    }

    let grid_as_string = grid_to_string(&grid);
}