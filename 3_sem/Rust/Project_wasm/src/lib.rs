mod mod_img;
use wasm_bindgen::prelude::*;
use mod_img::create_image;

#[wasm_bindgen]
pub fn generate_fractal(width: usize, height: usize, xmin: f64, xmax: f64, ymin: f64, ymax: f64) -> Vec<u8> {
    let img = create_image(width, height, xmin, xmax, ymin, ymax);

    let raw_image = img.into_raw();
    raw_image
}