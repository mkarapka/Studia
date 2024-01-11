fn dig_pow(n: i64, p: i32) -> i64 {
    let digits: Vec<_> = n.to_string().chars().map(|d| d.to_digit(10).unwrap() as i64).collect();
    let sum: i64 = digits.iter().enumerate().map(|(i, &d)| d.pow((p + i as i32) as u32)).sum();
    if sum % n == 0 { sum / n } else { -1 }
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn basic_tests() {
        assert_eq!(dig_pow(89, 1), 1);
        assert_eq!(dig_pow(92, 1), -1);
        
    }

    #[test]
    fn basic_tests_1() {
        assert_eq!(dig_pow(695, 2), 2);
        assert_eq!(dig_pow(46288, 3), 51);
        
    }
    #[test]
    fn basic_test_2() {
        assert_eq!(dig_pow(46288, 5), -1);
        assert_eq!(dig_pow(135, 1), 1);
    }
    #[test]
    fn basic_tests_3() {
        assert_eq!(dig_pow(89, 1), 1);
        assert_eq!(dig_pow(92, 1), -1);
        assert_eq!(dig_pow(695, 2), 2);
        assert_eq!(dig_pow(46288, 3), 51);
        assert_eq!(dig_pow(46288, 5), -1);
        assert_eq!(dig_pow(135, 1), 1);
    }
    #[test]
    fn edge_case_tests() {
        assert_eq!(dig_pow(1, 1), 1);
        assert_eq!(dig_pow(123456789, 1), -1);
    }
}
