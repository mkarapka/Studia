use std::ops;

#[derive(Copy, Clone)]
pub struct Complex{
    pub real: f32,
    pub imag: f32,
}

impl Complex{
    pub fn new(r: f32, i: f32) -> Complex{
        Complex{
            real: r,
            imag: i,
        }
    }
    
    pub fn norm(&self) -> f32{
        (self.real * self.real + self.imag * self.imag).sqrt()
    }
    // fn print(&self){
    //     println!("{} + {}i", self.real, self.imag);
    // }
}
impl ops::Add<Complex> for Complex{
    type Output = Complex;
    fn add(self, other: Complex) -> Complex{
        Complex{
            real: self.real + other.real,
            imag: self.imag + other.imag,
        }
    }
}
impl ops::Sub<Complex> for Complex{
    type Output = Complex;
    fn sub(self, other: Complex) -> Complex{
        Complex{
            real: self.real - other.real,
            imag: self.imag - other.imag,
        }
    }
}

impl ops::Mul<Complex> for Complex{
    type Output = Complex;
    fn mul(self, other: Complex) -> Complex{
        Complex{
            real: self.real * other.real - self.imag * other.imag,
            imag: self.real * other.imag + self.imag * other.real,
        }
    }
}   

impl ops::Div<Complex> for Complex{
    type Output = Complex;
    fn div(self, other: Complex) -> Complex{
        Complex{
            real: (self.real * other.real + self.imag * other.imag)/(other.real * other.real + other.imag * other.imag),
            imag: (self.imag * other.real - self.real * other.imag)/(other.real * other.real + other.imag * other.imag),
        }
    }
}









