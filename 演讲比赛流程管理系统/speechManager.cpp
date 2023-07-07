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
	//��ʼ������������
	this->initSpeech();

	//����12��ѡ��
	this->createSpeaker();
}

//�˵�����
void speechManager::show_Menu()
{
	cout << "-��ӭ�μ��ݽ�����-" << endl;
	cout << " 1���鿴����ѡ��" << endl;
	cout << " 2����Ӳ���ѡ��" << endl;
	cout << " 3��ɾ������ѡ��" << endl;
	cout << " 4����ʼ�ݽ�����" << endl;
	cout << " 5���鿴�����¼" << endl;
	cout << " 6����ձ�����¼" << endl;
	cout << " 7���˳�����ϵͳ" << endl;
}

//�˳�����
void speechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

//����������ʼ��
void speechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->mVictory.clear();

	//��ʼ����������
	this->m_Index = 1;
}

//����ѡ��
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

//�鿴ѡ��
void speechManager::showSpeaker()
{
	int index = 1;
	for (vector<Speaker>::iterator it = v1.begin(); it != v1.end(); it++,index++)
	{
		cout << "ѡ��" << index << "�ţ�" << it->m_Name << endl;
	}
	system("pause");
	system("cls");
}

//���ѡ��
void speechManager::addSpeaker()
{
	if (v1.size() < 12)
	{
		ofstream ofs("speechMaker.csv", ios::out | ios::app);
		string temp;
		cout << "������ѡ��������" << endl;
		cin >> temp;
		for (vector<Speaker>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			if (it->m_Name == temp)
			{
				cout << "��ѡ���Ѵ��ڣ�" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
		ofs << temp << endl;
		ofs.close();
		this->createSpeaker();
		cout << "��ӳɹ�" << endl;
	}
	else
	{
		cout << "ѡ���Ѿ��ﵽ12����������ӣ�" << endl;
	}
	system("pause");
	system("cls");
}



//ɾ��ѡ��
void speechManager::deleteSpeaker()
{
	int index;
	string temp;
	cout << "��������Ҫɾ����ѡ�ֵ�������" << endl;
	cin >> temp;
	cout << "ȷ��ɾ����\t" << "1��ȷ��\t" << "2������\t" << endl;
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
				cout << "ɾ���ɹ���" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
		cout << "��ѡ�ֲ����ڣ�" << endl;
	}
	system("pause");
	system("cls");
}

//�鿴�����¼
void speechManager::viewRecord()
{
	ifstream ifs;
	ifs.open("speech.csv", ios::in);

	if (!ifs.is_open())
	{
		cout << "�ļ������ڣ�" << endl;
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
		cout << "�ļ�Ϊ�գ�" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		system("pause");
		system("cls");
		return;
	}

	//�ļ���Ϊ��
	this->fileIsEmpty = false;
	ifs.putback(ch);//��ȡ�ĵ����ַ��Ż�ȥ
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
			//cout << temp << "��\t";
			v.push_back(temp);
			start = pos + 1;
		}
		this->mVictory.insert(make_pair(index, v));
		v.clear();
		index++;
	}
	cout << endl;
	//�ر��ļ�
	ifs.close();

	for (map<int, vector<string>>::iterator it = mVictory.begin(); it != mVictory.end(); it++)
	{
		cout << "��" << it->first << "��\t" << "�ھ���" << it->second[0] << it->second[1] << "��\t";
		cout << "�Ǿ���" << it->second[2] << it->second[3] << "��\t";
		cout << "������" << it->second[4] << it->second[5] << "��\t" << endl;
	}
	system("pause");
	system("cls");
}

//��������¼
void speechManager::clearRecord()
{
	cout << "ȷ����գ�\t" << "1��ȷ��\t" << "2������\t" <<endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		cout << "��¼����գ�" << endl;
	}
	
	system("pause");
	system("cls");
}

//��ʼ����
void speechManager::startSpeech()
{

	if (createSpeaker())
	{
		//��һ�ֱ���
			//��ǩ
		drawLots();

		//����
		Speech();

		//��ʾ����ѡ����Ϣ
		showPromote();

		//�ڶ��ֱ���
		this->m_Index++;

		//��ǩ
		drawLots();

		//����
		Speech();

		//��ʾʤ��ѡ����Ϣ
		showPromote();

		//�������
		saveRecord();

		this->m_Index--;
	}
	else
	{
		cout << "����������������Ӳ�����Ա��" << endl;
	}
	system("pause");
	system("cls");
}


//��ǩ
void speechManager::drawLots()
{
	cout << "���ڽ��е� " << m_Index << " �������ǩ�����ݽ�" << endl;
	system("pause");
	if (m_Index == 1)
	{
		int num = 0;
		random_shuffle(v1.begin(), v1.end());
		cout << "��һ�飺";
		for (vector<Speaker>::iterator it = v1.begin(); it != v1.end(); it++,num++)
		{
			if (num == 6)
			{
				cout << endl;
				cout << "�ڶ��飺";
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

//����
void speechManager::Speech()
{
	int num = 0;
	multimap<double, Speaker, greater<double>>mlt;
	if (m_Index == 1)
	{
		v2.clear();
		cout << endl;
		cout << "���ڽ��е� " << m_Index << " ���ݽ���ί��֣�������ƽ����" << endl;
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
			//cout << it->m_Name << it->m_Score[m_Index - 1] << "��\t";
			mlt.insert(make_pair(avg, *it));
			if (num % 6 == 0)
			{
				int count = 0;
				for (multimap<double, Speaker, greater<double>>::iterator it = mlt.begin(); it != mlt.end(); it++,count++)
				{
					cout << it->second.m_Name << it->second.m_Score[m_Index - 1] << "��\t";
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
		cout << "�� " << m_Index << " ���ݽ�������ϣ�" << endl;
	}
	else
	{
		vVictory.clear();
		int num = 0;
		cout << endl;
		cout << "���ڽ��е� " << m_Index << " ���ݽ���ί��֣�������ƽ����" << endl;
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
			cout << it->second.m_Name << it->second.m_Score[m_Index - 1] << "��\t";
			if (count < 3)
			{
				vVictory.push_back(it->second);
			}
		}
		cout << endl;
		cout << "�� " << m_Index << " ���ݽ�������ϣ�" << endl;
	}
}

//��ʾ����ѡ����Ϣ
void speechManager::showPromote()
{
	cout << "������ѡ�֣�" << endl;
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
		cout << it->m_Name << it->m_Score[m_Index - 1] << "��\t";
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}

//�������
void speechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<Speaker>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << it->m_Name << "," << it->m_Score[this->m_Index - 1] << ",";
	}
	ofs << endl;

	//�ر��ļ�
	ofs.close();

	cout << "��¼�ѱ���" << endl;
}


speechManager::~speechManager()
{

}