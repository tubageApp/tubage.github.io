#include <iostream>
using namespace std;
#include<vector>//容器头文件
#include<algorithm>//标准算法的头文件（记住）

void myPrintf(int var)
{
    cout << var << endl;
}
int main() {
    vector<int> v;//STL动态数组容器
    v.push_back(10);//向容器中插入数据
    vector<int>::iterator itbegin = v.begin();//起始迭代器，指向容器中第一个元素
    vector<int>::iterator itend = v.end(); //结束迭代器，指向容器中最后一个元素的下一个位置
    //第一种遍历方式
    while (itbegin != itend)
    {
        cout << *itbegin << endl;
        itbegin++;
    }
    //第二种遍历方式
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << endl;
    }
    //第三种遍历方式
    for_each(v.begin(), v.end(), myPrintf);//STL提供的遍历算法
    return 0;
}
