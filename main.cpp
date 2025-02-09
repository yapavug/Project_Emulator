#include <iostream>
#include <array>
#include <map>
#include <vector>
#include <cstdlib> // ��������� ��� exit(0)


#include "show_registers.h"
#include "execute_machine_instruction.h"


int main()
{
	setlocale(LC_ALL, "ru");

	std::array<int, 2048> data_mem = { 0 };

	int initial_data[] = { 10, 15, 21, 28, 29, 33, 88, 100, 47, 97, 99 };

	for (int i = 0; i <= initial_data[0]; ++i)
	{
		data_mem[i] = initial_data[i];
	}

	for (auto elem : data_mem)
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl << std::endl << std::endl;


	std::array<int, 2048> instruct_mem = { 0 };

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
		std::cout<< instruct_mem[i]<<" ";
	}

	std::map<std::string, int> REGISTERS;
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

	std::map<std::string, int> regs = {

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

	std::cout << std::endl << std::endl << std::endl;

	std::vector<std::string> order = { "r0", "r1", "r2", "r3", "rax", "rbx", "rcx", "rdi", "eflags" };

	show_registers(regs, order);

	std::cout << std::endl << std::endl;

	int pc = 0;		//������� ������ - �������

	std::vector<int> instruction;

	while (pc < instruct_mem.size()) {
		// �������� ������ 4 ��������
		instruction.assign(instruct_mem.begin() + pc, instruct_mem.begin() + pc + 4);

		// ������� ����������� �������
		std::cout << "����������� �������: ";
		for (int elem : instruction) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;

		// ��������� �������
		int jump_to = execute_machine_instruction(instruction, regs, REGISTERS, data_mem);

		// ������� ��������� ��������� ����� ���������� �������
		show_registers(regs, order);

		if (jump_to == -1) {
			std::cerr << "������ ���������� �������. ����������." << std::endl;
			break;
		}
		else
		{
			if (jump_to > 0)
			{
				pc = (jump_to - 1) * 4;
			}
			else
			{
				pc += 4;
			}
		}

		// ������� ��������� pc
		std::cout << "pc: " << pc << std::endl;
	}


	return 0;
}