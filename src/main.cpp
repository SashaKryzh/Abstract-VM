#include "abstract.hpp"

int main(int ac, char *av[])
{
	--ac;
	++av;

	for (int i = 0; i < ac; i++)
	{
		std::cout << av[i] << std::endl;
	}
	return 0;
}
