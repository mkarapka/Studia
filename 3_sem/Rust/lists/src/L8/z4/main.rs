
fn john(n: i32) -> Vec<i32> {
    let mut john_days = vec![0];
    let mut ann_days = vec![1];
    for i in 1..n as usize {
        john_days.push(i as i32 - ann_days[john_days[i - 1] as usize]);
        ann_days.push(i as i32 - john_days[ann_days[i - 1] as usize]);
    }
    john_days
}

fn ann(n: i32) -> Vec<i32> {
    let mut john_days = vec![0];
    let mut ann_days = vec![1];
    for i in 1..n as usize {
        john_days.push(i as i32 - ann_days[john_days[i - 1] as usize]);
        ann_days.push(i as i32 - john_days[ann_days[i - 1] as usize]);
    }
    ann_days
}

fn sum_john(n: i32) -> i32 {
    john(n).iter().sum()
}

fn sum_ann(n: i32) -> i32 {
    ann(n).iter().sum()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_john() {
        assert_eq!(john(11), vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6]);
        assert_eq!(john(14), vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6, 7, 7, 8]);
    }
    #[test]
    fn test_ann() {
        assert_eq!(ann(6), vec![1, 1, 2, 2, 3, 3]);
        assert_eq!(ann(15), vec![1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6, 7, 8, 8, 9]);
    }
    #[test]
    fn test_sum_john() {
        assert_eq!(sum_john(75), 1720);
        assert_eq!(sum_john(78), 1861);
    }
    #[test]
    fn test_sum_ann() {
        assert_eq!(sum_ann(115), 4070);
        assert_eq!(sum_ann(150), 6930);
    }

    #[test]
    fn test_john_additional() {
        assert_eq!(john(5), vec![0, 0, 1, 2, 2]);
        assert_eq!(john(10), vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6]);
    }

    #[test]
    fn test_ann_additional() {
        assert_eq!(ann(8), vec![1, 1, 2, 2, 3, 3, 4, 5]);
        assert_eq!(ann(15), vec![1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6, 7, 8, 8, 9]);
    }

    #[test]
    fn test_sum_john_additional() {
        assert_eq!(sum_john(50), 759);
        assert_eq!(sum_john(100), 3066);
    }

    #[test]
    fn test_sum_ann_additional() {
        assert_eq!(sum_ann(120), 4432);
        assert_eq!(sum_ann(160), 7886);
    }

}

