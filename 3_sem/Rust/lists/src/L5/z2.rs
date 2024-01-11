fn even_numbers(array: &Vec<i32>, number: usize) -> Vec<i32> {
    array.iter()
    .filter(|&x| x % 2 == 0)
    .rev()
    .take(number)
    .cloned()
    .collect::<Vec<i32>>()
    .into_iter()
    .rev()
    .collect()
}
#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn sample_tests() {
        assert_eq!(even_numbers(&vec!(1, 2, 3, 4, 5, 6, 7, 8, 9), 3), vec!(4, 6, 8));
        
    }
    #[test]
    fn sample_tests_1() {
        
        assert_eq!(even_numbers(&vec!(-22, 5, 3, 11, 26, -6, -7, -8, -9, -8, 26), 2), vec!(-8, 26));
    }
    #[test]
    fn sample_tests_2() {
        assert_eq!(even_numbers(&vec!(6, -25, 3, 7, 5, 5, 7, -3, 23), 1), vec!(6));
    }  
    #[test]
    fn sample_tests_3() {
        assert_eq!(even_numbers(&vec!(0, 1, 3, 2, 7, 9, 13, 21, 23, 27, 29, 31), 2), vec!(0, 2));
    }  
    #[test]
    fn sample_tests_4() {
        assert_eq!(even_numbers(&vec!(4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), 3), vec!(10, 12, 14));
    }     
}