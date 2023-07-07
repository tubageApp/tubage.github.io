#include"cricle.h"
#include"point.h"

void Cricle::setR(int r)
{
	m_R = r;
}
int Cricle::getR()
{
	return m_R;
}

void Cricle::setCenter(Point& center)
{
	m_Center = center;
}
Point Cricle::getCenter()
{
	return m_Center;
}
