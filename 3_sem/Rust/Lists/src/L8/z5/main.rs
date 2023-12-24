fn first_n_smallest(arr: &[i32], n: usize) -> Vec<i32> {
    let mut sorted = arr.to_vec();
    sorted.sort();
    let mut smallest = sorted.into_iter().take(n).collect::<Vec<_>>();
    let mut result = Vec::new();
    for &i in arr {
        if let Some(pos) = smallest.iter().position(|&x| x == i) {
            smallest.remove(pos);
            result.push(i);
        }
    }
    result
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_basic() {
        assert_eq!(first_n_smallest(&[1,2,3,4,5],3), [1,2,3]);
        assert_eq!(first_n_smallest(&[5,4,3,2,1],3), [3,2,1]);
    }
    #[test]
    fn test_basic_1() {
        assert_eq!(first_n_smallest(&[1,2,3,1,2],3), [1,2,1]);
        assert_eq!(first_n_smallest(&[1,2,3,-4,0],3), [1,-4,0]);
    }
    #[test]
    fn test_basic_2() {
        assert_eq!(first_n_smallest(&[1,2,3,4,5],0), []);
        assert_eq!(first_n_smallest(&[1,2,3,4,5],5), [1,2,3,4,5]);
    }
    #[test]
    fn test_basic_3() {
        assert_eq!(first_n_smallest(&[1,2,3,4,2],4), [1,2,3,2]);
        assert_eq!(first_n_smallest(&[2,1,2,3,4,2],2), [2,1]);
    }
    #[test]
    fn test_basic_4() {
        assert_eq!(first_n_smallest(&[2,1,2,3,4,2],3), [2,1,2]);
        assert_eq!(first_n_smallest(&[2,1,2,3,4,2],4), [2,1,2,2]);
    }

}