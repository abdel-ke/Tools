#include <iostream>

#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"
//Reset
#define reset "\e[0m"

#define COUT(X) std:: << X << std::endl;
int main()
{
	std::cout << BRED << "BRED" << std::endl;
	std::cout << BGRN << "BGRN" << std::endl;
	std::cout << BYEL << "BYEL" << std::endl;
	std::cout << BBLU << "BBLU" << std::endl;
	std::cout << BMAG << "BMAG" << std::endl;
	std::cout << BCYN << "BCYN" << std::endl;
	std::cout << BWHT << "BWHT" << reset << std::endl;
}
