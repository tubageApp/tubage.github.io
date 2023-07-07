#include<iostream>
using namespace std;

class Person
{
public:
    friend ostream& operator<<(ostream& cout, Person p);
    //ǰ��++����
    //����������Ϊ�ˣ�һֱ��һ�����ݽ��в���
    Person& operator++()
    {
        ++m_A;
        ++m_B;
        return *this;
    }

    //����++����
    //����ֵ����Ϊ��temp�Ǿֲ�������������������ͷ�
    Person operator++(int)
    {
        Person temp = *this;
        m_A++;
        m_B++;
        return temp;
    }

public:
    Person(int a, int b)
    {
        this->m_A = a;
        this->m_B = b;
    }

private:
    int m_A;
    int m_B;
};

//���������<<����
ostream& operator<<(ostream& cout, Person p)
{
    cout << "m_A=" << p.m_A << "\tm_B=" << p.m_B << endl;
    return cout;
}


void test01()
{
    Person p1(10, 10);
    cout << p1 << endl;
}

void test02()
{
    Person p2(20, 20);
    cout << ++p2 << endl;
}

void test03()
{
    Person p3(30, 30);
    cout << p3++ << endl;
    cout << p3 << endl;
    cout << p3 << endl;
    cout << ++p3 << endl;
}

int main()
{
    test01();
    test02();
    test03();
    system("pause");
    return 0;
}