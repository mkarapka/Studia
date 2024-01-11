mod complex_mod;
use complex_mod::Complex;
use image::{RgbaImage, Rgba};

fn mandelbrot(c: &Complex, max_iter: u32) -> u32 {
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

pub fn create_image(width: usize, height: usize) -> RgbaImage {
    let max_iter = 256;
    let xmin = -2.0;
    let xmax = 1.0;
    let ymin = -1.5;
    let ymax = 1.5;

    let mut imgbuf = RgbaImage::new(width as u32, height as u32);

    for (x, y, pixel) in imgbuf.enumerate_pixels_mut() {
        let real = xmin + (x as f32 / width as f32) * (xmax - xmin);
        let imag = ymin + (y as f32 / height as f32) * (ymax - ymin);

        let c = Complex::new(real, imag);
        let color = mandelbrot(&c, max_iter);

        let red = (color * 8 % 255) as u8;
        let green = (color * 4 % 255) as u8;
        let blue = (color * 16 % 255) as u8;
        let alpha = 255; // Pełna przezroczystość

        *pixel = Rgba([red, green, blue, alpha]);
    }

    imgbuf
}


fn main() {
    let img = create_image(800, 600);
    img.save("mandelbrot.jpg").unwrap();
}
