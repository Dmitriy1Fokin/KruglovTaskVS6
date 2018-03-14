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

typedef struct Point
{
	int x, y;
};

typedef struct Shape
{
	int vertex_num;
	vector<Point> vertexes;
};

string ReadFromTextFile(string pathToText);
vector<string> stringToVector(string mainString);
void PrintElem(string temp);
void Task1();

Shape addVectorShape();
Point addPoint();
void PrintVectorShape(Shape shape);
void PrintPoints(Point point);
int SumOfTopOfShapes(vector<Shape> vShapes);
void GeneralInfoOfShapes(vector<Shape> vShapes);
bool isTringle(Shape shape);
bool isRectangle(Shape shape);
bool isPentagon(Shape shape);
vector<Shape> DeletePentagons(vector<Shape> vShapes);
vector<Point> FirstCoordinate(vector<Shape> vShapes);
void Task2();



int main()
{
	srand(time(0));
	//Task1();
	Task2();

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

void Task1()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	string str = ReadFromTextFile("Text.txt");

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
}

Shape addVectorShape()
{
	int vertexNumBuffer = (rand() % 3) + 3;
	vector<Point> vectorPoint(vertexNumBuffer);
	generate(vectorPoint.begin(), vectorPoint.end(), addPoint);	

	Shape shape;
	shape.vertex_num = vertexNumBuffer;
	shape.vertexes = vectorPoint;

	return shape;
}

Point addPoint()
{
	int x = rand() % 51;
	int y = rand() % 51;
	Point point;
	point.x = x;
	point.y = y;

	return point;
}

void PrintVectorShape(Shape shape)
{
	switch (shape.vertex_num)
	{
	case 3: 
	{
		cout << "Shape: Tringle.\n"; 
		for_each(shape.vertexes.begin(), shape.vertexes.end(), PrintPoints);
	} break;
	case 4: 
	{
		cout << "Shape: Rectangle.\n";
		for_each(shape.vertexes.begin(), shape.vertexes.end(), PrintPoints);
	} break;
	case 5: 
	{
		cout << "Shape: Pentagon.\n";
		for_each(shape.vertexes.begin(), shape.vertexes.end(), PrintPoints);
	} break;
	}
}

void PrintPoints(Point point)
{
	cout << "Point: (" << point.x << ", " << point.y << ")\n";
}

int SumOfTopOfShapes(vector<Shape> vShapes)
{
	int sum(0);
	
	for (int i = 0; i < vShapes.size(); i++)
		sum += vShapes[i].vertex_num;

	return sum;
}

void GeneralInfoOfShapes(vector<Shape> vShapes)
{
	int tringle = count_if(vShapes.begin(), vShapes.end(), isTringle);
	int rectangle = count_if(vShapes.begin(), vShapes.end(), isRectangle);
	int pentagon = count_if(vShapes.begin(), vShapes.end(), isPentagon);

	cout << "Number of shapes:\n";
	cout << "Tringles: " << tringle << endl;
	cout << "Rectangles: " << rectangle << endl;
	cout << "Pentagons: " << pentagon << endl;
}

bool isTringle(Shape shape)
{
	return shape.vertex_num == 3;
}

bool isRectangle(Shape shape)
{
	return shape.vertex_num == 4;
}

bool isPentagon(Shape shape)
{
	return shape.vertex_num == 5;
}

vector<Shape> DeletePentagons(vector<Shape> vShapes)
{
	vShapes.erase(remove_if(vShapes.begin(), vShapes.end(), isPentagon), vShapes.end());
	return vShapes;
}

vector<Point> FirstCoordinate(vector<Shape> vShapes)
{
	vector<Point> vPoint;

	for (int i = 0; i < vShapes.size(); i++)
		vPoint.push_back(vShapes[i].vertexes[0]);

	return vPoint;
}



void Task2()
{
	vector<Shape> vectorShape(3);
	generate(vectorShape.begin(), vectorShape.end(), addVectorShape);
	for_each(vectorShape.begin(), vectorShape.end(), PrintVectorShape);	
	
	int sumOfTop;
	cout << endl <<"Sum of top of the shapes: " << (sumOfTop = SumOfTopOfShapes(vectorShape)) << endl << endl;

	GeneralInfoOfShapes(vectorShape);

	vectorShape = DeletePentagons(vectorShape);
	cout << endl;
	for_each(vectorShape.begin(), vectorShape.end(), PrintVectorShape);

	vector<Point> firstPoints = FirstCoordinate(vectorShape);
	cout << endl;
	for_each(firstPoints.begin(), firstPoints.end(), PrintPoints);
}


