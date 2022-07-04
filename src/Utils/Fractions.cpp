#include "Utils/Fractions.h"

#include <iostream>

void simplify(Fraction &frac)
{
	int max = 0;
	if(frac.n > frac.d)
		max = frac.n;
	else
		max = frac.d;

	std::cout << frac.n << " " << frac.d << std::endl;

	while(true)
	{
		if(((frac.n % max) == 0) && ((frac.d % max) == 0))
		{
			break;
		}
		max--;
	}

	std::cout << max << std::endl;
	frac.n /= max;
	frac.d /= max;
}
