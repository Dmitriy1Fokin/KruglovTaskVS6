/*1.	Написать программу, которая выполняет следующие действия :
a.Читает содержимое текстового файла
b.Выделяет слова, словом считаются последовательность символов разделенных пробелами и / или знаками табуляции и / или символами новой строки
c.Вывести список слов присутствующий в тексте без повторений(имеется в виду, что одно и то же слово может присутствовать в списке только один раз)

2.	Написать программу, которая выполняет следующие действия(все операции должны выполняться с помощью стандартных алгоритмов) :
	a.Заполняет вектор геометрическими фигурами.Геометрическая фигура может быть треугольником, квадратом, прямоугольником или пяти угольником.Структура описывающая геометрическую фигуру  определена ниже,
	b.Подсчитывает общее количество вершин всех фигур содержащихся в векторе(так треугольник добавляет к общему числу 3, квадрат 4 и т.д.)
	c.Подсчитывает количество треугольников, квадратов и прямоугольников в векторе
	d.Удаляет все пятиугольники
	e.На основании этого вектора создает vector<Point>, который содержит координаты одной из вершин(любой) каждой фигуры, т.е.первый элемент этого вектора содержит координаты одной из вершину первой фигуры, второй элемент этого вектора содержит координаты одной из вершину второй фигуры и т.д.
	f.Изменяет вектор так, чтобы он содержал в начале все треугольники, потом все квадраты, а потом прямоугольники.
	g.Распечатывает вектор после каждого этапа работы


	Геометрическая фигура задается следующей структурой :
typedef  struct
{
	int vertex_num;      // количество вершин, для треугольника 3, для квадрата и 
						 // прямоугольника 4, для пяти угольника 5
	vector<Point> vertexes;   // вектор содержащий координаты вершин фигуры
							  // Для треугольника содержит 3 элемента
							  // Для квадрата и прямоугольника содержит 4 
							  // элемента
							  // Для пятиугольника 5 элементов
} Shape;

typedef struct
{
	int x, y;
} Point;


Подсказка: кроме алгоритмов рассмотренных в этой работе можно применять все средства описанные в предыдущих работах, включая алгоритмы сортировки.*/


#include "stdafx.h"

using namespace std;

string ReadFromTextFile(string pathToText);
vector<string> stringToVector(string mainString);
void PrintElem(string temp);

int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	string str = ReadFromTextFile("Text.txt");
	//cout << str << endl;

	SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ')
		{
			SetConsoleTextAttribute(hConsole, (WORD)((15 << 0) | 0));
			cout << str[i];
			SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		}
		cout << str[i];
	}
	SetConsoleTextAttribute(hConsole, (WORD)((15 << 0) | 0));


	vector<string> vecStr = stringToVector(str);
	cout << "\nVector:\n";
	for_each(vecStr.begin(), vecStr.end(), PrintElem);
	sort(vecStr.begin(), vecStr.end());
	vecStr.erase(unique(vecStr.begin(), vecStr.end()), vecStr.end());
	cout << "\nwithout duplicates:\n";
	for_each(vecStr.begin(), vecStr.end(), PrintElem);


	_getch();
    return 0;
}

string ReadFromTextFile(string pathToText)
{
	ifstream textFile;
	string strWithAllText, strBuffer;

	textFile.open(pathToText);
	if (!textFile)
		cout << "ERROR! File not found\n";

	while (getline(textFile, strBuffer))
		strWithAllText += strBuffer;

	textFile.close();

	return strWithAllText;
}

vector<string> stringToVector(string mainString)
{
	string strBuffer;
	istringstream strStream(mainString);
	vector<string> vectorWithLecsemy;

	while (strStream >> strBuffer)
		vectorWithLecsemy.push_back(strBuffer);

	return vectorWithLecsemy;
}

void PrintElem(string temp)
{
	cout << temp << endl;
}