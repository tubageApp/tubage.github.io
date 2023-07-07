#pragma once
#include<iostream>
using namespace std;

template<class T>
class MyArray
{
public:
	MyArray(int capacity)
	{
		this->capacity = capacity;
		this->size = 0;
		this->myArray = new T[this->capacity];
	}

	MyArray(const MyArray&arr)
	{
		this->capacity = arr.capacity;
		this->size = arr.size;
		this->myArray = new T[arr->capacity];
		for (int i = 0; i < arr.size; i++)
		{
			this->myArray[i] = arr[i];
		}
	}

	T& operator=(const MyArray& arr)
	{
		if (this->myArray != NULL)
		{
			delete[] this->myArray;
			this->myArray = NULL;
			this->capacity = 0;
			this->size = 0;
		}
		this->capacity = arr.capacity;
		this->size = arr.size;
		this->myArray = new T[arr->capacity];
		for (int i = 0; i < arr.size; i++)
		{
			this->myArray[i] = arr[i];
		}
		return *this;
	}

	void endInsert(const T& var)
	{
		if (this->capacity = this->size)
		{
			return;
		}
		else
		{
			this->myArray[this->size] = var;
			this->size++;
		}
	}

	void endDelete()
	{
		if (this->size == 0)
		{
			return;
		}
		else
		{
			this->size--;
		}
	}

	T& operator[](int& index)
	{
		return this->myArray[index];
	}

	int getCapacity()
	{
		return this->capacity;
	}

	int getSize()
	{
		return this->size;
	}

	~MyArray()
	{
		if (this->myArray != NULL)
		{
			delete[] this->myArray;
			this->myArray = NULL;
		}
	}

private:
	T* myArray;
	int capacity;
	int size;
};


class Person
{
public:
	Person(string name, int age)
	{
		this->Name = name;
		this->Age = age;
	}
	string Name;
	int Age;
};