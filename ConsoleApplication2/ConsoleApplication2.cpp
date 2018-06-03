//Прибавить к каждому числу корень квадратный из произведения максимума и последнего числа
//макросы - это препроцессорные функции, созданные с помощью директивы #define, которые принимают параметры подобно функциям.
#include <iostream>//iostream заголовочный файл с классами, функциями и переменными для организации ввода-вывода в языке программирования C++.
#include <Windows.h>//чтобы использовать функционал windows
#include <list>   
#include <sstream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <fstream>
#include <cstdio>
#include <time.h>
#include <cstring>
using namespace std;



class SqrtValue
{
private:
	double Factor;
public:
	SqrtValue(const double& _Val) : Factor(_Val) {
	}

	double operator ( ) (double& elem) const
	{
		if (Factor > 0)
		{
			elem = elem + sqrt(Factor);
			return elem;
		}
		else
		{
			return elem;
		}
	}
};



// проверка корректности символа в имени файла
bool CorrectSymbol(char c)
{
	switch (c)
	{
	case '.':
	case '*':
	case '?':
	case '<':
	case '>':
	case ':':
	case '|':
		return false;
	default:
		return true;
	}
}


// проверка корректности имени
bool CorrectName(char *name)
{
	int i = 1;
	bool goodsm = false;
	if (name[0] != '\0')
	{
		goodsm = CorrectSymbol(name[0]);
		while (name[i] != '\0' && goodsm)
			goodsm = CorrectSymbol(name[i++]);
	}

	return goodsm;
}

//ввод имени файла
char* InputFileName()
{
	char *filename;
	filename = new char[45];

	do
	{
		cout << "Введите имя файла(без расширения):  ";
		cin >> filename;
		if (CorrectName(filename))
		{
			strcat(filename, ".txt");
			break;
		}
		else
			cout << "Файл не удалось создать\n";
	} while (true);

	return filename;
}

// заполнение файла случайными числами
FILE *LoadInTextFile(int &N, int &M)
{
	FILE *file;
	char* filename = InputFileName();

	file = fopen(filename, "w+");

	srand((unsigned int)time(0));

	fstream in(file);
	for (int i = 1; i <= N; i++)
	{
		in << rand() % (2 * M + 1) - M << ' ';
	}
	cout << "Файл создан!" << endl;
	return file;
}

// заполнение файла случайными числами через generate
FILE *LoadInTextFileInGenerate(int &N, int &M)
{
	FILE *file;
	char* filename = InputFileName();

	file = fopen(filename, "w+");
	fstream in(file);

	srand((unsigned int)time(0));

	list<double> numbers(N);
	generate_n(std::ostream_iterator<int>(in, " "), N, [M]() {return rand() % (2 * M + 1) - M;  });
	cout << "Файл создан!" << endl;
	return file;
}

// загрузка чисел из файла в список
list<double> LoadFromFile(FILE *File)
{
	ifstream in(File);
	in.seekg(0);

	int x;
	list < double > numbers;
	if (!in.eof())
	{
		in >> x;

	}
	while (!in.eof())
	{
		numbers.push_back(x);
		in >> x;
	}
	in.close();
	return numbers;
}

// печать списка в файл
void OutputFile(list<double> &items)
{
	char* newfname = InputFileName();
	ofstream fout(newfname);
	if (fout)
	{
		list<double>::const_iterator pos;

		for (pos = items.begin(); pos != items.end(); ++pos)
		{
			fout << *pos << ' ';
		}
		cout << endl << "Файл выведен!" << endl;
		fout.close();
	}
	else
	{
		cout << "Ошибка открытия файла!" << endl;
	}
}

// печать списка на экран
void OutputScreen(list<double> &items)
{
	list<double>::const_iterator pos;

	for (pos = items.begin(); pos != items.end(); ++pos)
	{
		cout << *pos << ' ';
	}
	cout << endl << "Список выведен!" << endl;
}

// поиск минимального элемента в списке
double SearchMax(list<double> &numbers)
{
	double max = numbers.front();
	for (auto iter = ++numbers.begin(); iter != numbers.end(); iter++)
	{
		if (*iter > max)
			max = *iter;
	}
	return max;
}
// поиск минимального элемента в списке
double SearchLast(list<double> &numbers)
{
	return numbers.back();
}

// поиск минимального элемента в списке (через итераторы)
double SearchMax(list<double>::iterator begin, list<double>::iterator end)
{
	double max = *begin;
	for (auto iter = ++begin; iter != end; iter++)
	{
		if (*iter > max)
			max = *iter;
	}
	return max;
}

// поиск последнего элемента в списке (через итераторы)
double SearchLast(list<double>::iterator begin, list<double>::iterator end)
{
	double last;
	for (auto iter = ++begin; iter != end; iter++)
	{
		last = *iter;
	}
	return last;
}
bool CheckPositive(double &max, double &last)
{
	if ((max > 0) && (last > 0) || (max <= 0) && (last <= 0))
		return true;
	else
		return false;
}
// функция modify для изменения списка
list<double> Modify(list<double> &numbers)
{
	if (numbers.empty())
		return numbers;
	list<double> numbers2;
	double max = SearchMax(numbers);
	double chislo = max * numbers.back();
	for (auto iter = numbers.begin(); iter != numbers.end(); iter++)
	{
		if (chislo>=0)
		{
			*iter = *iter + sqrt(max*numbers.back());
		}
		numbers2.push_back(*iter);
	}
	return numbers2;
}

