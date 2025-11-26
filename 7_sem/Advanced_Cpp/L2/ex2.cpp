#include <iostream>
#include <fstream>
#include <string>
#include <memory>

class line_writer
{
private:
    std::ofstream file;

public:
    explicit line_writer(const std::string &filename)
    {
        file.open(filename);
    }

    void write_line(const std::string &line)
    {
        if (file.is_open())
        {
            file << line << "\n";
        }
    }

    ~line_writer()
    {
        if (file.is_open())
            {
                file.close();
                std::cout << "Closing File ...\n";
            }
    }
};

int main()
{
    auto lw_ptr = std::make_shared<line_writer>("ex2.txt");
    auto lw_ptr1 = lw_ptr;
    auto lw_ptr2 = lw_ptr;
    auto lw_ptr3 = lw_ptr;

    lw_ptr->write_line("Cześć,");
    lw_ptr1->write_line("Co tam?");
    lw_ptr2->write_line("W porządku,");
    lw_ptr3->write_line("A u ciebie?");
}