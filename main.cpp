#include <iostream>

// Функция образующая необходимый конечный автомат.
// Она обрабатывает скобку от '%' до '%' и выдает результат true или false
bool KA(std::string in)
{
    if(in[0] == in[1]) return false; // проверка на цепочку вида: "%%"
    
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
                    //std::cout << "Ошибка в расстановке скобок. Не подходит. " << std::endl;
                    return false;
                }
                
                two_br_opened = true;
                idx += 2;
                c = in[idx];
            } else {
                
                // Если есть уже открытые скобки, тогда строка нас не устраивает.
                if(two_br_opened == true || one_br_opened == true)
                {
                    //std::cout << "Ошибка в расстановке скобок. Не подходит. " << std::endl;
                    return false;
                }
                
                one_br_opened = true;  //Показываем, что уже есть открытые скобки.
                ++idx;                 //Смещаемся на символ вперед. Это либо 'a', либо 'b'
                c = in[idx];
                
            }
            
//            // проверка на наличие букв в скобках
//            if((in[idx] == 'a') || (in[idx] == 'b'))
//            {
//                std::cout << "В скобках есть буквы. Всё проходит. " << std::endl;
//            } else {
//                std::cout << "Ошибка. Пустые скобки. Не подходит. " << std::endl;
//                return false;
//            }
            
            // Проверка на наличие букв в скобках и на то, что скобки открыты.
            if((c == 'a' || c == 'b') && (one_br_opened || two_br_opened))
            {
                // Считываем 'a'
                while(c == 'a')
                {
                    ++a_counter;
                    ++idx;
                    c = in[idx];
                }
                
                // Проверяем количество 'a' на четность и на то, что есть хотя бы одна 'b'
                if((a_counter % 2 != 0) || (c != 'b'))
                {
                    //std::cout << "Нечетное количество 'a'. Не подходит. " << std::endl;
                    return false;
                }
                
                // считываем 'b'
                while(c == 'b')
                {
                    ++b_counter;
                    ++idx;
                    c = in[idx];
                    
                    // проверяем на то, что последовательность символов верна
                    if(in[idx] == 'a')
                    {
                        //std::cout << "'a' после 'b'. Не подходит. " << std::endl;
                        return false;
                    }
                }
                
                // Проверяем количество 'b' на нечетность
                if(b_counter % 2 == 0)
                {
                    //std::cout << "Четное количество 'b'. Не подходит. " << std::endl;
                    return false;
                }
                
                // проверка на закрывающие скобки.
                if(c == ')')
                {
                    //проверка на двойную закрывающую скобку.
                    if(in[idx + 1] == ')')
                    {
                        // показываем, что двойная скобка закрылась.
                        two_br_opened = false;
                        idx += 2;
                        c = in[idx];
                        
                        // проверка на случай, если у нас одна открывающая скобка, но две закрывающие
                        if(one_br_opened == true)
                        {
                            //std::cout << "Ошибка в расстановке скобок. Не подходит. " << std::endl;
                            return false;
                        }
                        
                        // удаляем счетчики под 'a' и 'b'
                        a_counter = 0;
                        b_counter = 0;
                        
                    } else {
                        // показываем, что одинарная скобка закрылась.
                        one_br_opened = false;
                        ++idx;
                        c = in[idx];
                        
                        // проверка на случай, когда у нас две открывающие, но одна закрывающая скобка
                        if(two_br_opened == true)
                        {
                            //std::cout << "Ошибка в расстановке скобок. Не подходит. " << std::endl;
                            return false;
                        }
                        
                        // удаляем счетчики под 'a' и 'b'
                        a_counter = 0;
                        b_counter = 0;
                        
                    }
                } else {
                    // Если закрывающих скобок не будет, то цепочка не подходит.
                    //std::cout << "Ошибка в расстановке скобок. Нет закрывающей. Не подходит. " << std::endl;
                    return false;
                }
                
                
            } else {
                // Если проверка на непустые скобки не пройдена.
                //std::cout << "Ошибка. Пустые скобки. Не подходит. " << std::endl;
                return false;
            }
        }
        
        // проверка на случай, если нет открывающих скобок, но есть закрывающие
        if(in[idx - 1] == '%' && in[idx] != '(')
        {
            //std::cout << "Ошибка в расстоновке скобок. Не подходит. " << std::endl;
            return false;
        }
        
    } while(c != '%');
    
    //std::cout << "Всё подходит. " << std::endl;
    return true;
}

// Функция, которая считывает поступившую строку и отправляет в КА '%' до '%'
void recognition(std::string in)
{
    std::string out = "";           // строка, которая передается КА
    char c;                         // бегунок по строке
    int place = 0;                  // место начала строки
    bool isempty = true;            // переменная, показывающая, что подходящих цепочек нет.
    
    // цикл по строке
    for(int idx = 0; idx < in.length(); ++idx)
    {
        c = in[idx];
        
        // Начала обработки строки.
        if(c == '%')
        {
            out += c;
            place = idx + 1;        // записываем позицию первого символа
            ++idx;
            c = in[idx];
            
            // считываем строку до '%'
            while(c != '%')
            {
                out += c;
                ++idx;
                c = in[idx];
                if(idx > in.length()) break;    // Проверка на выход из строки
                                                // Необходимо на случай, если в конце нет '%'
            }
            if(idx > in.length()) break;        // Аналогичная проверка.
            
            --idx;
            out += '%';
            
            // Проверка строки.
            if(KA(out) == true)
            {
                std::cout << place << "\t:\t" << out << std::endl; // выводим строку
                isempty = false;    // показываем, что есть хотя бы одна подходящая цепочка
            }
            out = "";
            place = 0;
            
        }
    }
    
    // если цепочек не найдено, то показываем.
    if(isempty == true)
    {
        std::cout << "Цепочек не найдено" << std::endl;
    }
    
}

