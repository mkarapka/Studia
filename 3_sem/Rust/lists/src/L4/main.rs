fn number(bus_stops: &[(i32, i32)]) -> i32 {
    let mut r = 0;
    for &(enter, exit) in bus_stops {
        r = r + enter - exit;
    }
    r
}

#[test]
fn returns_expected() {
  assert_eq!(number(&[(10,0),(3,5),(5,8)]), 5);
  assert_eq!(number(&[(3,0),(9,1),(4,10),(12,2),(6,1),(7,10)]), 17);
  assert_eq!(number(&[(3,0),(9,1),(4,8),(12,2),(6,1),(7,8)]), 21);
  assert_eq!(number(&[(1,0),(2,1),(10,3),(5,2),(1,5),(2,10)]), 0);
  assert_eq!(number(&[(3,0),(9,1),(4,8),(2,2),(6,1),(10,8)]), 14);
}
fn main(){
    
}