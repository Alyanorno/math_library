#include "linear_math.h"
#include <iostream>

#define PRINT_VECTOR( v, N ) do { \
	for( int I(0); I < N; I++ ) \
		std::cout << v[I] << std::endl; \
	std::cout << std::endl; } while(0)

#define PRINT_MATRIX( m, M, N ) do { \
	for( int i(0); i < N; i++ ) \
	{ \
		std::cout << "Vector [" << i << "]" << std::endl; \
		PRINT_VECTOR( m[i], M ); \
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

	linear_math::Matrix<2> m1;
	m1.Identity();
	std::cout << "Identity m1" << std::endl;
	PRINT_MATRIX( m1, 2, 2 );

	linear_math::Matrix<2> m2;
	m1[0] = linear_math::Vector<2>( 2, 7 );
	m1[1] = linear_math::Vector<2>( -3, 5 );
	m2[0] = linear_math::Vector<2>( 10, 12 );
	m2[1] = linear_math::Vector<2>( -8, -2 );
	std::cout << "m1" << std::endl;
	PRINT_MATRIX( m1, 2, 2 );
	std::cout << "m2" << std::endl;
	PRINT_MATRIX( m2, 2, 2 );
	
	linear_math::Matrix<2> result;
	result = m1 * m2;
	std::cout << "m1 * m2" << std::endl;
	PRINT_MATRIX( result, 2, 2 );

	linear_math::Matrix<3> m;
	m.Determinant();
	
	return 0;
}
