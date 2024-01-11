fn string_to_num(a: &str) -> i32 {
    let result = a.parse().unwrap();
    return result;
}

#[cfg(test)]
mod tests {
    use super::string_to_num;
    #[test]
    fn test_string_to_num() {
        assert_eq!(string_to_num("1234"), 1234);
    }

    #[test]
    fn test_string_to_num_2() {
        assert_eq!(string_to_num("605"), 605);
    }

    #[test]
    fn test_string_to_num_3() {
        assert_eq!(string_to_num("1405"), 1405);
    }

    #[test]
    fn test_string_to_num_4() {
        assert_eq!(string_to_num("-7"), -7);
    }

}
fn main() {


}

