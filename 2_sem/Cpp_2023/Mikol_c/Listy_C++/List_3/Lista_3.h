#ifndef LISTA_3_HPP
#define LISTA_3_HPP
class Liczba{

    public:
        double value;
        const static size_of_history = 1;
        int tem_size = 1;
        double* tab;

        Liczba(double aValue){
            value = aValue;
            tab = new double[size_of_history];
            tab[size_of_history-1] = value;
        }

        ~Liczba(){
            delete [] tab;
        }

        Liczba& operator=(const Liczba& other){
            if (this != &other)
            {
                value = other.value;
                size_of_history = other.size_of_history;
                tem_size = other.size_of_history;
                delete [] tab;
                tab = new double[size_of_history];
                for (int i = 0; i < size_of_history; i++)
                {
                    tab[i] = other.tab[i];
                }
            }
            return *this;
        }

        Liczba(const Liczba& other){
            if (this != &other)
            {
                Change_val(tab, other.value);
            }
            return *this;
        }

        void Change_val(double* tab, double new_val){
        double* new_tab = new double[size_of_history];
        for (int i = 0; i < size_of_history - 1; i++)
        {
            new_tab[i+1] = tab[i];
        }
        new_tab[0] = new_val;
        delete [] tab;
        tab = new_tab;
        }

        
        void Change_val(double new_val){
            value = new_val;
            tem_size ++;
            if (tem_size > size_of_history)
            {
                Change_val(tab,new_val);
                tem_size = 0;
            }
            else{
                tab[size_of_history - tem_size] = value;
            }
            
        }

        void History(){
            for (int i = 0; i < size_of_history; i++)
            {
                std::cout << tab[i] << " ";
            }
            std::cout << "\n";
        }

        void Pick(double Searching_val){
            bool flag = false;
            for (int i = 0; i < size_of_history; i++)
            {
                if (tab[i] == Searching_val)
                {
                    value = tab[i];
                    flag = true;
                }
            }
            if (flag == false)
            {
                std::cout << "W historii nie ma takiej wartości" << "\n";
            }
        }
        
        void Show_value(){
            std::cout << value << "\n";
        }
};

#endif