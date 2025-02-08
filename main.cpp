#include <iostream>
#include <array>
#include <map>
#include <vector>
#include <cstdlib> // Подключил для exit(0)


const int NONE_OPCODE = 255;

void show_registers(const std::map<std::string, int>& registers, const std::vector<std::string>& order) {
	std::cout << "Состояния регистров:\n";
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
		// Определяем целевой регистр
		std::string dest_reg;
		for (const auto& reg : REGISTERS) {
			if (reg.second == operand1) {
				dest_reg = reg.first;
				break;
			}
		}

		if (dest_reg.empty()) {
			std::cerr << "Ошибка: неизвестный регистр для mov: " << operand1 << std::endl;
			return -1;
		}

		// Определяем источник данных
		if (operand2 == 0) {  // Специальный случай: адрес data_memory
			regs[dest_reg] = 0;  // Записываем адрес начала data_memory
		}
		else if (operand2 >= 100 && operand2 < 170) {  // Косвенная адресация
			std::string src_reg;
			for (const auto& reg : REGISTERS) {
				if (reg.second == (operand2 - 100)) {
					src_reg = reg.first;
					break;
				}
			}
			if (src_reg.empty()) {
				std::cerr << "Ошибка: неизвестный регистр для косвенной адресации: " << (operand2 - 100) << std::endl;
				return -1;
			}
			regs[dest_reg] = data_mem[regs[src_reg]];  // Загружаем значение из памяти
		}
		else if (operand2 >= 170 && operand2 <= 255) {  // Непосредственное значение
			regs[dest_reg] = operand2 - 170;  // Записываем непосредственное значение
		}
		else {  // Регистр
			std::string src_reg;
			for (const auto& reg : REGISTERS) {
				if (reg.second == operand2) {
					src_reg = reg.first;
					break;
				}
			}
			if (src_reg.empty()) {
				std::cerr << "Ошибка: неизвестный регистр для mov: " << operand2 << std::endl;
				return -1;
			}
			regs[dest_reg] = regs[src_reg];  // Копируем значение из другого регистра
		}
	}

	if (opcode == 2) //add
	{

		// Определяем целевой регистр
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
			// Определяем второй регистр
			std::string src1;
			for (const auto& reg : REGISTERS) {
				if (reg.second == operand2) {
					src1 = reg.first;
					break;
				}
			}

			// Определяем третий регистр
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

		// Определяем целевой регистр
		std::string dest_reg;
		for (const auto& reg : REGISTERS) {
			if (reg.second == operand1) {
				dest_reg = reg.first;
				break;
			}
		}

		// Определяем второй регистр
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

			// Определяем третий регистр
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

		// Определяем второй регистр
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
			// Определяем третий регистр
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
		// Определяем целевой регистр
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
		std::cout << "Максимальный элемент:	" << regs["rdi"] << std::endl;
		exit(0);
	}

	if (opcode == 10) //load
	{
		// Определяем целевой регистр
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

		regs[dest_reg] = data_mem[regs[src_reg]];  // Загружаем значение из памяти


	}

	return 0;  // Успешное выполнение
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


	// Количество элементов в initial_instructions
	int initial_size = sizeof(initial_instructions) / sizeof(initial_instructions[0]);

	// Копируем элементы из initial_instructions в instruct_mem
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

		{"r0", 0},		//Перед началом цикла хранит адрес начала данных в памяти data_memory ([0])
		{"r1", 0},		//Перед началом цикла в него записывается первый эл-т массива - количество элементов в массиве  (10)
		{"r2", 0},		//Перед началом цикла хранит смещение, необходимое для доступа ко второму эл-ту массива данных в data_memory (1)
		{"r3", 0},		//Перед началом цикла хранит адрес второго элемента массива в памяти data_memory ([1])
		{"rax", 0},		//Сначала хранит первый элемент массива (15) - текущий максимум
		{"rbx", 0},		//Хранит текущий элемент
		{"rcx", 0},		//Счетчик
		{"rdi", 0},		//В него запсывается максимум после hlt
		{"eflags", 0},	//Флаг для условных переходов

	};

	std::cout << std::endl << std::endl << std::endl;

	std::vector<std::string> order = { "r0", "r1", "r2", "r3", "rax", "rbx", "rcx", "rdi", "eflags" };

	show_registers(regs, order);

	std::cout << std::endl << std::endl;

	int pc = 0;		//счетчик команд - регистр

	std::vector<int> instruction;

	while (pc < instruct_mem.size()) {
		// Копируем первые 4 элемента
		instruction.assign(instruct_mem.begin() + pc, instruct_mem.begin() + pc + 4);

		// Выводим выполняемую команду
		std::cout << "Выполняется команда: ";
		for (int elem : instruction) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;

		// Выполняем команду
		int jump_to = execute_machine_instruction(instruction, regs, REGISTERS, data_mem);

		// Выводим состояние регистров после выполнения команды
		show_registers(regs, order);

		if (jump_to == -1) {
			std::cerr << "Ошибка выполнения команды. Прерывание." << std::endl;
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

		// Выводим состояние pc
		std::cout << "pc: " << pc << std::endl;
	}


	return 0;
}