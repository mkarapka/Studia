use image::{RgbaImage, Rgba};
use std::ops;

#[derive(Copy, Clone)]
pub struct Complex{
    pub real: f64,
    pub imag: f64,
}

impl Complex{
    pub fn new(r: f64, i: f64) -> Complex{
        Complex{
            real: r,
            imag: i,
        }
    }
    
    pub fn norm(&self) -> f64{
        (self.real * self.real + self.imag * self.imag).sqrt()
    }
    
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




fn mandelbrot(c: &Complex, max_iter: u64) -> u64 {
    let mut z = Complex::new(0.0, 0.0);
    let mut n = 0;

    while n < max_iter {
        z = z * z + *c;

        if z.norm() > 4.0 {
            break;
        }
        n += 1;
    }
    n
}

pub fn create_image(width: usize, height: usize, xmin: f64, xmax: f64, ymin: f64, ymax: f64) -> RgbaImage {
    let max_iter = 256;

    let mut imgbuf = RgbaImage::new(width as u32, height as u32);

    for y in 0..height {
        for x in 0..width {
            let real = xmin + (x as f64 / width as f64) * (xmax - xmin) ;
            let imag = ymin + (y as f64 / height as f64) * (ymax - ymin);
            
            let c = Complex::new(real, imag);
            let color = mandelbrot(&c, max_iter);
    
            let red = (color * 8 % 255) as u8;
            let green = (color * 4 % 255) as u8;
            let blue = (color * 16 % 255) as u8;
            let alpha = 255; 
    
            let pixel = imgbuf.get_pixel_mut(x as u32, y as u32);
            *pixel = Rgba([red, green, blue, alpha]);
        }
    }
    imgbuf
}
