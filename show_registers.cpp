#include "show_registers.h"

void show_registers(const std::map<std::string, int>& registers, const std::vector<std::string>& order) {
	std::cout << "Состояния регистров:\n";
	for (const auto& key : order) {
		std::cout << key << ":\t" << registers.at(key) << "\n";
	}
}