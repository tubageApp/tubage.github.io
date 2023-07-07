#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<deque>
#include<ctime>
#include<algorithm>

class Person
{
public:
	Person(string name, int score)
	{
		this->m_Name = name;
		this->m_Score = score;
	}

	string m_Name;
	int m_Score;
};

//标识符<<重载
ostream &operator<<(ostream& cout, Person& p)
{
	cout << p.m_Name << "\t的分数:" << p.m_Score << endl;
	return cout;
}

//创建5名选手i放在vector容器
void getPerson(vector<Person>&v)
{
	string name;
	int score = 0;
	string sName = "12345";
	for (int i = 0; i < 5; i++)
	{
		name = "选手";
		name += sName[i];
		Person p(name, score);
		v.push_back(p);
	}
	//测试：
	//for(vector<Person>::iterator it = v1.begin();it!=v1.end();it++)
	//{
	//	cout << *it << endl;
	//}
}

//获得分数，并计算平均分
void getScore(vector<Person>&v)
{
	//srand((unsigned int)time(NULL));    放在此处也行，但不可以放在循环内
	for (vector<Person>::iterator it=v.begin();it!=v.end();it++)
	{
		int score;
		deque<int>d1;
		for (int i = 0; i < 10; i++)
		{
			score = rand() % 41 + 60;
			d1.push_back(score);
		}
		//for(deque<int>::iterator it = d1.begin();it!=d1.end();it++)
		//{
		//	cout << *it << endl;
		//}
		sort(d1.begin(), d1.end());
		d1.pop_back();
		d1.pop_front();
		score = 0;
		for (int i = 0; i < d1.size(); i++)
		{
			score += d1[i];
		}
		int avg = score / d1.size();
		it->m_Score = avg;
	}
}

void printPerson(vector<Person>& v)
{
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
}

void test01()
{
	//随机数种子
	srand((unsigned int)time(NULL));
	//创建5名选手
	vector<Person>v1;
	getPerson(v1);
	//获得平均分
	getScore(v1);
	//打印五名选手成绩
	printPerson(v1);
}

int main()
{
	test01();
	system("pause");
	return 0;
}