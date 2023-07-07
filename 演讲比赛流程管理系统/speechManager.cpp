#include"speechManager.h"
#include"Speaker.h"
#include<fstream>
#include<vector>
#include<algorithm>
#include<map>
#include<deque>
#include<numeric>

speechManager::speechManager()
{
	//初始化容器和属性
	this->initSpeech();

	//创建12名选手
	this->createSpeaker();
}

//菜单功能
void speechManager::show_Menu()
{
	cout << "-欢迎参加演讲比赛-" << endl;
	cout << " 1、查看参赛选手" << endl;
	cout << " 2、添加参赛选手" << endl;
	cout << " 3、删除参赛选手" << endl;
	cout << " 4、开始演讲比赛" << endl;
	cout << " 5、查看往届记录" << endl;
	cout << " 6、清空比赛记录" << endl;
	cout << " 7、退出比赛系统" << endl;
}

//退出功能
void speechManager::exitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

//所有容器初始化
void speechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->mVictory.clear();

	//初始化比赛轮数
	this->m_Index = 1;
}

//创建选手
bool speechManager::createSpeaker()
{
	v1.clear();
	ifstream ifs;
	string name;
	int key = 1;
	ifs.open("speechMaker.csv", ios::in);
	while (ifs >> name && v1.size() < 12)
	{
		Speaker s;
		s.m_Name = name;
		for (int i = 0; i < 2; i++)
		{
			s.m_Score[i] = 0;
		}
		v1.push_back(s);
		key++;
	}
	if (v1.size() == 12)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//查看选手
void speechManager::showSpeaker()
{
	int index = 1;
	for (vector<Speaker>::iterator it = v1.begin(); it != v1.end(); it++,index++)
	{
		cout << "选手" << index << "号：" << it->m_Name << endl;
	}
	system("pause");
	system("cls");
}

//添加选手
void speechManager::addSpeaker()
{
	if (v1.size() < 12)
	{
		ofstream ofs("speechMaker.csv", ios::out | ios::app);
		string temp;
		cout << "请输入选手姓名！" << endl;
		cin >> temp;
		for (vector<Speaker>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			if (it->m_Name == temp)
			{
				cout << "该选手已存在！" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
		ofs << temp << endl;
		ofs.close();
		this->createSpeaker();
		cout << "添加成功" << endl;
	}
	else
	{
		cout << "选手已经达到12个，无需添加！" << endl;
	}
	system("pause");
	system("cls");
}



//删除选手
void speechManager::deleteSpeaker()
{
	int index;
	string temp;
	cout << "请输入想要删除的选手的姓名！" << endl;
	cin >> temp;
	cout << "确认删除？\t" << "1、确认\t" << "2、返回\t" << endl;
	cin >> index;
	if (index == 1)
	{
		for (vector<Speaker>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			if (it->m_Name == temp)
			{
				v1.erase(it);
				ofstream ofs("speechMaker.csv", ios::out | ios::trunc);
				for (vector<Speaker>::iterator it = v1.begin(); it != v1.end(); it++)
				{
					ofs << it->m_Name << endl;
				}
				cout << "删除成功！" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
		cout << "该选手不存在！" << endl;
	}
	system("pause");
	system("cls");
}

//查看往届记录
void speechManager::viewRecord()
{
	ifstream ifs;
	ifs.open("speech.csv", ios::in);

	if (!ifs.is_open())
	{
		cout << "文件不存在！" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		system("pause");
		system("cls");
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空！" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		system("pause");
		system("cls");
		return;
	}

	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch);//读取的单个字符放回去
	string buf;
	int index = 1;
	while (ifs >> buf)
	{
		//cout << buf << endl;
		vector<string>v;
		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = buf.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string temp = buf.substr(start, pos - start);
			//cout << temp << "分\t";
			v.push_back(temp);
			start = pos + 1;
		}
		this->mVictory.insert(make_pair(index, v));
		v.clear();
		index++;
	}
	cout << endl;
	//关闭文件
	ifs.close();

	for (map<int, vector<string>>::iterator it = mVictory.begin(); it != mVictory.end(); it++)
	{
		cout << "第" << it->first << "届\t" << "冠军：" << it->second[0] << it->second[1] << "分\t";
		cout << "亚军：" << it->second[2] << it->second[3] << "分\t";
		cout << "季军：" << it->second[4] << it->second[5] << "分\t" << endl;
	}
	system("pause");
	system("cls");
}

//清空往届记录
void speechManager::clearRecord()
{
	cout << "确认清空？\t" << "1、确认\t" << "2、返回\t" <<endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		cout << "记录已清空！" << endl;
	}
	
	system("pause");
	system("cls");
}

//开始比赛
void speechManager::startSpeech()
{

	if (createSpeaker())
	{
		//第一轮比赛
			//抽签
		drawLots();

		//比赛
		Speech();

		//显示晋级选手信息
		showPromote();

		//第二轮比赛
		this->m_Index++;

		//抽签
		drawLots();

		//比赛
		Speech();

		//显示胜利选手信息
		showPromote();

		//保存分数
		saveRecord();

		this->m_Index--;
	}
	else
	{
		cout << "参赛人数不够请添加参赛人员！" << endl;
	}
	system("pause");
	system("cls");
}


//抽签
void speechManager::drawLots()
{
	cout << "现在进行第 " << m_Index << " 轮随机抽签进行演讲" << endl;
	system("pause");
	if (m_Index == 1)
	{
		int num = 0;
		random_shuffle(v1.begin(), v1.end());
		cout << "第一组：";
		for (vector<Speaker>::iterator it = v1.begin(); it != v1.end(); it++,num++)
		{
			if (num == 6)
			{
				cout << endl;
				cout << "第二组：";
			}
			cout << it->m_Name<<"  ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<Speaker>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << it->m_Name << "  ";
		}
		cout << endl;
	}
}

//比赛
void speechManager::Speech()
{
	int num = 0;
	multimap<double, Speaker, greater<double>>mlt;
	if (m_Index == 1)
	{
		v2.clear();
		cout << endl;
		cout << "现在进行第 " << m_Index << " 轮演讲评委打分，并计算平均分" << endl;
		system("pause");
		for (vector<Speaker>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			num++;
			deque<double>d1;
			double score = 0;
			for (int i = 0; i < 10; i++)
			{
				int temp = rand() % 40 + 60;
				d1.push_back(temp);
			}
			sort(d1.begin(), d1.end(), greater<double>());
			d1.pop_back();
			d1.pop_front();
			double sum = accumulate(d1.begin(), d1.end(),0.0f);
			double avg = sum / size(d1);
			it->m_Score[m_Index - 1] = avg;
			//cout << it->m_Name << it->m_Score[m_Index - 1] << "分\t";
			mlt.insert(make_pair(avg, *it));
			if (num % 6 == 0)
			{
				int count = 0;
				for (multimap<double, Speaker, greater<double>>::iterator it = mlt.begin(); it != mlt.end(); it++,count++)
				{
					cout << it->second.m_Name << it->second.m_Score[m_Index - 1] << "分\t";
					if (count < 3)
					{
						v2.push_back(it->second);
					}
				}
				mlt.clear();
				cout << endl;
			}
		}
		cout << endl;
		cout << "第 " << m_Index << " 轮演讲比赛完毕！" << endl;
	}
	else
	{
		vVictory.clear();
		int num = 0;
		cout << endl;
		cout << "现在进行第 " << m_Index << " 轮演讲评委打分，并计算平均分" << endl;
		system("pause");
		for (vector<Speaker>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			double score = 0;
			for (int i = 0; i < 10; i++)
			{
				int temp = rand() % 40 + 60;
				score += temp;
			}
			double avg = score / 10;
			it->m_Score[m_Index - 1] = avg;
			mlt.insert(make_pair(avg, *it));
		}
		int count = 0;
		for (multimap<double, Speaker, greater<double>>::iterator it = mlt.begin(); it != mlt.end(); it++, count++)
		{
			cout << it->second.m_Name << it->second.m_Score[m_Index - 1] << "分\t";
			if (count < 3)
			{
				vVictory.push_back(it->second);
			}
		}
		cout << endl;
		cout << "第 " << m_Index << " 轮演讲比赛完毕！" << endl;
	}
}

//显示晋级选手信息
void speechManager::showPromote()
{
	cout << "晋级的选手：" << endl;
	vector<Speaker>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}
	for (vector<Speaker>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << it->m_Name << it->m_Score[m_Index - 1] << "分\t";
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}

//保存分数
void speechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<Speaker>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << it->m_Name << "," << it->m_Score[this->m_Index - 1] << ",";
	}
	ofs << endl;

	//关闭文件
	ofs.close();

	cout << "记录已保存" << endl;
}


speechManager::~speechManager()
{

}