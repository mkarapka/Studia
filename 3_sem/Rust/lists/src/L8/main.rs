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
            'n' => y = if y == 0 { height - 1 } else { y - 1 },
            'e' => x = (x + 1) % width,
            's' => y = (y + 1) % height,
            'w' => x = if x == 0 { width - 1 } else { x - 1 },
            '*' => grid[y][x] ^= 1,
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
            },
            ']' => {
                if grid[y][x] != 0 {
                    i = *stack.last().unwrap();
                } else {
                    stack.pop();
                }
            },
            _ => {}
        }
        i += 1;
        iter_count += 1;
    }

    grid.iter().map(|row| row.iter().map(|&cell| if cell == 0 { '0' } else { '1' }).collect::<String>()).collect::<Vec<_>>().join("\r\n")
}