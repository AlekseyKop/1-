//��������� � ������� ����� ������ ���������� �� ������������ ��������� � ���������� �����
//������� - ��� ��������������� �������, ��������� � ������� ��������� #define, ������� ��������� ��������� ������� ��������.
#include <iostream>//iostream ������������ ���� � ��������, ��������� � ����������� ��� ����������� �����-������ � ����� ���������������� C++.
#include <Windows.h>//����� ������������ ���������� windows
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



// �������� ������������ ������� � ����� �����
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


// �������� ������������ �����
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

//���� ����� �����
char* InputFileName()
{
	char *filename;
	filename = new char[45];

	do
	{
		cout << "������� ��� �����(��� ����������):  ";
		cin >> filename;
		if (CorrectName(filename))
		{
			strcat(filename, ".txt");
			break;
		}
		else
			cout << "���� �� ������� �������\n";
	} while (true);

	return filename;
}

// ���������� ����� ���������� �������
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
	cout << "���� ������!" << endl;
	return file;
}

// ���������� ����� ���������� ������� ����� generate
FILE *LoadInTextFileInGenerate(int &N, int &M)
{
	FILE *file;
	char* filename = InputFileName();

	file = fopen(filename, "w+");
	fstream in(file);

	srand((unsigned int)time(0));

	list<double> numbers(N);
	generate_n(std::ostream_iterator<int>(in, " "), N, [M]() {return rand() % (2 * M + 1) - M;  });
	cout << "���� ������!" << endl;
	return file;
}

// �������� ����� �� ����� � ������
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

// ������ ������ � ����
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
		cout << endl << "���� �������!" << endl;
		fout.close();
	}
	else
	{
		cout << "������ �������� �����!" << endl;
	}
}

// ������ ������ �� �����
void OutputScreen(list<double> &items)
{
	list<double>::const_iterator pos;

	for (pos = items.begin(); pos != items.end(); ++pos)
	{
		cout << *pos << ' ';
	}
	cout << endl << "������ �������!" << endl;
}

// ����� ������������ �������� � ������
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
// ����� ������������ �������� � ������
double SearchLast(list<double> &numbers)
{
	return numbers.back();
}

// ����� ������������ �������� � ������ (����� ���������)
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

// ����� ���������� �������� � ������ (����� ���������)
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
// ������� modify ��� ��������� ������
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

// ������������� ������� modify ��� ��������� ������
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

// �������  ��� ��������� ������ ����� transform
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

// �������  ��� ��������� ������ ����� for_each
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

// �������  ��� ���������� �����
double Sum(list<double> &numbers)
{
	if (numbers.empty())
	{
		cout << "������ ������" << endl;
		return 0;
	}
	double sum = 0;
	for (auto iter = numbers.begin(); iter != numbers.end(); iter++)
	{
		sum += *iter;
	}
	return sum;
}

// �������  ��� ���������� �������� ���������������
double Average(list<double> &numbers)
{
	if (numbers.empty())
	{
		cout << "������ ������" << endl;
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
		cout << "��� �����: ";
		while ((!(cin >> n)) || cin.get() != '\n')
		{
			cout << "������������ ���� !!  ��������� �����!\n";
			cin.clear(); // ���������� ��� ���� ������, ������ ����� ���������� "�������"
			cin.sync();//������ ������ �� �������
			cout << "��� ����� : ";
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
		cout << "������� ��������: ";
		while ((!(cin >> n)) || cin.get() != '\n')
		{
			cout << "������������ ���� !!  ��������� �����!\n";
			cin.clear(); // ���������� ��� ���� ������, ������ ����� ���������� "�������"
			cin.sync();//������ ������ �� �������
			cout << "������� ��������: ";
			getchar();
			getchar();
		}
	} while ((n < min) || (n > max));
	return n;
}

int Menu()
{
	cout << " --------------------����---------------------  " << endl;
	cout << "1 - Modify(�������������� ������ )" << endl;
	cout << "2 - Modify(�������������� ������ - ������������� �������) " << endl;
	cout << "3 - �������������� � ������� transform" << endl;
	cout << "4 - �������������� � ������� for_each" << endl;
	cout << "5 - ��������� �����" << endl;
	cout << "6 - ��������� ������� ��������������" << endl;
	cout << "7 - ����� �� ����� " << endl;
	cout << "8 - ��������� � ����" << endl;
	cout << "0 - ����� " << endl;
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

	cout << " --------------------����---------------------  " << endl;
	cout << "1 - ���������� ���������� ����� ���������� �������(����� ����)" << endl;
	cout << "2 - ���������� ���������� ����� ���������� �������(����� generate) " << endl;
	cout << "0 - �����" << endl;
	changemenu = InputNumber(0, 2);
	switch (changemenu)
	{
	case 1:
		cout << "������ ������ -->" << endl;
		N = InputParametr(0, 30);
		cout << "�������� ��� ����� -->" << endl;
		M = InputParametr(0, 100);
		file = LoadInTextFile(N, M);
		break;

	case 2:
		cout << "������ ������ -->" << endl;
		N = InputParametr(0, 30);
		cout << "�������� ��� ����� -->" << endl;
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
				cout << "�����: " << Sum(numbers) << endl;
				break;

			case 6:
				cout << "������� ��������������: " << Average(numbers) << endl;
				break;

			case 7:
				cout << "������: " << endl;
				OutputScreen(numbers);
				break;

			case 8:
				OutputFile(numbers);
				break;

			default:
				cout << "����� " << endl; exit(0);
				break;

			}
		}
	}
	else
		cout << "�� ����� ������!\n";
	system("pause");
}
