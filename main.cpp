#include <iostream>
#include <array>
#include <map>
#include <vector>

using namespace std;


void show_registers(const map<string, int>& registers, const vector<string>& order) {
	cout << "��������� ���������:\n";
	for (const auto& key : order) {
		cout << key << ":\t" << registers.at(key) << "\n";
	}
}



int main()
{
	setlocale(LC_ALL, "ru");

	array<int, 2048> data_mem = { 0 };

	int initial_data[] = { 10, 15, 21, 28, 29, 33, 88, 45, 47, 97, 99 };

	for (int i = 0; i <= initial_data[0]; ++i)
	{
		data_mem[i] = initial_data[i];
	}

	for (auto elem : data_mem)
	{
		cout << elem << " ";
	}
	cout << endl << endl << endl;


	array<int, 2048> instruct_mem = { 0 };

	int initial_instructions[] = { 
		1, 7, 0, 255,
		10, 8, 107, 255,
		1, 9, 171, 255,
		2, 10, 7, 9,
		10, 13, 110, 255,
		1, 15, 8, 255,
		8, 15, 15, 255,
		4, 15, 255, 255,
		5, 17, 255, 255,
		2, 10, 171, 255,
		10, 14, 110, 255,
		4, 14, 13, 255,
		6, 15, 255, 255,
		1, 13, 14, 255,
		8, 15, 15, 255,
		7, 8, 255, 255,
		1, 16, 13, 255,
		1, 13, 230, 255,
		9, 255, 255, 255 };


	// ���������� ��������� � initial_instructions
	int initial_size = sizeof(initial_instructions) / sizeof(initial_instructions[0]);

	// �������� �������� �� initial_instructions � instruct_mem
	for (int i = 0; i < initial_size; ++i) {
		instruct_mem[i] = initial_instructions[i];
	}

	for (int i = 0; i < instruct_mem.size(); ++i) {
		cout<< instruct_mem[i]<<" ";
	}

	map<string, int> REGISTERS;
	REGISTERS["r0"] = 7;
	REGISTERS["r1"] = 8;
	REGISTERS["r2"] = 9;
	REGISTERS["r3"] = 10;
	REGISTERS["r4"] = 11;
	REGISTERS["r5"] = 12;
	REGISTERS["rax"] = 13;
	REGISTERS["rbx"] = 14;
	REGISTERS["rcx"] = 15;
	REGISTERS["rdi"] = 16;

	map<string, int> regs = {

		{"r0", 0},		//����� ������� ����� ������ ����� ������ ������ � ������ data_memory ([0])
		{"r1", 0},		//����� ������� ����� � ���� ������������ ������ ��-� ������� - ���������� ��������� � �������  (10)
		{"r2", 0},		//����� ������� ����� ������ ��������, ����������� ��� ������� �� ������� ��-�� ������� ������ � data_memory (1)
		{"r3", 0},		//����� ������� ����� ������ ����� ������� �������� ������� � ������ data_memory ([1])
		{"rax", 0},		//������� ������ ������ ������� ������� (15) - ������� ��������
		{"rbx", 0},		//������ ������� �������
		{"rcx", 0},		//�������
		{"rdi", 0},		//� ���� ����������� �������� ����� hlt
		{"eflags", 0},	//���� ��� �������� ���������

	};

	cout << endl << endl << endl;

	vector<string> order = { "r0", "r1", "r2", "r3", "rax", "rbx", "rcx", "rdi", "eflags" };

	show_registers(regs, order);

	return 0;
}