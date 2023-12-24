mod image_mod;  
use image_mod::Image;
mod complex_mod;
use complex_mod::Complex;

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

fn main() {
    let width = 800;
    let height = 600;
    let max_iter = 256;
    let xmin = -2.0;
    let xmax = 1.0;
    let ymin = -1.5;
    let ymax = 1.5;

    let mut image = Image::new(width, height);

    for y in 0..height {
        for x in 0..width {
            let real = xmin + (x as f32 / width as f32) * (xmax - xmin);
            let imag = ymin + (y as f32 / height as f32) * (ymax - ymin);

            let c = Complex::new(real, imag);
            let color = mandelbrot(&c, max_iter);

            
            let red = (color * 8) as u8;
            let green = (color * 4) as u8;
            let blue = (color * 16) as u8;

            image.set_color(x, y, red, green, blue);
        }
    }

    image.save_to_file("mandelbrot.ppm").unwrap();
}