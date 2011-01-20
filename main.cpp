#include "linear_math.h"
#include <iostream>

#define PRINT_VECTOR( v, N ) do { \
	for( int i(0); i < N; i++ ) \
		std::cout << v[i] << std::endl; \
	std::cout << std::endl; } while(0)

#define PRINT_MATRIX( m, M, N ) do { \
	for( int i(0); i < N; i++ ) \
	{ \
		for( int j(0); j < M; j++ ) \
			std::cout << m[i][j] << "   "; \
		std::cout << std::endl; \
	} \
	std::cout << std::endl; } while(0)

int main()
{
	std::cout << __LINE__ << std::endl 
		  << __FILE__ << std::endl 
		  << __DATE__ << std::endl 
		  << __TIME__ << std::endl << std::endl;

	linear_math::Vector<3> v1( 666, 23, 50 );
	v1[0] = 3;
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

	linear_math::Matrix<3> m;
	m.Identity();
	std::cout << "Identity m" << std::endl;
	PRINT_MATRIX( m, 3, 3 );

	m[0] = linear_math::Vector<3>( 2, 5, 7 );
	m[1] = v2;
	m[2] = linear_math::Vector<3>( 2, 5, 7 );
	std::cout << "m" << std::endl;
	PRINT_MATRIX( m, 3, 3 );
	
	m *= m;
	std::cout << "m" << std::endl;
	PRINT_MATRIX( m, 3, 3 );

	return 0;
}
