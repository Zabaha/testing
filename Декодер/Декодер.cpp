#include <iostream>
#include <fstream>
#include <Windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>
#include <math.h>
using namespace std;

using std::cin;
using std::cout;
using std::endl;

int getArabNum(const char&);
bool isCorrectLetter(const char&);
bool getRomanNumeral(char[], int&);
bool checkSequence(const char[], const int&);
int getSubtractingSequence(const char&, const char&);
int calc(const char[], const int&);

int main() {
	const int size = 25;
	char romanNumeral[size];
	bool exit = false, isCorrectNumber;
	int actualSize;

	while (!exit) {
		actualSize = size;
		romanNumeral[0] = '\0';
		isCorrectNumber = false;

		cout << "Please enter Roman Numeral\n>";
		if (getRomanNumeral(romanNumeral, actualSize))
		{
			if (checkSequence(romanNumeral, actualSize))
			{
				isCorrectNumber = true;
			}
		}
		if (isCorrectNumber)
		{
			cout << calc(romanNumeral, actualSize) << endl;
		}
		else
		{
			cout << "Provided Romam numeral is incorrect.\n";
		}


		if (cin.get() == '2')
		{
			cout << "\n1 :: Try once again\n2 :: EXIT\n>";
			exit = true;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		system("CLS");
	}
	return 0;
}

//вычесление результата
int calc(const char array[], const int& count)
{
	int res = 0;
	int prev = 0, next;
	for (int i = count; i >= 0; --i)
	{
		next = getArabNum(array[i]);
		if (prev > next)
		{
			res = (res - prev) + (prev - next);
		}
		else
		{
			res += next;
		}
		prev = next;

	}
	return res;
}

bool checkSequence(const char romanNumeral[], const int& actualSize)
{
	int substrResult = 0;

	for (int i = actualSize - 1; i >= 0; --i)
	{
		// ЕСЛИ СТРОКА НЕ МЕНЬШЕ 3Х СИМВОЛОВ
		if (i > 1)
		{
			/*исключаем последовательности типа:  VXV, IVI, XLX, LCL, LXL, VIV, DCD */
			if (romanNumeral[i] == romanNumeral[i - 2] && romanNumeral[i] != romanNumeral[i - 1])
			{

				if (getArabNum(romanNumeral[i - 1])
					% getArabNum(romanNumeral[i]) == 0
					|| getArabNum(romanNumeral[i])
					/ getArabNum(romanNumeral[i - 1]) == 5) {
					return false;
				}

			}
			else if (romanNumeral[i] == romanNumeral[i - 1])
			{
				/*исключаем последовательности типа:  IVV, IXX, XLL, XCC, CDD, CMM */
				if (getArabNum(romanNumeral[i - 2]) < getArabNum(romanNumeral[i - 1]))
				{
					return false;
				}
			}
		}
		if (i > 0)
		{
			if (romanNumeral[i] == romanNumeral[i - 1])
			{
				/*исключаем последовательности типа : VV, LL, DD*/
				if ((getArabNum(romanNumeral[i]) == 5) || (getArabNum(romanNumeral[i]) == 50) || (getArabNum(romanNumeral[i]) == 500))
				{
					return false;
				}
			}
		}

		// ИНАЧЕ ИСКЛЮЧЕНИЙ НЕТ
		if (substrResult > 0 && getArabNum(romanNumeral[i]) <= substrResult)
		{
			return false; //цифра следующая слева от пары требующей вычитания должна быть
						  //больше разности
		}
		else {
			//cout << "4" << endl;
			if (i > 0)
			{ //двигаемся далее по массиву для обработки следующей пары (если такая есть)
				--i;
				if (getArabNum(romanNumeral[i]) < getArabNum(romanNumeral[i + 1]))
				{
					substrResult = getSubtractingSequence(romanNumeral[i], romanNumeral[i + 1]);
					if (substrResult == -1)
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

/*При вычитании допустимы только следующие
 * последовательности
 * IV (4), IX(9), XL(40), XC(90), CD(400), CM(900)
 */
int getSubtractingSequence(const char& left, const char& right)
{
	int result;

	result = getArabNum(right) - getArabNum(left);
	if (result == 900 || result == 400 || result == 90 || result == 40 || result == 9 || result == 4)
	{
		return result;
	}
	return -1;
}

/* Читаем строку. Проверяем на наличие цифры повторящейся
 * более трех раз подряд и корректность символа
 * Если все прошло успешно то функция заполняет массив и
 * возвращает true
 * !!! эта функция меняет значение размера массива
 */
bool getRomanNumeral(char romanNumeral[], int& maxSize)
{
	char ch;
	int recurrenc = 1;

	for (int i = 0; i < maxSize; ++i)
	{
		//идем по строке пока позволяет размер массива
		ch = cin.get();
		if (isCorrectLetter(ch) || ch == '\n')
		{

			//корректен ли символ
			if (i > 0) {
				if (romanNumeral[i - 1] == ch)
				{
					//если предыдущий символ равен текущему
					recurrenc++;
					if (recurrenc == 4)
					{
						//достигнут недопустимый предел повторений
						//cout << "UPS!";
						cin.clear();
						cin.ignore(1000, '\n');
						return false;
					}
				}
				else
				{
					recurrenc = 1;
				}
			}
			if (ch == '\n')
			{
				//если достигнут конец строки
				romanNumeral[i] = '\0'; //то закрываем массмв char
				maxSize = i; //и выходим из цикла
			}
			else
			{
				romanNumeral[i] = ch;
			}
		}
		else
		{
			//cout << "UPS!";
			cin.clear();
			cin.ignore(1000, '\n');
			return false;
		}
	}
	return true;
}

//return roman digit arabic equivalent
int getArabNum(const char& rimNumber)
{
	switch (rimNumber)
	{
	case 'I':
	case 'i':
		return 1;
	case 'V':
	case 'v':
		return 5;
	case 'X':
	case 'x':
		return 10;
	case 'L':
	case 'l':
		return 50;
	case 'C':
	case 'c':
		return 100;
	case 'D':
	case 'd':
		return 500;
	case 'M':
	case 'm':
		return 1000;
	}
	return 0;
}

//check if provided roman digit is correct
bool isCorrectLetter(const char& letter)
{
	const int size = 14;
	char mySymbols[size] = { 'I', 'V', 'X', 'L', 'C', 'D', 'M', 'i', 'v', 'x', 'l', 'c', 'd', 'm' };
	for (int i = 0; i < size; ++i)
	{
		if (letter == mySymbols[i])
		{
			return true;
		}
	}
	return false;
}
