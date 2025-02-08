#include <iostream>
#include <array>
#include <map>
#include <vector>
#include <cstdlib> // ��������� ��� exit(0)


const int NONE_OPCODE = 255;

void show_registers(const std::map<std::string, int>& registers, const std::vector<std::string>& order) {
	std::cout << "��������� ���������:\n";
	for (const auto& key : order) {
		std::cout << key << ":\t" << registers.at(key) << "\n";
	}
}


int execute_machine_instruction(std::vector<int>& instr, std::map<std::string, int>& regs, const std::map<std::string, int>& REGISTERS, std::array<int, 2048>& data_mem) {
	int opcode = instr.at(0);
	int operand1 = instr.at(1);
	int operand2 = instr.at(2);
	int operand3 = instr.at(3);

	if (opcode == 1) {  // mov
		// ���������� ������� �������
		std::string dest_reg;
		for (const auto& reg : REGISTERS) {
			if (reg.second == operand1) {
				dest_reg = reg.first;
				break;
			}
		}

		if (dest_reg.empty()) {
			std::cerr << "������: ����������� ������� ��� mov: " << operand1 << std::endl;
			return -1;
		}

		// ���������� �������� ������
		if (operand2 == 0) {  // ����������� ������: ����� data_memory
			regs[dest_reg] = 0;  // ���������� ����� ������ data_memory
		}
		else if (operand2 >= 100 && operand2 < 170) {  // ��������� ���������
			std::string src_reg;
			for (const auto& reg : REGISTERS) {
				if (reg.second == (operand2 - 100)) {
					src_reg = reg.first;
					break;
				}
			}
			if (src_reg.empty()) {
				std::cerr << "������: ����������� ������� ��� ��������� ���������: " << (operand2 - 100) << std::endl;
				return -1;
			}
			regs[dest_reg] = data_mem[regs[src_reg]];  // ��������� �������� �� ������
		}
		else if (operand2 >= 170 && operand2 <= 255) {  // ���������������� ��������
			regs[dest_reg] = operand2 - 170;  // ���������� ���������������� ��������
		}
		else {  // �������
			std::string src_reg;
			for (const auto& reg : REGISTERS) {
				if (reg.second == operand2) {
					src_reg = reg.first;
					break;
				}
			}
			if (src_reg.empty()) {
				std::cerr << "������: ����������� ������� ��� mov: " << operand2 << std::endl;
				return -1;
			}
			regs[dest_reg] = regs[src_reg];  // �������� �������� �� ������� ��������
		}
	}

	if (opcode == 2) //add
	{

		// ���������� ������� �������
		std::string dest_reg;
		for (const auto& reg : REGISTERS) {
			if (reg.second == operand1) {
				dest_reg = reg.first;
				break;
			}
		}

		if (operand2 > 170)
		{
			regs[dest_reg] += (operand2 - 170);
		}
		else
		{
			// ���������� ������ �������
			std::string src1;
			for (const auto& reg : REGISTERS) {
				if (reg.second == operand2) {
					src1 = reg.first;
					break;
				}
			}

			// ���������� ������ �������
			std::string src2;
			for (const auto& reg : REGISTERS) {
				if (reg.second == operand3) {
					src2 = reg.first;
					break;
				}
			}

			regs[dest_reg] = regs[src1] + regs[src2];
		}

	}

	if (opcode == 3) //sub
	{

		// ���������� ������� �������
		std::string dest_reg;
		for (const auto& reg : REGISTERS) {
			if (reg.second == operand1) {
				dest_reg = reg.first;
				break;
			}
		}

		// ���������� ������ �������
		std::string src1;
		for (const auto& reg : REGISTERS) {
			if (reg.second == operand2) {
				src1 = reg.first;
				break;
			}
		}

		if (170 <= operand3 <= 255)
		{
			regs[dest_reg] = regs[src1] - (operand3 - 170);
		}
		else
		{

			// ���������� ������ �������
			std::string src2;
			for (const auto& reg : REGISTERS) {
				if (reg.second == operand3) {
					src2 = reg.first;
					break;
				}
			}

			regs[dest_reg] = regs[src1] - regs[src2];

		}

	}

	if (opcode == 4) //cmp
	{
		regs["eflags"] = 2;

		// ���������� ������ �������
		std::string src1;
		for (const auto& reg : REGISTERS) {
			if (reg.second == operand1) {
				src1 = reg.first;
				break;
			}
		}

		if (operand2 == NONE_OPCODE)
		{
			if (regs[src1] == 0)
			{
				regs["eflags"] = 0;
			}
		}
		else
		{
			// ���������� ������ �������
			std::string src2;
			for (const auto& reg : REGISTERS) {
				if (reg.second == operand2) {
					src2 = reg.first;
					break;
				}
			}

			if (regs[src1] > regs[src2])
			{
				regs["eflags"] = 1;
			}

			else
			{
				if (regs[src1] < regs[src2])
				{
					regs["eflags"] = -1;
				}
				else
				{
					regs["eflags"] = 0;
				}
			}

		}
	}


	if (opcode == 5) //je
	{
		
		if (regs["eflags"] == 0)
		{
			return operand1;
		}

	}

	if (opcode == 6) //jle
	{

		if (regs["eflags"] <= 0)
		{
			return operand1;
		}

	}

	if (opcode == 7) //jmp
	{

		return operand1;

	}


	if (opcode == 8) //dec
	{
		// ���������� ������� �������
		std::string dest_reg;
		for (const auto& reg : REGISTERS) {
			if (reg.second == operand1) {
				dest_reg = reg.first;
				break;
			}
		}
		regs[dest_reg] = regs[dest_reg] - 1;
	}

	if (opcode == 9) //hlt 
	{
		std::cout << "������������ �������:	" << regs["rdi"] << std::endl;
		exit(0);
	}

	if (opcode == 10) //load
	{
		// ���������� ������� �������
		std::string dest_reg;
		for (const auto& reg : REGISTERS) {
			if (reg.second == operand1) {
				dest_reg = reg.first;
				break;
			}
		}

		std::string src_reg;
		for (const auto& reg : REGISTERS) {
			if (reg.second == operand2 - 100) {
				src_reg = reg.first;
				break;
			}
		}

		regs[dest_reg] = data_mem[regs[src_reg]];  // ��������� �������� �� ������


	}

	return 0;  // �������� ����������
}




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