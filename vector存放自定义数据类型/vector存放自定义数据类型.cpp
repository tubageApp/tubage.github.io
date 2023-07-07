#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<algorithm>

class Person
{
public:
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	string m_Name;
	int m_Age;
};

Person func(Person& p)
{
	return p;
}

void test01()
{
	vector<Person> v;
	Person p1("ÍõöÎÔó", 22);
	Person p2("»Æ  ¹·", 21);
	v.push_back(p1);
	v.push_back(p2);

	for (vector<Person>::iterator it = v.begin(); it!= v.end(); it++)
	{
		cout << (*it).m_Name << (*it).m_Age << endl;
	}

	for_each(v.begin(), v.end(), func);
}

int main()
{
	test01();
	system("pause");
	return 0;
}