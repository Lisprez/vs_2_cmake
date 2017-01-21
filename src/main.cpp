#include <iostream>
#include "print.h"

int main(int argc, char* argv[])
{
    std::cout << "Test output from the main.cpp" << std::endl;
	std::cout << produce_string() << std::endl;
    return 0;
}
