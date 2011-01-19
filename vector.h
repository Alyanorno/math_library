#pragma once
#include <math.h>


#define DEFAULT( N, T ) \
public: \
	Vector() { for(int i(0); i < N; i++) values[i] = 0; } \
	Vector( T array[] ) { for(int i(0); i < N; i++) values[i] = array[i]; } \
	void Normalize() \
	{ \
		T length = Length(); \
		for( int i(0); i < N; i++ ) \
			values[i] /= length; \
	} \
	T Length() \
		{ return sqrt( length::Loop<N-1, T>::function( values ) ); } \
	T inline Dot( Vector<N,T>& v ) \
		{ return dot::Loop<N-1, T>::function( values, v.values ); } \
	T& operator[]( int n ) { return values[n]; } \
	OPERATOR(+, N, T) \
	OPERATOR(-, N, T) \
	OPERATOR(*, N, T) \
	OPERATOR(/, N, T) \
	T values[N]

#define OPERATOR( OPERATION, N, T ) \
	/* Vector of same size */ \
	friend Vector<N,T>& operator OPERATION( Vector<N,T>& v1, Vector<N,T>& v2 ) \
	{ \
		T array[N]; \
		for(int i(0); i < N; i++ ) \
			tempVector[i] = v1[i] OPERATION v2[i]; \
		return Vector<N,T>( array ); \
	} \
	void operator OPERATION=( Vector<N,T>& v ) \
		{ for( int i(0); i < N; i++ ) values[i] OPERATION= v[i]; } \
	/* Scalar */ \
	friend Vector<N,T>& operator OPERATION( Vector<N,T>& v1, T s ) \
	{ \
		T array[N]; \
		for(int i(0); i < N; i++ ) \
			tempVector[i] = v1[i] OPERATION s; \
		return Vector<N,T>( array ); \
	} \
	void operator OPERATION=( T s ) \
		{ for( int i(0); i < N; i++ ) values[i] OPERATION= s; }

#define LOOP( TYPE_ARGS, ARGS, FUNCTION, OPERATION, ZERO ) \
	template< int N, typename T = float > \
	struct Loop \
		{ static inline T function( TYPE_ARGS ) \
			{ return FUNCTION OPERATION Loop<N-1, T>::function( ARGS ); }}; \
	template< typename T > \
	struct Loop<0, T> \
		{ static inline T function( TYPE_ARGS ) \
			{ return ZERO; }};
#define COMMA ,


namespace linear_math
{
	namespace dot
		{ LOOP( T x[] COMMA T y[], x COMMA y, x[N] * y[N], +, x[0] * y[0] ) }
	namespace length
		{ LOOP( T v[], v, v[N] * v[N], +, v[0] * v[0] ) }


	template< int N, typename T = float >
	struct Vector
	{
		DEFAULT( N, T);
	};


	template< typename T >
	struct Vector<4, T>
	{
		DEFAULT( 4, T );
	public:
		Vector( T x, T y, T z, T w )
		{
			values[0] = x;
			values[1] = y;
			values[2] = z;
			values[3] = w;
		}
	};
	
	template< typename T >
	struct Vector<3, T>
	{
		DEFAULT( 3, T );
	public:
		Vector( T x, T y, T z ) 
		{
			values[0] = x;
			values[1] = y;
			values[2] = z;
		}
		Vector<3, T> Cross( Vector<3, T>* v ) {}
	};
	
	template< typename T >
	struct Vector<2, T>
	{
		DEFAULT( 2, T );
	public:
		Vector( T x, T y )
		{
			values[0] = x;
			values[1] = y;
		}
	};
}
#undef COMMA
#undef LOOP
#undef OPERATOR
#undef DEFAULT
