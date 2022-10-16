#include <iostream>

bool KA(std::string in)
{
    if(in[0] == in[1]) return false;
    
    char c;                      // c - бегунок по тексту

    bool two_br_opened = false;  // проверка на открытие двух скобок
    bool one_br_opened = false;  // проверка на открытие одной скобки
    
    int a_counter = 0;          // проверка на четность 'a'
    int b_counter = 0;          // проверка на нечетность 'b'
    
    int idx = 1;                // индекс перемещения по строке
    c = in[idx];                // передаем бегунку значение символа после '%'
    
    
    // Цикл, который проходится по переданной строке
    do
    {

        c = in[idx];
        
        if(c == '(')            // Если символ '(', то проверяем одинарная скобка или двойная
        {
            if(in[idx + 1] == '(' )
            {
                // Если есть уже открытые скобки, тогда строка нас не устраивает.
                if(two_br_opened == true || one_br_opened == true)
                {
                    std::cout << "Ошибка в расстановке скобок. Не подходит. " << std::endl;
                    return false;
                }
                
                two_br_opened = true;
                idx += 2;
                c = in[idx];
            } else {
                
                // Если есть уже открытые скобки, тогда строка нас не устраивает.
                if(two_br_opened == true || one_br_opened == true)
                {
                    std::cout << "Ошибка в расстановке скобок. Не подходит. " << std::endl;
                    return false;
                }
                
                one_br_opened = true;  //Показываем, что уже есть открытые скобки.
                ++idx;                 //Смещаемся на символ вперед. Это либо 'a', либо 'b'
                c = in[idx];
                
            }
            
            //
            if(c == 'a' || c == 'b')
            {
                
            } else {
                std::cout << "Ошибка в расстановке скобок. Не подходит. " << std::endl;
                return false;
            }
        
            if((c == 'a' || c == 'b') && (one_br_opened || two_br_opened))
            {
                while(c == 'a')
                {
                    ++a_counter;
                    ++idx;
                    c = in[idx];
                }
                
                if((a_counter % 2 != 0) || (c != 'b'))
                {
                    std::cout << "Нечетное количество 'a'. Не подходит. " << std::endl;
                    return false;
                }
                
                while(c == 'b')
                {
                    ++b_counter;
                    ++idx;
                    c = in[idx];
                    
                    if(in[idx] == 'a')
                    {
                        std::cout << "'a' после 'b'. Не подходит. " << std::endl;
                        return false;
                    }
                }
                
                if(b_counter % 2 == 0)
                {
                    std::cout << "Четное количество 'b'. Не подходит. " << std::endl;
                    return false;
                }
                
                if(c == ')')
                {
                    if(in[idx + 1] == ')')
                    {
                        two_br_opened = false;
                        idx += 2;
                        c = in[idx];
                        
                        if(one_br_opened == true)
                        {
                            std::cout << "Ошибка в расстановке скобок. Не подходит. " << std::endl;
                            return false;
                        }
                        
                        a_counter = 0;
                        b_counter = 0;
                        
                    } else {
                        one_br_opened = false;
                        ++idx;
                        c = in[idx];
                        
                        if(two_br_opened == true)
                        {
                            std::cout << "Ошибка в расстановке скобок. Не подходит. " << std::endl;
                            return false;
                        }
                        
                        a_counter = 0;
                        b_counter = 0;
                        
                    }
                }
                
                
            }
        }
    } while(c != '%');
    std::cout << "Всё подходит. " << std::endl;
    return true;
}

void recognition(std::string in)
{
    std::string out = "";
    char c;
    int place = 0;
    bool percent = false;
    bool isempty = true;
    
    for(int idx = 0; idx < in.length(); ++idx)
    {
        c = in[idx];
        if(c == '%')
        {
            out += c;
            percent = true;
            place = idx + 1;
            ++idx;
            c = in[idx];
            
            while(c != '%')
            {
                out += c;
                ++idx;
                c = in[idx];
                if(idx > in.length()) break;
            }
            if(idx > in.length()) break;
            
            --idx;
            out += '%';
            
            if(KA(out) == true)
            {
                std::cout << place << " : " << out << std::endl;
                isempty = false;
            }
            out = "";
            place = 0;
            
        }
    }
    if(isempty == true)
    {
        std::cout << "Цепочек не найдено" << std::endl;
    }
    
}

int main(int argc, const char * argv[]) {
    std::string test = "%(aabbb)(b)((aab))%(aabbb)(b)((aab))%";
    recognition(test);
    
    return 0;
}
