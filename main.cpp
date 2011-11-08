#include "linear_math.h"
#include <iostream>


template< int T >
void printVector( linear_math::Vector<T> v )
{
	for( int i(0); i < T; i++ )
		std::cout << v[i] << ' ';
	std::cout << std::endl;
}

template< int N, int M >
void printMatrix( linear_math::Matrix<N,M> v )
{
	for( int i(0); i < N; i++ )
	{
		printVector( v[i] );
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main()
{
	std::cout << __LINE__ << std::endl 
		  << __FILE__ << std::endl 
		  << __DATE__ << std::endl 
		  << __TIME__ << std::endl << std::endl;

	linear_math::Vector<3> v1( 666, 23, 50 );
	v1[0] = 3;
	std::cout << "v1" << std::endl;
	printVector( v1 );

	linear_math::Vector<3> v2( -2, 1, 0.5 );
	std::cout << "v2" << std::endl;
	printVector( v2 );

	std::cout << "Dot product of " << "v1" << " and " << "v2" << std::endl;
	std::cout << v1.Dot( v2 ) << std::endl << std::endl;

	v1.Normalize();
	std::cout << "Normalize " << "v1" << std::endl;
	printVector( v1 );

	linear_math::Matrix<2> m1;
	m1.Identity();
	std::cout << "Identity m1" << std::endl;
	printMatrix( m1 );

	linear_math::Matrix<2> m2;
	m1[0] = linear_math::Vector<2>( 2, 7 );
	m1[1] = linear_math::Vector<2>( -3, 5 );
	m2[0] = linear_math::Vector<2>( 10, 12 );
	m2[1] = linear_math::Vector<2>( -8, -2 );
	std::cout << "m1" << std::endl;
	printMatrix( m1 );
	std::cout << "m2" << std::endl;
	printMatrix( m2 );
	
	std::cout << "m1 + m2" << std::endl;
	printMatrix<2,2>( m1 + m2 );

	linear_math::Matrix<3> m;
	m.Determinant();

	return 0;
}
