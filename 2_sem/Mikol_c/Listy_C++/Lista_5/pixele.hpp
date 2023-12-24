#pragma once
#include<iostream>
#include<string>
#include<cmath>
using namespace std;
class Kolor{    

private:
    int red;
    int green;
    int blue;  
public:
    Kolor();
    
    Kolor(int Ared, int Agreen, int Ablue);

    bool check_range(int p, int k,int input);

    int get_red();

    int get_green();

    int get_blue();

    void set_red(int value);

    void set_green(int value);

    void set_blue(int value);

    void light_kolor_up(int value);

    void merge_colors();
};

class kolortransparentny : public Kolor{
    private:
        int alfa;
    public:
        kolortransparentny();

        kolortransparentny(int r, int g, int b, int a);

        int get_alfa();

        void set_alfa(int value);
};


class kolornazwany : public Kolor{
    private:
        string nazwa_kolor;
    public:
        kolornazwany();

        kolornazwany(string name);

        void set_name(string Aname);

        string get_name();
};

class kolornt : public kolortransparentny, public kolornazwany{
public:
    kolornt();
    
    kolornt(int r, int g, int b, int a, string nazwa);
};


class pixel {
public:
    int pixel_x;
    int pixel_y;

    static int display_hight;
    static int display_width;

    pixel();

    pixel(int x, int y);

    void set_pixel(int x, int y);

    void left_down();

    void left_up();

    void right_down();

    void right_up();
};

class pikselkolorowy : public pixel{
public:
    kolortransparentny pixel_color;

    pikselkolorowy();

    pikselkolorowy(Kolor color, int alpha);

    pikselkolorowy(int x, int y);

    void move_pixel(int x, int y);
};

int odległosc(const pixel& p, const pixel& q);
