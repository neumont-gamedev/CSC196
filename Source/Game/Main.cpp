#include "Math/Math.h"
#include "Core/Random.h"
#include <iostream>

#define NAME "Raymond\n"

int main()
{
	//const float deg = viper::radToDeg(viper::pi);
	//viper::clamp(2, 3, 5);
	std::cout << NAME;
	std::cout << "Hello, World!\n";
	std::cout << viper::math::pi << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << viper::random::getRandomFloat() << std::endl;
	}
}
