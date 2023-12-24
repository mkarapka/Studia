#pragma once
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <typeinfo>
namespace File{
class Plik {
public:
    virtual ~Plik() = default;
};

    class Wejscie : public Plik {
    private:
        std::ifstream plik;

    public:
        explicit Wejscie(const std::string& filename) {
            plik.open(filename, std::ios::binary);
            if (!plik.is_open()) {
                throw std::runtime_error("Nie można otworzyć pliku do odczytu.");
            }
        }

        ~Wejscie() {
            plik.close();
        }

        template <typename T>
        void odczytaj(T& data) {
            
            plik.read(reinterpret_cast<char*>(&data), sizeof(data));
        }

        bool eof() const {
            return plik.eof();
        }
    };
    class Wyjscie : public Plik {
private:
    std::ofstream plik;

public:
    explicit Wyjscie(const std::string& filename) {
        plik.open(filename, std::ios::binary);
        if (!plik.is_open()) {
            throw std::runtime_error("Nie można otworzyć pliku do zapisu.");
        }
    }

    ~Wyjscie() {
        plik.close();
    }

    template <typename T>
    void zapisz(const T& data) {

        plik.write(reinterpret_cast<const char*>(&data), sizeof(data));
    }
};
};