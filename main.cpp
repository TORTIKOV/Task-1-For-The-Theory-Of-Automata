#include <iostream>

bool rasp(std::string in)
{
    char c;                     // c - бегунок по тексту

    bool two_br_opened = false;  // проверка на открытие двух скобок
    bool one_br_opened = false;  // проверка на открытие одной скобки
    
    int a_counter = 0;          // проверка на четность 'a'
    int b_counter = 0;          // проверка на нечетность 'b'
    
    int idx = 1;
    c = in[idx];
    
    do
    {
        c = in[idx];
        
        if(c == '(')
        {
            if(in[idx + 1] == '(' )
            {
                
                if(two_br_opened == true || one_br_opened == true)
                {
                    std::cout << "Ошибка в расстановке скобок. Не подходит. " << std::endl;
                    return false;
                }
                
                two_br_opened = true;
                idx += 2;
                c = in[idx];
            } else {
                
                if(two_br_opened == true || one_br_opened == true)
                {
                    std::cout << "Ошибка в расстановке скобок. Не подходит. " << std::endl;
                    return false;
                }
                
                one_br_opened = true;
                ++idx;
                c = in[idx];
            }
            
            if(c == 'a' || c == 'b')
            {
                
            } else {
                std::cout << "Ошибка с буквами. Не подходит. " << std::endl;
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
                
                if((a_counter % 2 != 0) && (c != 'b'))
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



int main(int argc, const char * argv[]) {
    std::string test = "%(aabbb)(bb)((aab))%";
    
    std::cout << rasp(test) << std::endl;
    
    return 0;
}
