#include <iostream>
#include <chrono>

void print_day_suffix(std::chrono::year_month_day date)
{
    switch (auto day = static_cast<unsigned>(date.day()))
    {
    case 1:
        std::cout << "1st";
        break;
    case 2:
        std::cout << "2nd";
        break;
    case 3:
        std::cout << "3rd";
        break;
    default:
        std::cout << day << "th";
        break;
    }
}

void print_date_with_month_name(std::chrono::year_month_day date)
{
    switch (auto month = static_cast<unsigned>(date.month()))
    {
    case 1:
        print_day_suffix(date);
        std::cout << " January " << date.year();
        break;
    case 2:
        print_day_suffix(date);
        std::cout << " February " << date.year();
        break;
    case 3:
        print_day_suffix(date);
        std::cout << " March " << date.year();
        break;
    case 4:
        print_day_suffix(date);
        std::cout << " April " << date.year();
        break;
    case 5:
        print_day_suffix(date);
        std::cout << " May " << date.year();
        break;
    case 6:
        print_day_suffix(date);
        std::cout << " June " << date.year();
        break;
    case 7:
        print_day_suffix(date);
        std::cout << " July " << date.year();       
        break;
    case 8:
        print_day_suffix(date);
        std::cout << " August " << date.year();
        break;
    case 9:
        print_day_suffix(date);
        std::cout << " September " << date.year();
        break;
    case 10:
        print_day_suffix(date);
        std::cout << " October " << date.year();
        break;
    case 11:
        print_day_suffix(date);
        std::cout << " November " << date.year();
        break;
    case 12:
        print_day_suffix(date);
        std::cout << " December " << date.year();
        break;
    default:
        break;
    }
    std::cout << std::endl;
}



int main()
{
    for(unsigned i = 1; i <= 3; i++)
    {
        std::chrono::year_month_day date{std::chrono::year{2025}, std::chrono::month{5}, std::chrono::day{i}};
        print_date_with_month_name(date);
    }
    auto today = std::chrono::year_month_day{
        std::chrono::floor<std::chrono::days>(
            std::chrono::system_clock::now()
        )
    };
    print_date_with_month_name(today);
}