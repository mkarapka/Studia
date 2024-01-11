fn hamming(n: usize) -> u64 {
    let mut hamming = vec![1];
    let (mut i2, mut i3, mut i5) = (0, 0, 0);
    for _ in 1..n {
        let next = *[2 * hamming[i2], 3 * hamming[i3], 5 * hamming[i5]].iter().min().unwrap();
        hamming.push(next);
        if 2 * hamming[i2] == next { i2 += 1; }
        if 3 * hamming[i3] == next { i3 += 1; }
        if 5 * hamming[i5] == next { i5 += 1; }
    }
    hamming[n - 1]
}

#[cfg(test)]
mod tests {
    use super::hamming;

    #[test]
    fn sample_tests() {
        assert_eq!(hamming(1), 1);
        assert_eq!(hamming(2), 2);
        assert_eq!(hamming(3), 3);
        assert_eq!(hamming(4), 4);
    }

    #[test]
    fn sample_tests_1() {
        assert_eq!(hamming(5), 5);
        assert_eq!(hamming(6), 6);
        assert_eq!(hamming(7), 8);
        assert_eq!(hamming(8), 9);
    }

    #[test]
    fn sample_tests_2() {
        assert_eq!(hamming(9), 10);
        assert_eq!(hamming(10), 12);
        assert_eq!(hamming(11), 15);
        assert_eq!(hamming(12), 16);
    }

    #[test]
    fn sample_tests_3() {
        assert_eq!(hamming(13), 18);
        assert_eq!(hamming(14), 20);
        assert_eq!(hamming(15), 24);
        assert_eq!(hamming(16), 25);
    }

    #[test]
    fn sample_tests_4() {
        assert_eq!(hamming(17), 27);
        assert_eq!(hamming(18), 30);
        assert_eq!(hamming(19), 32);
    }
}
