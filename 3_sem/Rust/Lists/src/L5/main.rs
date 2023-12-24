fn count_odd_pentafib(n: u16) -> u16 {
    let arr = [0, 1, 1, 0, 0, 0];
    match n {
        0 => 0,
        1 | 2 | 3 | 4 | 5 => 1,
        _ => {
            fib_loop(6, n, arr, 1)
        }
    }
}

fn fib_loop(i: u16, n: u16, mut arr: [u16; 6], sm: u16) -> u16 {
    
    let current = (i % 6) as usize;
    let prev = ((i - 1) % 6) as usize;
    let exp: i32 = (2 * (arr[prev] as i32) - (arr[current] as i32)).abs();
   
    arr[current] = if exp % 2 != 0 {1} else {0};
    if i == n+1 {return sm;}
    fib_loop(i + 1, n, arr, sm + arr[current])
}

#[cfg(test)]
mod tests {
    use super::count_odd_pentafib;

    #[test]
    fn basic_tests() {
        assert_eq!(count_odd_pentafib(5), 1);
    }
    
    #[test]
    fn edge_cases() {
        assert_eq!(count_odd_pentafib(0), 0);
        assert_eq!(count_odd_pentafib(1), 1);
        assert_eq!(count_odd_pentafib(2), 1);
    }

    #[test]
    fn basic_tests_1() {
        assert_eq!(count_odd_pentafib(10), 3);
    }
    
    
    #[test]
    fn basic_tests_2() {
        assert_eq!(count_odd_pentafib(15), 5);
    }

    #[test]
    fn basic_tests_3() {
        assert_eq!(count_odd_pentafib(45), 15);
        assert_eq!(count_odd_pentafib(68), 23);
    }
}
fn main(){
    
}