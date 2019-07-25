#include <iostream>
#include <stdio.h>

using namespace std;

class Car
{
	protected:
		int Engine_cap;
		int price;
	public:
		Car();
		~Car();
		void SetCar(int Engine_cap, int price);
		void ShowCar();
};

Car::Car()
{

}

Car::~Car()
{

}

void Car::SetCar(int Engine_cap, int price)
{
	this->Engine_cap = Engine_cap;
	this->price = price;
}

void Car::ShowCar()
{
	printf("Engine_cap: %d, price: %d\n", this->Engine_cap, this->price);
}

class TRUCK : public Car
{
	private:
		int max_cap;
	public:
		TRUCK();
		~TRUCK();
		void SetTruck(int max_cap);
		void ShowTruck();
};

TRUCK::TRUCK()
{

}

TRUCK::~TRUCK()
{

}

void TRUCK::SetTruck(int max_cap)
{
	this->max_cap = max_cap;
}

void TRUCK::ShowTruck()
{
	printf("max_cap: %d\n", this->max_cap);
}

class SUV : public Car
{
	private:
		int sparetire_num;
	public:
		SUV();
		~SUV();
		void SetSuv(int sparetire_num);
		void ShowSuv();
};

SUV::SUV()
{

}

SUV::~SUV()
{

}

void SUV::SetSuv(int sparetire_num)
{
	this->sparetire_num = sparetire_num;
}

void SUV::ShowSuv()
{
	printf("sparetire_num: %d\n", this->sparetire_num);
}


int main()
{
	SUV p1;
	TRUCK p2;
	p1.SetCar(1,2);
	p2.SetCar(3,4);

	p1.SetSuv(200);
	p2.SetTruck(300);

	p1.ShowCar();
	p1.ShowSuv();

	p2.ShowCar();
	p2.ShowTruck();

	return 0;
}
	

