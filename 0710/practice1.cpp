#include <iostream>

using namespace std;

void swap(int *x, int *y)
{
	*x = 10;
	*y = 20;
}

void swap(double *x, double *y)
{
	*x = 10.1010;
	*y = 20.2020;
}

void swap(char *x, char *y)
{
	*x = 'c';
	*y = 'd';
}

void swap(long int *x, long int *y)
{
	*x = 1000000;
	*y = 2000000;
}


int main()
{
	int num1 = 1, num2 = 2;
	cout << num1 << " " << num2 << endl;
	swap(&num1,&num2);
	cout << num1 << " " << num2 << endl << endl;

	double double1 = 1.1111, double2 = 2.2222;
	cout << double1 << " " << double2 << endl;
	swap(&double1,&double2);
	cout << double1 << " " << double2 << endl << endl;

	char char1 = 'a', char2 = 'b';
	cout << char1 << " " << char2 << endl;
	swap(&char1,&char2);
	cout << char1 << " " << char2 << endl << endl;

	long int long1 = 100, long2 = 200;
	cout << long1 << " " << long2 << endl;
	swap(&long1,&long2);
	cout << long1 << " " << long2 << endl;

	return 0;
}
