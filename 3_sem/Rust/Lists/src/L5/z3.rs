fn reverse_words(str: &str) -> String {
    str.split(' ')
       .map(|word| 
        if word != "" { word.chars()
       .rev().collect::<String>()}

        else { word.to_string() })
       .collect::<Vec<String>>()
       .join(" ")
}
#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn sample_tests() {
        assert_eq!(reverse_words("The quick brown fox jumps over the lazy dog."), "ehT kciuq nworb xof spmuj revo eht yzal .god");
        
    }
    #[test]
    fn sample_tests_1() {
        
        assert_eq!(reverse_words("apple"), "elppa");
    }
    #[test]
    fn sample_tests_2() {
        assert_eq!(reverse_words("a b c d"),"a b c d");
    }  
    #[test]
    fn sample_tests_3() {
        assert_eq!(reverse_words("double  spaced  words"), "elbuod  decaps  sdrow");
    }  
    #[test]
    fn sample_tests_4() {
        assert_eq!(reverse_words("programming in        Rust"), "gnimmargorp ni        tsuR");
    }     
}