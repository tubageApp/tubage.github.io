#include<iostream>
using namespace std;

class Person
{
public:
    friend ostream& operator<<(ostream& cout, Person p);
    //前置++重载
    //返回引用是为了：一直对一个数据进行操作
    Person& operator++()
    {
        ++m_A;
        ++m_B;
        return *this;
    }

    //后置++重载
    //返回值是因为：temp是局部变量，函数结束后或被释放
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

//左移运算符<<重载
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