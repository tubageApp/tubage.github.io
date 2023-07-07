#include<iostream>
using namespace std;
#include<fstream>

int main()
{
	ofstream ofs;
	ofs.open("test.txt", ios::out);
	ofs << "¶ÎÌÎ" << endl;
	ofs.close();

	system("pause");
	return 0;
}