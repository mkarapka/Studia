fn part_list(arr: Vec<&str>) -> String {
    (1..arr.len())
        .map(|i| format!("({}, {})", arr[0..i].join(" "), arr[i..].join(" ")))
        .collect::<Vec<_>>()
        .join("")
}

#[cfg(test)]
    mod tests {
    use super::*;

    fn dotest(arr: Vec<&str>, exp: &str) -> () {
        println!("arr: {:?}", arr);
        let ans = part_list(arr);
        println!("actual:\n{}", ans);
        println!("expect:\n{}", exp);
        println!("{}", ans == exp);
        assert_eq!(ans, exp);
        println!("{}", "-");
    }

    #[test]
    fn basis_test() {
        dotest(vec!["I", "wish", "I", "hadn't", "come"],
                "(I, wish I hadn't come)(I wish, I hadn't come)(I wish I, hadn't come)(I wish I hadn't, come)");
    }

    #[test]
    fn basis_test_1() {
        dotest(vec!["cdIw", "tzIy", "xDu", "rThG"], 
            "(cdIw, tzIy xDu rThG)(cdIw tzIy, xDu rThG)(cdIw tzIy xDu, rThG)");
        
    }

    #[test]
    fn basis_test_2() {
        dotest(vec!["one", "two", "three", "four", "five"],
            "(one, two three four five)(one two, three four five)(one two three, four five)(one two three four, five)");
    }

    #[test]
    fn basis_test_3() {
        dotest(vec!["apple", "banana", "cherry"],
            "(apple, banana cherry)(apple banana, cherry)");
    }

    #[test]
    fn basis_test_4() {
        dotest(vec!["a", "b", "c", "d", "e", "f"],
            "(a, b c d e f)(a b, c d e f)(a b c, d e f)(a b c d, e f)(a b c d e, f)");
    }
}

