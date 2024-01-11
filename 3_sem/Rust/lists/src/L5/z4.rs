fn expanded_form(n: u64) -> String {
   
    fn expand(c: char, x: usize) -> String {
        println!("{} {}", x, c);
        if c != '0' {
            c.to_string() + &"0".repeat(x)
        } else {
            String::new()
        }
    }

    let mut x = n.to_string().len();
    n.to_string()
        .chars()
        .map(|c| {
            x -= 1;
            let result = expand(c, x);
            result
        })
        .filter(|c| !c.is_empty())
        .collect::<Vec<String>>()
        .join(" + ")
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn examples() {
        assert_eq!(expanded_form(12), "10 + 2");
        
    }
    #[test]
    fn examples_1() {
        assert_eq!(expanded_form(42), "40 + 2");
    }
    #[test]
    fn examples_2() {
        assert_eq!(expanded_form(70304), "70000 + 300 + 4");
    }
    #[test]
    fn examples_3() {
        assert_eq!(expanded_form(1), "1");
    }
    #[test]
    fn examples_4() {
        assert_eq!(expanded_form(10234), "10000 + 200 + 30 + 4");
    }
}

// fn main() {
//     println!("{}", expanded_form(10234));
// }



