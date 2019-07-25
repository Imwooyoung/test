#include <iostream>
#include <stdio.h>

using namespace std;

class Person
{
	private:
		char* name;
		int age;
		bool gender;
	public:
		Person();
		~Person();
		void SetPerson(char* name, int age, bool gender);
		void ShowPerson();
};


Person::Person()
{
	cout << "start" << endl;
}

Person::~Person()
{
	cout << "end" << endl;
}

void Person::SetPerson(char* name, int age, bool gender)
{
	this->name = (char*)name;
	this->age = age;
	this->gender = gender;
}

void Person::ShowPerson()
{
	printf("name: %s, age: %d, gender: ", this->name, this->age);
	if(this->gender == true)
		printf("man\n");
	else
		printf("woman\n");
}

