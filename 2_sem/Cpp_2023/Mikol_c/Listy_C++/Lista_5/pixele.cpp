#include<iostream>
#include<string>
#include<cmath>
#include"pixele.hpp"

using namespace std;

//Klasa Kolor 
Kolor::Kolor() : Kolor(0,0,0){}
    
Kolor::Kolor(int Ared, int Agreen, int Ablue){
    if(check_range(0,255,Ared) and check_range(0,255,Agreen) and check_range(0,255,Ablue))
    {
        set_red(Ared);
        set_green(Agreen);
        set_blue(Ablue);
    }
    else{
        throw out_of_range("Nieprawidłowy zakres dla koloru");
    }
}

bool Kolor::check_range(int p, int k,int input){
    if(p <= input and k >= input){
        return true;
    }
    return false;
}

int Kolor::get_red(){ return red;}

int Kolor::get_green(){ return green;}

int Kolor::get_blue(){ return blue;}

void Kolor::set_red(int value){
    if(value >= 0 and value <= 255){
        red = value;
    }
}

void Kolor::set_green(int value){
    if(value >= 0 and value <= 255){
        green = value;
    }
}

void Kolor::set_blue(int value){
    if(value >= 0 and value <= 255){
        blue = value;
    }
}

void Kolor::light_kolor_up(int value){
    if(value + red > 255){
        red = 255;
    }
    if(value + red < 0){
        red = 0;
    }

    if(value + green > 255){
        green = 255;
    }
    if(value + green < 0){
        green = 0;
    }

    if(value + blue > 255){
        blue = 255;
    }
    if(value + blue < 0){
        blue = 0;
    }
}

void Kolor::merge_colors(){
    int avg = (red + green + blue) / 3;
    red = avg;
    green = avg;
    blue = avg;
}

//Klasa transparentny 
kolortransparentny::kolortransparentny(){
    int alfa = 0;
}

kolortransparentny::kolortransparentny(int r, int g, int b, int a) : Kolor(r, g, b), alfa(a)
{
}

int kolortransparentny::get_alfa(){ return alfa; }

void kolortransparentny::set_alfa(int value){
    if(value >= 0 and value <= 255){
        alfa = value;
    }
    else{
        cout << "Nieprawidłowy zakres dla koloru ";
    }
}

//Klasa nazwany
kolornazwany::kolornazwany(){
    nazwa_kolor = "";
}

kolornazwany::kolornazwany(string name){
    set_name(name);
}

void kolornazwany::set_name(string Aname){
    bool flag = true;
    // for (auto c in Aname){
    //     if (!lowe)
    // }
    for (int i = 0; i < Aname.length(); i++)
    {
        char znak = Aname[i];
        if( (int)znak < 97 or (int)znak > 122){
            flag = false;
            break;
        }
    }
    if(flag == true){
        nazwa_kolor = Aname;
    }
    else{
        cout << "Nieprawidłowa nazwa koloru";
    }  
}

string kolornazwany::get_name(){return nazwa_kolor; }


//Klasa kolornt
kolornt::kolornt() : kolortransparentny(), kolornazwany() {}

kolornt::kolornt(int r, int g, int b, int a, string nazwa) : kolortransparentny(r, g, b, a), kolornazwany(nazwa) {}


//Klasa pixel
pixel::pixel(){
    pixel_x = 0;
    pixel_y = 0;
}

pixel::pixel(int x, int y){
    set_pixel(x,y);
}

void pixel::set_pixel(int x, int y){
    if (x >= 0 and x < display_width)
    {
        pixel_x = x;
    }
    else{
        cout << "Złe dane wejściowe\n";
    }

    if (y >= 0 and y < display_hight)
    {
        pixel_y = y;
    }
    else{
        cout << "Złe dane wejściowe\n";
    }
}

void pixel::left_down(){
    int przek = sqrt(pixel_x * pixel_x + pixel_y * pixel_y);
    cout << przek << endl;
}

void pixel::left_up(){
    int hight = 1080 - pixel_y;
    int przek = sqrt(pixel_x * pixel_x + hight * hight);
    cout << przek << endl;
}

void pixel::right_down(){
    int width = 1920 - pixel_x;
    int przek = sqrt(width * width + pixel_y * pixel_y);
    cout << przek << endl;
}

void pixel::right_up(){
    int width = 1920 - pixel_x;
    int hight = 1080 - pixel_y;
    int przek = sqrt(width * width + hight * hight);
    cout << przek << endl;
}


//Klasa pixelkolorowy 
pikselkolorowy::pikselkolorowy() {
    pixel_color = kolortransparentny();
}

pikselkolorowy::pikselkolorowy(Kolor color, int alpha) {
    pixel_color = kolortransparentny(color.get_red(), color.get_green(), color.get_blue(), alpha);
}

pikselkolorowy::pikselkolorowy(int x, int y) : pixel(x ,y){};

void pikselkolorowy::move_pixel(int x, int y)
    {
        set_pixel(pixel_x + x, pixel_y + y);
    }

//Odległość 
int odległosc(const pixel& p, const pixel& q){
    int d_x = (p.pixel_x - q.pixel_x);
    int d_y = (p.pixel_y - q.pixel_y);
    int result = sqrt(d_x * d_x + d_y * d_y);
    return result;
}

