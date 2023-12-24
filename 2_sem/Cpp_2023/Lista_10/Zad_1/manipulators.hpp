#pragma once

#include <iostream>
#include <iomanip>
namespace manips{
class ignore
{
    public:
    int x;

    ignore(int x) : x(x) {}

    friend std::istream& operator>>(std::istream& is, const ignore& ign) {
        int count = ign.x;
        while (count > 0 && is.peek() != '\n' && !is.eof()) {
            if(is.peek() == '\n'){
            }
            is.ignore();
            count--;
        }
        return is;
    }
};
class index
{
    public:   
    int x;
    int w;

    index(int x, int w) : x(x), w(w) {}

    friend std::ostream& operator<<(std::ostream& os, const index& ind) {
        std::streamsize prevWidth = os.width();
        char prevFill = os.fill();

        os << '[' << std::setw(ind.w) << std::right << ind.x << ']';

        os.width(prevWidth);
        os.fill(prevFill);

        return os;
    }
};

inline std::istream& clearline(std::istream& is) {
    while (is.peek() != '\n' && is.peek() != EOF) {
        is.ignore();
    }
    if (is.peek() == '\n') {
        is.ignore();
    }
    return is;
}

inline std::ostream& comma(std::ostream& os){
    return os << ", ";
}

inline std::ostream& colon(std::ostream& os){
    return os << ": ";
}
}