#include "linear_math.h"
#include <iostream>

#define PRINT_VECTOR( v, n ) do { \
	for( int i(0); i < n; i++ ) \
		std::cout << v[i] << std::endl; \
	std::cout << std::endl; } while(0)

int main()
{
	add(2,5);

	linear_math::Vector<3> v1( 3, 23, 50);
	std::cout << "v1" << std::endl;
	PRINT_VECTOR( v1, 3 );

	linear_math::Vector<3> v2( -2, 1, 0.5 );
	std::cout << "v2" << std::endl;
	PRINT_VECTOR( v2, 3 );

	std::cout << "Dot product of " << "v1" << " and " << "v2" << std::endl;
	std::cout << v1.Dot( v2 ) << std::endl << std::endl;

	v1.Normalize();
	std::cout << "Normalize " << "v1" << std::endl;
	PRINT_VECTOR( v1, 3 );
	return 0;
}
