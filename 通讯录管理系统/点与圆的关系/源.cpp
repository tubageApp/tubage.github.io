#include<iostream>
using namespace std;
#include"cricle.h"
#include"point.h"

void isPlace(Cricle& c, Point& p)
{
	int a =
		(p.getX() - c.getCenter().getX()) * (p.getX() - c.getCenter().getX()) +
		(p.getY() - c.getCenter().getY()) * (p.getY() - c.getCenter().getY());
	int b = c.getR() * c.getR();
	if (a == b)
	{
		cout << "点在圆上！" << endl;
	}
	else if (a > b)
	{
		cout << "点在圆外！" << endl;
	}
	else
	{
		cout << "点在圆内！" << endl;
	}
}

int main()
{
	Point p;
	p.setX(10);
	p.setY(5);
	Cricle c;
	c.setR(5);
	Point center;
	center.setX(5);
	center.setY(5);
	c.setCenter(center);

	isPlace(c, p);
	system("pause");
	return 0;
}