fn count_num(n:i64, i:i64) -> i64{
    if i == 1{
        return n;
    }
    n + count_num(n+1, i-1)
}
fn row_sum_odd_numbers(n:i64) -> i64 {
    let last = 1 + (count_num(1, n) - 1) * 2;
    (2*last + (n - 1)*(-2))*n/2
    
  }
  #[test]
  fn returns_expected() {
    assert_eq!(row_sum_odd_numbers(1), 1);
    assert_eq!(row_sum_odd_numbers(42), 74088);
    assert_eq!(row_sum_odd_numbers(4), 64);
    assert_eq!(row_sum_odd_numbers(5), 125);
    assert_eq!(row_sum_odd_numbers(6), 216);

  }
fn main() {
    
}
