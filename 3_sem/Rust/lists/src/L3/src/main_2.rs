fn number(bus_stops:&[(i32,i32)]) -> i32 {
    let mut r = 0;
    for res in bus_stops{
        r = r + bus_stops[0] - bus_stops[1];
    }
    
}
fn main(){
    
}