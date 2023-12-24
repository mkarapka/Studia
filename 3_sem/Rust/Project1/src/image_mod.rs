use std::fs::File;
use std::io::Write;

pub struct Image {
    width: usize,
    height: usize,
    data: Vec<u8>,
}

impl Image {
    pub fn new(wi: usize, he: usize) -> Image {
        Image {
            width: wi,
            height: he,
            data: vec![0; wi * he * 3],
        }
    }

    pub fn set_color(&mut self, x: usize, y: usize, red: u8, green: u8, blue: u8) {
        let index = (y * self.width + x) * 3;
        self.data[index] = red;
        self.data[index + 1] = green;
        self.data[index + 2] = blue;
    }

    pub fn save_to_file(&self, filename: &str) -> std::io::Result<()> {
        let mut file = File::create(filename)?;
        file.write_all(format!("P6\n{} {}\n255\n", self.width, self.height).as_bytes())?;
        file.write_all(&self.data)?;
        Ok(())
    }
}


