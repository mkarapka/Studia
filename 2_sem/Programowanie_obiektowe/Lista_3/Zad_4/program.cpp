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

   Kolor(){
       red = 0;
       green = 0;
       blue = 0;
   }
  
   Kolor(int Ared, int Agreen, int Ablue){
       if(Ared >= 0 and Ared <= 255){
           red = Ared;
       }
       else{
           cout << "Nieprawidłowy zakres dla koloru";
       }
       if (Agreen >= 0 and Agreen <= 255)
       {
           green = Agreen;
       }
       else{
           cout << "Nieprawidłowy zakres dla koloru";
       }
       if (Ablue >= 0 and Ablue <= 255)
       {
           blue = Ablue;
       }
       else{
           cout << "Nieprawidłowy zakres dla koloru";
       }
   }


   int get_red(){ return red;}


   int get_green(){ return green;}


   int get_blue(){ return blue;}


   void set_red(int value){
       if(value >= 0 and value <= 255){
           red = value;
       }
   }


   void set_green(int value){
       if(value >= 0 and value <= 255){
           green = value;
       }
   }


   void set_blue(int value){
       if(value >= 0 and value <= 255){
           blue = value;
       }
   }


   void light_kolor_up(int value){
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


   void merge_colors(){
       int avg = (red + green + blue) / 3;
       red = avg;
       green = avg;
       blue = avg;
   }
};


class kolortransparentny : public Kolor{
   private:
       int alfa;


   public:
       kolortransparentny(){
           alfa = 0;
       }


       kolortransparentny(int r, int g, int b, int a) : Kolor(r, g, b), alfa(a)
       {
           set_red(r);
           set_green(g);
           set_blue(b);
       }


       int get_alfa(){ return alfa; }


       void set_alfa(int value){
           if(value >= 0 and value <= 255){
               alfa = value;
           }
           else{
               cout << "Nieprawidłowy zakres dla koloru";
           }
       }
};


class kolornazwany : public Kolor{
   private:
       string nazwa_kolor;
   public:
       kolornazwany(){
           nazwa_kolor = "";
       }


       void kolornazwany(string Aname){
           bool flag = true;
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

       string get_nazwa{return nazwa_kolor; }
};


class kolornt : public kolortransparentny , public kolornazwany{
   public:
       kolornt() : kolortransparentny() , kolornazwany(){}
      
       kolornt(int r, int g, int b, int a, string nazwa) : kolortransparentny(r, g, b, a), kolornazwany(nazwa){}
};


class pixel {
   public:
       static int pixel_x;
       static int pixel_y;
  
   pixel(){
       pixel_x = 0;
       pixel_y = 0;
   }


   pixel(int x, int y){
       if (x >= 0 and 1920)
       {
           pixel_x = x;
       }
       else{
           cout << "Złe dane wejściowe";
       }


       if (y >= 0 and y <= 1080)
       {
           pixel_y = y;
       }
       else{
           cout << "Złe dane wejściowe";
       }
   }


   void left_down(){
       int przek = sqrt(pixel_x * pixel_x + pixel_y * pixel_y);
       cout << przek;
   }


   void left_up(){
       int hight = 1080 - pixel_y;
       int przek = sqrt(pixel_x * pixel_x + hight * hight);
       cout << przek;
   }


   void right_down(){
       int width = 1920 - pixel_x;
       int przek = sqrt(width * width + pixel_y * pixel_y);
       cout << przek;
   }


   void right_up(){
       int width = 1920 - pixel_x;
       int hight = 1080 - pixel_y;
       int przek = sqrt(width * width + hight * hight);
       cout << przek;
   }
};


class pikselkolorowy : public pixel{
   public:
       kolortransparentny pixel_color;


       void move_pixel(int x, int y)
       {
           pixel(pixel_x + x, pixel_y + y);
       }   
};


int distance(const pixel& p, const pixel& q){
   int d_x = (p.pixel_x - q.pixel_x);
   int d_y = (p.pixel_y - q.pixel_y);
   int result = sqrt(d_x * d_x - d_y * d_y);
   return result;
}








