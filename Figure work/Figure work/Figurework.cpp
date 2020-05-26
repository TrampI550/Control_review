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
		cout << "����" << endl
			<< "1. ������� �������" << endl
			<< "2. ������� �����������" << endl
			<< "3. ������� ����" << endl
			<< "4. ������� ������������" << endl
			<< "5. ���������� ������� ��������� �����" << endl
		    << "6. �����" << endl;
		cin >> choise;

		switch (choise)
		{
		case 1:
		{
			double side;
			TryAgainSquare:
			cout << "�������:" << endl;
			cout << "������� ����� �������: ";
			cin >> side;
			if (side == 0)
			{
				cout << "������ ������� �����������, ��������� �������" << endl;
				goto TryAgainSquare;
			}
			cout << "�������� ������� " << endl;

			shapes.push_back(new Square(side));

			break;
		}

		case 2:
		{
			double side_a, side_b, side_c;
			TryAgainTriangle:
			cout << "�����������:" << endl;
			cout << "������� ����� ������� a: ";
			cin >> side_a;
			cout << "������� ����� ������� b: ";
			cin >> side_b;
			cout << "������� ����� ������� c: ";
			cin >> side_c;

			if (side_a >= side_b + side_c || side_b >= side_a + side_c || side_c >= side_a + side_b)
			{
				cout << "������ ������� �����������, ��������� �������" << endl;
				goto TryAgainTriangle;
			}

			cout << "�������� ����������� " << endl;

			shapes.push_back(new Triangle(side_a, side_b, side_c));

			break;
		}

		case 3:
		{
			double radius;
			TryAgainCircle:
			cout << "����:" << endl;
			cout << "������� ����� �������: ";
			cin >> radius;

			if (radius == 0)
			{
				cout << "������ ������� �����������, ��������� �������" << endl;
				goto TryAgainCircle;
			}

			cout << "�������� ���� " << endl;

			shapes.push_back(new Circle(radius));

			break;
		}

		case 4:
		{
			double side_a, side_b;
			TryAgainRectangle:
			cout << "�������������:" << endl;
			cout << "������� ����� ������� a: ";
			cin >> side_a;
			cout << "������� ����� ������� b: ";
			cin >> side_b;

			if (side_b == 0||side_a==0)
			{
				cout << "������ ������� �����������, ��������� �������" << endl;
				goto TryAgainRectangle;
			}

			cout << "�������� ������������� " << endl;

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
					cout << "�������.     ������� = ";

				if (triangle_pointer != 0)
					cout << "�����������. ������� = ";

				if (circle_pointer != 0)
					cout << "����.        ������� = ";

				if (rectangle_pointer != 0)
					cout << "�������������. ������� = ";

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
			cout << "������������ ��������, ��������� �������" << endl;
			break;
		}
		};
	} while (choise != 6);

	size_t size = shapes.size();

	for (size_t i = 0; i < size; ++i)
		delete shapes[i];

	return 0;
}