#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include"Speaker.h"

class speechManager
{
public:
	//构造函数
	speechManager();

	//菜单功能
	void show_Menu();

	//退出功能
	void exitSystem();

	//所有容器初始化
	void initSpeech();

	//创建选手
	bool createSpeaker();

	//开始比赛
	void startSpeech();

	//抽签
	void drawLots();
	//比赛
	void Speech();

	//显示晋级选手信息
	void showPromote();

	//保存分数
	void saveRecord();

	//读取往届记录
	void loadRecord();

	//查看往届记录
	void viewRecord();

	//清空往届记录
	void clearRecord();

	//查看选手
	void showSpeaker();

	//添加选手
	void addSpeaker();

	//删除选手
	void deleteSpeaker();

	//析构函数
	~speechManager();

	//比赛选手
	vector<Speaker>v1;

	//第一轮晋级选手
	vector<Speaker>v2;

	//胜利选手
	vector<Speaker>vVictory;

	//具体选手
	map<int, vector<string>>mVictory;

	//记录回合数
	int m_Index = 1;

	//记录文件是否存在
	bool fileIsEmpty;
};
