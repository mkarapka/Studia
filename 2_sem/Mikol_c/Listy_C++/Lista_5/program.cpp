#include <iostream>
#include <string>
#include <cmath>
#include "pixele.hpp"

int pixel::display_hight = 1080;;
int pixel::display_width = 1920;
int main() {
    Kolor k1(23, 255, 23);
    std::cout << k1.get_red() << std::endl;
    std::cout << k1.get_green() << std::endl;
    std::cout << k1.get_blue() << std::endl;

    k1.set_red(78);
    std::cout << k1.get_red() << std::endl;
    k1.set_red(300); // wartość poza zakresem, nie zostanie zmieniona

    k1.light_kolor_up(20);
    std::cout << k1.get_red() << " " << k1.get_green() << " " << k1.get_blue() << std::endl;

    k1.light_kolor_up(30);
    std::cout << k1.get_red() << " " << k1.get_green() << " " << k1.get_blue() << std::endl;

    kolortransparentny k2;
    std::cout << k2.get_alfa() << std::endl;

    k2.set_alfa(200);
    std::cout << k2.get_alfa() << std::endl;

    kolornazwany k4("beżowy");
    k4.set_name("red");
    std::cout << k4.get_name() << std::endl;

    kolornt k5(255, 78, 62, 122,"czerwony");
    
    std::cout << k5.kolortransparentny::get_red() << " " << k5.kolortransparentny::get_green() 
    << " " << k5.kolortransparentny::get_blue() << " " << k5.get_name() << std::endl;


    std::cout << "Pixele\n";
    pixel pix(23, -12);;
    pix.set_pixel(12, 1000);
    std::cout << pix.pixel_x << "," << pix.pixel_y << std::endl;

    pix.left_down();
    std::cout << pix.pixel_x << "," << pix.pixel_y << std::endl;

    pix.right_up();
    std::cout << pix.pixel_x << "," << pix.pixel_y << std::endl;

    pikselkolorowy k6(300,20);

    k6.move_pixel(12, 40);

    std::cout << k6.pixel_x << "," << k6.pixel_y << std::endl;

    std::cout<< "odległość: " << odległosc(k6, pix) << std::endl;

    return 0;
}
