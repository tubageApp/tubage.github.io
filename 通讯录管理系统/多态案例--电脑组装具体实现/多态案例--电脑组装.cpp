#include<iostream>
using namespace std;

//CPU抽象类
class CPU
{
public:
	virtual void calculate() = 0;
};

//显卡抽象类
class VideoCard
{
public:
	virtual void display() = 0;
};

//内存条抽象类
class MemoryBank
{
public:
	virtual void memory() = 0;
};

//计算器类
class Computer
{
public:
	Computer(CPU* cpu, VideoCard* vc, MemoryBank* mb)
	{
		m_cpu = cpu;
		m_vc = vc;
		m_mb = mb;
	}

	void work()
	{
		m_cpu->calculate();
		m_vc->display();
		m_mb->memory();
	}

	~Computer()
	{
		if (m_cpu != NULL)
		{
			delete m_cpu;
			m_cpu = NULL;
		}
		if (m_vc != NULL)
		{
			delete m_vc;
			m_vc = NULL;
		}
		if (m_mb != NULL)
		{
			delete m_mb;
			m_mb = NULL;
		}
	}

private:
	CPU* m_cpu;
	VideoCard* m_vc;
	MemoryBank* m_mb;
};

class IntelCPU:public CPU
{
	virtual void calculate()
	{
		cout << "Intel的CPU开始计算了" << endl;
	}
};

class IntelVideoCard:public VideoCard
{
	virtual void display()
	{
		cout << "Intel的显卡开始显示了" << endl;
	}
};

class IntelMemoryBank:public MemoryBank
{
	virtual void memory()
	{
		cout << "Intel的内存条开始存储了" << endl;
	}
};

class LenovoCPU :public CPU
{
	virtual void calculate()
	{
		cout << "Lenovo的CPU开始计算了" << endl;
	}
};

class LenovoVideoCard :public VideoCard
{
	virtual void display()
	{
		cout << "Lenovo的显卡开始显示了" << endl;
	}
};

class LenovoMemoryBank :public MemoryBank
{
	virtual void memory()
	{
		cout << "Lenovo的内存条开始存储了" << endl;
	}
};

void test01()
{
	Computer* computer1 = new Computer(new IntelCPU, new IntelVideoCard, new IntelMemoryBank);
	computer1->work();
	delete computer1;
	cout << "--------------------------" << endl;
	Computer* computer2 = new Computer(new LenovoCPU, new LenovoVideoCard, new LenovoMemoryBank);
	computer2->work();
	delete computer2;
	cout << "--------------------------" << endl;
	Computer* computer3 = new Computer(new LenovoCPU, new IntelVideoCard, new LenovoMemoryBank);
	computer3->work();
	delete computer3;
}

int main()
{
	test01();
	system("pause");
	return 0;
}