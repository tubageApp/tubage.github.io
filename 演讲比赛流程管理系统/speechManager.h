#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include"Speaker.h"

class speechManager
{
public:
	//���캯��
	speechManager();

	//�˵�����
	void show_Menu();

	//�˳�����
	void exitSystem();

	//����������ʼ��
	void initSpeech();

	//����ѡ��
	bool createSpeaker();

	//��ʼ����
	void startSpeech();

	//��ǩ
	void drawLots();
	//����
	void Speech();

	//��ʾ����ѡ����Ϣ
	void showPromote();

	//�������
	void saveRecord();

	//��ȡ�����¼
	void loadRecord();

	//�鿴�����¼
	void viewRecord();

	//��������¼
	void clearRecord();

	//�鿴ѡ��
	void showSpeaker();

	//���ѡ��
	void addSpeaker();

	//ɾ��ѡ��
	void deleteSpeaker();

	//��������
	~speechManager();

	//����ѡ��
	vector<Speaker>v1;

	//��һ�ֽ���ѡ��
	vector<Speaker>v2;

	//ʤ��ѡ��
	vector<Speaker>vVictory;

	//����ѡ��
	map<int, vector<string>>mVictory;

	//��¼�غ���
	int m_Index = 1;

	//��¼�ļ��Ƿ����
	bool fileIsEmpty;
};
