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

//��ʶ��<<����
ostream &operator<<(ostream& cout, Person& p)
{
	cout << p.m_Name << "\t�ķ���:" << p.m_Score << endl;
	return cout;
}

//����5��ѡ��i����vector����
void getPerson(vector<Person>&v)
{
	string name;
	int score = 0;
	string sName = "12345";
	for (int i = 0; i < 5; i++)
	{
		name = "ѡ��";
		name += sName[i];
		Person p(name, score);
		v.push_back(p);
	}
	//���ԣ�
	//for(vector<Person>::iterator it = v1.begin();it!=v1.end();it++)
	//{
	//	cout << *it << endl;
	//}
}

//��÷�����������ƽ����
void getScore(vector<Person>&v)
{
	//srand((unsigned int)time(NULL));    ���ڴ˴�Ҳ�У��������Է���ѭ����
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
	//���������
	srand((unsigned int)time(NULL));
	//����5��ѡ��
	vector<Person>v1;
	getPerson(v1);
	//���ƽ����
	getScore(v1);
	//��ӡ����ѡ�ֳɼ�
	printPerson(v1);
}

int main()
{
	test01();
	system("pause");
	return 0;
}