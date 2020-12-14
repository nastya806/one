//Ялунина Анастасия, МИ-1701
#include <iostream>
#include <string>
#include <random>
#include <sstream>

std::random_device rd;
std::ranlux48 rnd { rd() };
std::uniform_int_distribution<> dist1 {15, 25};
std::uniform_int_distribution<> dist2 {1, 3};

int read_answer()
{
    int result;
    std::cout <<"Возьми от 1 до 3 камушек" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::stringstream input_ss { input };
    input_ss >> result;
    bool f = input_ss.fail();
    while ( f || result < 1 || result > 3) {//обработка некоректного ввода используя строку
        std::cerr << "Ая-яй, можно брать только от 1 до 3. Давай еще раз: " << std::endl;
    	std::getline(std::cin, input);
    	std::stringstream input_ss { input };
        input_ss >> result;
        f = input_ss.fail();
    }
    return result;
}


int lvl_1(bool f)
{
	int d1 = dist1(rnd);
	std::cout << "Итого: " << d1 << " камушек" << std::endl;
	int d2, a;
	bool f1;
	for (unsigned i=0; d1>0; ++i)
	{
		if( i%2 == 0 )
	    {
	        a = read_answer();
	        while (a > d1)
	        {
	        	std::cerr << "Осталось " << d1 << " камушек. Выбирай дальше!" << std::endl;
	        	a = read_answer();
	        }
	        std::cout << "Осталось " <<(d1 - a) <<" камушек" << std::endl;
	        d1 -= a;
	        f1 = true;
	    }
	    else
	    {
	    	d2 = dist2 (rnd);
	    	while (d2 > d1)
	    	{
	    		d2 = dist2 (rnd);
	    	}
	        std::cout << "Противник взял - " << d2 << ". Камушек осталось: " << (d1-d2) << std::endl;
	        d1 -= d2;
	        f1 = false;
	    }
			if (d1 < 13 and f) return d1;
	    }
	if(f1) std::cout << "Game over. Вы проиграли(" << std::endl;
	else std::cout << "Game over. Вы победили)" << std::endl;
	return 1;
}


void lvl_3(bool f, int ans)
{
	int d1 = ans;
	std::cout << "Итого " << d1 << " камушек" << std::endl;
	int d2, a;//Для рандомного хода компа
	bool f1;
	for (unsigned i=0; d1>0; ++i)
	{
		if(i%2 == 0)
	    {
	        a = read_answer();//Выбор пользователя сколько камней взять
	        while (a > d1)
	        {
	        	std::cerr << "Всего осталось " << d1 << " камушек. Выбирай дальше!";
	        	a = read_answer();
	        }
	        std::cout << "Осталось " <<(d1 - a) <<" камушек " << std::endl;
	        d1 -= a;
	        f1 = true;
	    }

	    else
	    {
	        if( (d1 - 9) % 4 == 1 or d1 - 9 == -3 or d1 == 2 )
			{
	    		d1 -= 1;
	    		std::cout << "Противник взял камушек - 1" << ". Камушек осталось: " << d1 << std::endl;
	    	}

	    	else if( (d1 - 9) % 4 == 2 or d1 - 9 == -2 or d1 == 3 )
	    	{
	    		d1 -= 2;
	    		std::cout << "Противник взял камушек - 2" << ". Камушек осталось: " << d1 << std::endl;
	    	}

	    	else if( (d1 - 9) % 4 == 3 or d1 - 9 == -1 or d1 == 4 )
	    	{
	    		d1 -= 3;
	    		std::cout << "Противник взял камушек - 3" << ". Камушек осталось: " << d1 << std::endl;
	    	}

	    	else
	    	{
	    		d2 = dist2 (rnd);
	    		while (d2 > d1)
	    		{
	    			d2 = dist2 (rnd);
	    		}
	    		d1 -= d2;
	    		std::cout << "Рандом - " << d2 << ". Камушек осталось: " << d1 << std::endl;
	    	}
	    	f1 = false;
	    }
	}
	if(f1) std::cout << "Game over. Вы проиграли(" << std::endl;
	else std::cout << "Game over. Вы выйграли)" << std::endl;
}


void lvl_2()
{
	bool f = true;
	int ans = lvl_1(f);
	lvl_3(f, ans);
}


int main()
{
	int choise;
	bool f = false;

	do
	{
		std::cout << "Уровени сложности: " << std::endl
				  << "1. Лекгий" << std::endl
				  << "2. Средний" << std::endl
			      << "3. Высокий" << std::endl
				  << "4. Выход" << std::endl;
		std::cin >> choise;
		while (std::cin.fail() or choise < 1 or choise > 4) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
		    {
				std::cerr << "Ай-яй. Давай еще раз :" << std::endl;
		        if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
		        {
		            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
		            std::cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера
		        }
		        std::cin >> choise;
		    }
		std::cin.ignore(32767,'\n');

		switch(choise){
			case 1: {lvl_1(f); break;}
			case 2:	{lvl_2(); break;}
			case 3:	{lvl_3(f, dist1(rnd)); break;}

		}
	}while (choise != 4);

    return 0;
}



