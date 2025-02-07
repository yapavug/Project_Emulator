#include <iostream>
#include <array>

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");

	array<int, 2048> data_mem = { 0 };

	int initial_data[] = { 10, 15, 21, 28, 29, 33, 88, 45, 47, 97, 99 };

	for (int i = 0; i <= initial_data[0]; ++i)
	{
		data_mem[i] = initial_data[i];
	}

	//for (auto elem : data_mem)
	//{
	//	cout << elem << endl;
	//}




	return 0;
}