mod solution {
    pub fn range_extraction(a: &[i32]) -> String {
        let (range, result) = a.iter().fold((vec![], String::new()), |(mut range, mut result), &x| {
            if let Some(&last) = range.last() {
                if last + 1 == x {
                    range.push(x);
                    (range, result)
                } else {
                    result.push_str(&format_range(&range));
                    (vec![x], result)
                }
            } else {
                (vec![x], result)
            }
        });
        result + &format_range(&range)
    }

    fn format_range(range: &[i32]) -> String {
        match range.len() {
            0 => String::new(),
            1 => format!("{},", range[0]),
            2 => format!("{},{},", range[0], range[1]),
            _ => format!("{}-{},", range[0], range[range.len()-1]),
        }
    }
}