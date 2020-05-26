#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
class Shape
{
public:
	virtual double area() const = 0;
};

class Square : public Shape
{
public:
	Square(double size = 1.0) :
		_side(size)
	{
	}

	virtual double area() const
	{
		return _side * _side;
	}

private:
	double _side;
};

class Triangle : public Shape
{
public:
	Triangle(double side_a = 3.0, double side_b = 4.0, double side_c = 5.0) :
		_side_a(side_a),
		_side_b(side_b),
		_side_c(side_c)
	{
	}

	virtual double area() const
	{
		double p = (_side_a + _side_b + _side_c) / 2.0;

		return sqrt(p * (p - _side_a) * (p - _side_b) * (p - _side_c));
	}

private:
	double _side_a;
	double _side_b;
	double _side_c;
};
class Rectangle : public Shape
{
public:
	Rectangle(double side_a = 3.0, double side_b = 4.0) :
		_side_a(side_a),
		_side_b(side_b)
	{
	}

	virtual double area() const
	{
		return _side_a * _side_b;
	}

private:
	double _side_a;
	double _side_b;
};

class Circle : public Shape
{
	static const double Pi;

public:
	Circle(double radius = 1.0) :
		_radius(radius)
	{
	}

	virtual double area() const
	{
		return Pi * _radius * _radius;
	}

private:
	double _radius;
};

const double Circle::Pi = 3.1415;

int main()
{
	setlocale(LC_ALL, "Rus");

	vector< Shape* > shapes;
	size_t choise;

	do
	{
		cout << "Меню" << endl
			<< "1. Создать квадрат" << endl
			<< "2. Создать треугольник" << endl
			<< "3. Создать круг" << endl
			<< "4. Создать прямоугльник" << endl
			<< "5. Рассчитать площади созданных фигур" << endl
		    << "6. Выйти" << endl;
		cin >> choise;

		switch (choise)
		{
		case 1:
		{
			double side;
			TryAgainSquare:
			cout << "Квадрат:" << endl;
			cout << "Введите длину стороны: ";
			cin >> side;
			if (side == 0)
			{
				cout << "Данные введены неправильно, повторите попытку" << endl;
				goto TryAgainSquare;
			}
			cout << "Рисуется квадрат " << endl;

			shapes.push_back(new Square(side));

			break;
		}

		case 2:
		{
			double side_a, side_b, side_c;
			TryAgainTriangle:
			cout << "Треугольник:" << endl;
			cout << "Введите длину стороны a: ";
			cin >> side_a;
			cout << "Введите длину стороны b: ";
			cin >> side_b;
			cout << "Введите длину стороны c: ";
			cin >> side_c;

			if (side_a >= side_b + side_c || side_b >= side_a + side_c || side_c >= side_a + side_b)
			{
				cout << "Данные введены неправильно, повторите попытку" << endl;
				goto TryAgainTriangle;
			}

			cout << "Рисуется треугольник " << endl;

			shapes.push_back(new Triangle(side_a, side_b, side_c));

			break;
		}

		case 3:
		{
			double radius;
			TryAgainCircle:
			cout << "Круг:" << endl;
			cout << "Введите длину радиуса: ";
			cin >> radius;

			if (radius == 0)
			{
				cout << "Данные введены неправильно, повторите попытку" << endl;
				goto TryAgainCircle;
			}

			cout << "Рисуется круг " << endl;

			shapes.push_back(new Circle(radius));

			break;
		}

		case 4:
		{
			double side_a, side_b;
			TryAgainRectangle:
			cout << "Прямоугольник:" << endl;
			cout << "Введите длину стороны a: ";
			cin >> side_a;
			cout << "Введите длину стороны b: ";
			cin >> side_b;

			if (side_b == 0||side_a==0)
			{
				cout << "Данные введены неправильно, повторите попытку" << endl;
				goto TryAgainRectangle;
			}

			cout << "Рисуется прямоугольник " << endl;

			shapes.push_back(new Rectangle(side_a, side_b));

			break;
		}

		case 5:
		{
			Square* square_pointer;
			Triangle* triangle_pointer;
			Circle* circle_pointer;
			Rectangle* rectangle_pointer;
			size_t size = shapes.size();

			for (size_t i = 0; i < size; ++i)
			{
				square_pointer = dynamic_cast<Square*>(shapes[i]);
				triangle_pointer = dynamic_cast<Triangle*>(shapes[i]);
				circle_pointer = dynamic_cast<Circle*>(shapes[i]);
				rectangle_pointer = dynamic_cast<Rectangle*>(shapes[i]);

				if (square_pointer != 0)
					cout << "Квадрат.     Площадь = ";

				if (triangle_pointer != 0)
					cout << "Треугольник. Площадь = ";

				if (circle_pointer != 0)
					cout << "Круг.        Площадь = ";

				if (rectangle_pointer != 0)
					cout << "Прямоугольник. Площадь = ";

				cout << shapes[i]->area() << endl;
			}

			break;
		}
		case 6:
		{

		}
		break;

		default:
		{
			cout << "Неправильное значение, повторите попытку" << endl;
			break;
		}
		};
	} while (choise != 6);

	size_t size = shapes.size();

	for (size_t i = 0; i < size; ++i)
		delete shapes[i];

	return 0;
}