mod solution {
    pub fn range_extraction(a: &[i32]) -> String {
        let mut result = String::new();
        let mut i = 0;
        while i < a.len() {
            let range_start = i;
            while i + 2 < a.len() && a[i] + 1 == a[i+1] && a[i] + 2 == a[i+2] {
                i += 1;
            }
            if i > range_start && i + 1 < a.len() && a[i] + 1 == a[i+1] {
                result.push_str(&format!("{}-{},", a[range_start], a[i+1]));
                i += 2;
            } else if i > range_start {
                result.push_str(&format!("{}-{},", a[range_start], a[i]));
                i += 1;
            } else {
                result.push_str(&format!("{},", a[i]));
                i += 1;
            }
        }
        result.pop();
        result
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn example() {
        assert_eq!(solution::range_extraction(&[-6,-3,-2,-1,0,1,3,4,5,7,8,9,10,11,14,15,17,18,19,20]), "-6,-3-1,3-5,7-11,14,15,17-20");	
    }

    #[test]
    fn example_2() {
        assert_eq!(solution::range_extraction(&[-3,-2,-1,2,10,15,16,18,19,20]), "-3--1,2,10,15,16,18-20");
    }

    #[test]
    fn test_no_ranges() {
        assert_eq!(solution::range_extraction(&[1, 3, 5, 7]), "1,3,5,7");
    }

    #[test]
    fn test_negative_ranges() {
        assert_eq!(solution::range_extraction(&[-6, -4, -3, -2, -1]), "-6,-4--1");
    }

    #[test]
    fn test_mixed_ranges() {
        assert_eq!(solution::range_extraction(&[1, 3, 4, 5, 7, 9, 10]), "1,3-5,7,9,10");
    }
}



