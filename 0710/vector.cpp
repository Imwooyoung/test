#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
	vector<int>v;

	v.push_back(1);
	v.push_back(9);
	v.push_back(5);
	v.push_back(6);
	v.push_back(2);

	cout << "[v.at(i)]: ";
	for(int i=0;i<v.size();i++){
		cout << v.at(i) << " ";
	}
	cout <<"[v[i]]: ";
	for(int i=0;i<v.size();i++){
		cout << v[i] << " ";
	}

	cout << endl << endl;
	cout << "[*iter] iterator: ";
	vector<int>::iterator iter;
	for(iter=v.begin();iter!=v.end();iter++){
		cout << *iter << "";
	}
	cout << endl <<endl;

	return 0;
}
