#pragma once
#ifndef _EXECUTE_MACHINE_INSTRUCTION_H_
#define _EXECUTE_MACHINE_INSTRUCTION_H_

#include <iostream>
#include <array>
#include <map>
#include <vector>
#include <cstdlib> // Подключил для exit(0)

int execute_machine_instruction(std::vector<int>& instr, std::map<std::string, int>& regs, const std::map<std::string, int>& REGISTERS, std::array<int, 2048>& data_mem);

#endif // !_EXECUTE_MACHINE_INSTRUCTION_H_




