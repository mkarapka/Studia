#include<iostream>
#include<string>
#include<cmath>
int main(){
    Kolor k1(23,255,23);
    std::cout << k1.get_red() << ednl;
    std::cout << k1.get_green() << ednl;
    std::cout << k1.get_bule() << ednl;

    k1.set_red(78);
    std::cout << k1.get_red() << ednl;
    k1.set_red(300);

    k1.light_up(20);
    std:: cout << k1.get_red() << " " << k1.get_green() << " " k1.get_blue() << endl;

    k1.light_up(30);
    std:: cout << k1.get_red() << " " << k1.get_green() << " " k1.get_blue() << endl;

    kolortansparenty k2;
    std::cout << k2.get_alfa(); << endl;

    k2.set_alfa(200);
    std::cout << k2.get_alfa(); << endl;
    
    kolornazwany k4("beżowy");
    k4("red");
    std::cout << get_nazwa << endl;

    kolornt k5(255,78,62,"czerwony");

    std::cout << k5.get_red() << " " << k5.get_green() " " k5.get_blue() << k5.get_nazwa() << endl;

    pixel pix;
    pix(23, -12)
    pix(12, 1000);
    std :: cout << pix.left_down();
    std:: cout << pix.right_up();

    std:: cout << pix.pixel_x << "," << pix.pixel_y << endl;

    move_pixel(12,40);

    std:: cout << pix.pixel_x << "," << pix.pixel_y << endl;

    pixel k6(300,20);

    std::cout << distance(&k6, &k5); << endl;
    return 0;

}