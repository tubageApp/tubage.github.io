#include <iostream>
using namespace std;
#include<vector>//����ͷ�ļ�
#include<algorithm>//��׼�㷨��ͷ�ļ�����ס��

void myPrintf(int var)
{
    cout << var << endl;
}
int main() {
    vector<int> v;//STL��̬��������
    v.push_back(10);//�������в�������
    vector<int>::iterator itbegin = v.begin();//��ʼ��������ָ�������е�һ��Ԫ��
    vector<int>::iterator itend = v.end(); //������������ָ�����������һ��Ԫ�ص���һ��λ��
    //��һ�ֱ�����ʽ
    while (itbegin != itend)
    {
        cout << *itbegin << endl;
        itbegin++;
    }
    //�ڶ��ֱ�����ʽ
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << endl;
    }
    //�����ֱ�����ʽ
    for_each(v.begin(), v.end(), myPrintf);//STL�ṩ�ı����㷨
    return 0;
}