int main(int argc, const char * argv[]) {
    
//                         Тесты:
//---------------------------------------------------------
    // Тест из задания:
    std::string test_01 = "%(aabbb)(b)((aab))%";
    std::cout << "=== Test 01: ===" << std::endl;
    recognition(test_01);
    std::cout << std::endl;
    // Вывод:
    //      === Test 01: ===
    // 1     :    %(aabbb)(b)((aab))%
    
//---------------------------------------------------------
    
    // Тест нескольких верных цепочек:
    std::string test_02 = "%(aabbb)%(b)%((aab))%";
    std::cout << "=== Test 02: ===" << std::endl;
    recognition(test_02);
    std::cout << std::endl;
    // Вывод:
    //      === Test 02: ===
    // 1     :    %(aabbb)%
    // 9     :    %(b)%
    // 13    :    %((aab))%
    
//---------------------------------------------------------
    
    // Тест двух верных цепочек и одной неверной:
    std::string test_03 = "%((aabbb))%(bb)%((aaaab))%";
    std::cout << "=== Test 03: ===" << std::endl;
    recognition(test_03);
    std::cout << std::endl;
    // Вывод:
    //      === Test 03: ===
    // 1     :    %((aabbb))%
    // 16    :    %((aaaab))%

//---------------------------------------------------------
    
    // Тест нескольких неверных цепочек:
    std::string test_04 = "%((aabbb)%(bb)%((aaaaab))%";
    std::cout << "=== Test 04: ===" << std::endl;
    recognition(test_04);
    std::cout << std::endl;
    // Вывод:
    //      === Test 04: ===
    //    Цепочек не найдено
//---------------------------------------------------------
    
    // Тест на неверную последовательность букв:
    std::string test_05 = "%(aba)%";
    std::cout << "=== Test 05: ===" << std::endl;
    recognition(test_05);
    std::cout << std::endl;
    // Вывод:
    //      === Test 05: ===
    //    Цепочек не найдено
    
//---------------------------------------------------------
    
    // Тест на пустые скобки:
    std::string test_06 = "%(())%(aabbb)%";
    std::cout << "=== Test 06: ===" << std::endl;
    recognition(test_06);
    std::cout << std::endl;
    // Вывод:
    //      === Test 06: ===
    //    6     :    %(aabbb)%
    
//---------------------------------------------------------
    
    // Тест на ошибку с открытием/закрытием скобок:
    std::string test_07 = "%()%((aab))%";
    std::cout << "=== Test 07: ===" << std::endl;
    recognition(test_07);
    std::cout << std::endl;
    // Вывод:
    //      === Test 07: ===
    //    4     :    %((aab))%
    
//---------------------------------------------------------
    
    // Тест на пустую строку:
    std::string test_08 = "";
    std::cout << "=== Test 08: ===" << std::endl;
    recognition(test_08);
    std::cout << std::endl;
    // Вывод:
    //      === Test 08: ===
    //    Цепочек не найдено
    
//---------------------------------------------------------
    
    // Тест на строку из процентов:
    std::string test_09 = "%%";
    std::cout << "=== Test 09: ===" << std::endl;
    recognition(test_09);
    std::cout << std::endl;
    // Вывод:
    //      === Test 09: ===
    //    Цепочек не найдено
    
//---------------------------------------------------------
    

    // Тест на сторонние символы и регистр:
    std::string test_10 = "%(aAbbb)%((aaccb))%";
    std::cout << "=== Test 10: ===" << std::endl;
    recognition(test_10);
    std::cout << std::endl;
    // Вывод:
    //      === Test 10: ===
    //    Цепочек не найдено
    
//---------------------------------------------------------
    
    // Тест на строку без скобки в начале и в конце:
    std::string test_11 = "%aab))%(aab%";
    std::cout << "=== Test 11: ===" << std::endl;
    recognition(test_11);
    std::cout << std::endl;
    // Вывод:
    //      === Test 11: ===
    //    Цепочек не найдено
    
//---------------------------------------------------------
    
    
    // Тест на строку с поздним началом:
    std::string test_12 = "Начало цепочки тут -> %((aab))%";
    std::cout << "=== Test 12: ===" << std::endl;
    recognition(test_12);
    std::cout << std::endl;
    // Вывод:
    //      === Test 12: ===
    //    39    :    %((aab))%
    
//---------------------------------------------------------
    
    // Тест на строку с поздним концом:
    std::string test_13 = "%((aab))% <- тут был конец программы(->)";
    std::cout << "=== Test 13: ===" << std::endl;
    recognition(test_13);
    std::cout << std::endl;
    // Вывод:
    //      === Test 13: ===
    //    1     :    %((aab))%

//---------------------------------------------------------
    
    // Тест на сторонний текст в середине программы:
    std::string test_14 = "%((aab))% <- тут нет нужной цепочки ->%((aab))%";
    std::cout << "=== Test 14: ===" << std::endl;
    recognition(test_14);
    std::cout << std::endl;
    // Вывод:
    //      === Test 14: ===
    //    1     :    %((aab))%
    //    58    :    %((aab))%
    
//---------------------------------------------------------
    
    //Тест на всё вместе:
    std::string test_15 = "Made by: Sarmat Totikov %((aab))%((aab))%((aab))%%((aab))% ";
    std::cout << "=== Test 15: ===" << std::endl;
    recognition(test_15);
    std::cout << std::endl;
    // Вывод:
    //      === Test 15: ===
    //    25    :    %((aab))%
    //    33    :    %((aab))%
    //    41    :    %((aab))%
    //    50    :    %((aab))%
    
//---------------------------------------------------------
    return 0;
}
