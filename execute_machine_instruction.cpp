#include "execute_machine_instruction.h"

const int NONE_OPCODE = 255;

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