// перегруженная функция modify для изменения списка
list<double> Modify(list<double>::iterator begin, list<double>::iterator end)
{
	list<double> numbers2;
	double max = SearchMax(begin, end);
	double last = SearchLast(begin, end);
	for (list<double>::iterator iter = begin; iter != end; iter++)
	{
		if (CheckPositive(max, last))
		{
			*iter = *iter + sqrt(max*last);
		}
		numbers2.push_back(*iter);
	}
	return numbers2;
}

// функция  для изменения списка через transform
list<double> TransformList(list<double> &numbers)
{
	double max = SearchMax(numbers);
	list<double> numbers2;
	double last = SearchLast(numbers);
	double chislo = last * max;
	for (auto iter = numbers.begin(); iter != numbers.end(); iter++)
	{
		numbers2.push_back(*iter);
	}
	transform(numbers2.begin(), numbers2.end(), numbers2.begin(), SqrtValue(chislo));
	return numbers2;
}

// функция  для изменения списка через for_each
list<double> ForEachList(list<double>::iterator begin, list<double>::iterator end)
{
	list<double> numbers2;
	double max = SearchMax(begin, end);
	double last;
	for_each(begin, end, [&last](int i) { last = i; });
	for (list<double>::iterator i = begin; i != end; i++)
	{
		if (CheckPositive(max, last))
		{
			*i = *i + sqrt(max*last);
		}
		numbers2.push_back(*i);
	}
	return numbers2;
}

// функция  для вычисления суммы
double Sum(list<double> &numbers)
{
	if (numbers.empty())
	{
		cout << "Список пустой" << endl;
		return 0;
	}
	double sum = 0;
	for (auto iter = numbers.begin(); iter != numbers.end(); iter++)
	{
		sum += *iter;
	}
	return sum;
}

// функция  для вычисления среднего арифметоческого
double Average(list<double> &numbers)
{
	if (numbers.empty())
	{
		cout << "Список пустой" << endl;
		return 0;
	}
	else
	{
		double sums = Sum(numbers);
		int col = numbers.size();
		return (double)sums / col;
	}
}

int InputNumber(int min, int max)
{
	int n;
	do
	{
		cout << "Ваш выбор: ";
		while ((!(cin >> n)) || cin.get() != '\n')
		{
			cout << "Неправильный ввод !!  Повторите снова!\n";
			cin.clear(); // сбрасывает все биты потока, тоесть поток становится "хорошим"
			cin.sync();//Удалим данные из буффера
			cout << "Ваш выбор : ";
			getchar();
			getchar();
		}
	} while ((n < min) || (n > max));
	return n;
}

int InputParametr(int min, int max)
{
	int n;
	do
	{
		cout << "Введите параметр: ";
		while ((!(cin >> n)) || cin.get() != '\n')
		{
			cout << "Неправильный ввод !!  Повторите снова!\n";
			cin.clear(); // сбрасывает все биты потока, тоесть поток становится "хорошим"
			cin.sync();//Удалим данные из буффера
			cout << "Введите параметр: ";
			getchar();
			getchar();
		}
	} while ((n < min) || (n > max));
	return n;
}

int Menu()
{
	cout << " --------------------Меню---------------------  " << endl;
	cout << "1 - Modify(преобразование списка )" << endl;
	cout << "2 - Modify(преобразование списка - перегруженный вариант) " << endl;
	cout << "3 - Преобразование с помощью transform" << endl;
	cout << "4 - Преобразование с помощью for_each" << endl;
	cout << "5 - Посчитать сумму" << endl;
	cout << "6 - Посчитать среднее арифметическое" << endl;
	cout << "7 - Вывод на экран " << endl;
	cout << "8 - Сохранить в файл" << endl;
	cout << "0 - Выход " << endl;
	int n = InputNumber(0, 8);
	cout << "\n";
	return n;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	FILE* file=NULL;
	list<double> numbers;
	int N;
	int M;
	//char filename[40];
	//char newfname[40];
	int changemenu;
	bool enterfile = true;

	cout << " --------------------Меню---------------------  " << endl;
	cout << "1 - Заполнение текстового файла случайными числами(через цикл)" << endl;
	cout << "2 - Заполнение текстового файла случайными числами(через generate) " << endl;
	cout << "0 - Выход" << endl;
	changemenu = InputNumber(0, 2);
	switch (changemenu)
	{
	case 1:
		cout << "Размер списка -->" << endl;
		N = InputParametr(0, 30);
		cout << "Диапазон для чисел -->" << endl;
		M = InputParametr(0, 100);
		file = LoadInTextFile(N, M);
		break;

	case 2:
		cout << "Размер списка -->" << endl;
		N = InputParametr(0, 30);
		cout << "Диапазон для чисел -->" << endl;
		M = InputParametr(0, 100);
		file = LoadInTextFileInGenerate(N, M);
		break;

	default:
		enterfile = false;
		break;
	}
	if (enterfile)
	{
		numbers = LoadFromFile(file);
		for (;;)
		{
			int n = Menu();
			switch (n)
			{
			case 1:
				numbers = Modify(numbers);
				break;

			case 2:
				numbers = Modify(numbers.begin(), numbers.end());
				break;

			case 3:
				numbers = TransformList(numbers);
				break;

			case 4:
				numbers = ForEachList(numbers.begin(), numbers.end());
				break;

			case 5:
				cout << "Сумма: " << Sum(numbers) << endl;
				break;

			case 6:
				cout << "Среднее арифметическое: " << Average(numbers) << endl;
				break;

			case 7:
				cout << "Список: " << endl;
				OutputScreen(numbers);
				break;

			case 8:
				OutputFile(numbers);
				break;

			default:
				cout << "Выход " << endl; exit(0);
				break;

			}
		}
	}
	else
		cout << "До новых встреч!\n";
	system("pause");
}
