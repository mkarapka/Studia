use std::collections::HashMap;

fn sum_pairs(ints: &[i32], s: i32) -> Option<(i32, i32)> {
    let mut seen = HashMap::new();
    for &i in ints {
        if let Some(&val) = seen.get(&(s - i)) {
            return Some((val, i));
        }
        seen.insert(i, i);
    }
    None
}
#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn sample_tests() {
        let l1 = [1, 4, 8, 7, 3, 15];
        assert_eq!(sum_pairs(&l1, 8), Some((1, 7)));        
    }
    #[test]
    fn sample_tests_1() {
        let l2 = [1, -2, 3, 0, -6, 1];
        assert_eq!(sum_pairs(&l2, -6), Some((0, -6)));
    }
    #[test]
    fn sample_tests_2() {
        let l3 = [20, -13, 40];
        assert_eq!(sum_pairs(&l3, -7), None);
    }  
    #[test]
    fn sample_tests_3() {
        let l4 = [1, 2, 3, 4, 1, 0];
        assert_eq!(sum_pairs(&l4, 2), Some((1, 1)));
    }  
    #[test]
    fn sample_tests_4() {
        let l7 = [0, 2, 0];
        assert_eq!(sum_pairs(&l7, 0), Some((0, 0)));
    }     
}
