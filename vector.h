#pragma once
#include <math.h>


#define DEFAULT( N, T ) \
public: \
	Vector() { for(int i(0); i < N; i++) values[i] = 0; } \
	void Normalize() \
	{ \
		T length = Length(); \
		for( int i(0); i < N; i++ ) \
			values[i] /= length; \
	} \
	T Length() \
		{ return sqrt( length::Loop<N-1, T>::function( values ) ); } \
	T inline Dot( Vector<N, T>& v ) \
		{ return dot::Loop<N-1, T>::function( values, v.values ); } /* = ( values[i], v[i] ) ? */ \
	T operator[]( int n ) { return values[n]; } \
	T values[N]

#define LOOP( TYPE_ARGS, ARGS, FUNCTION, OPERATION, ZERO ) \
	template< int N, typename T = float > \
	struct Loop \
		{ static inline T function( TYPE_ARGS ) \
			{ return FUNCTION OPERATION Loop<N-1, T>::function( ARGS ); }}; \
	template< typename T > \
	struct Loop<0, T> \
		{ static inline T function( TYPE_ARGS ) \
			{ return ZERO; }}
#define COMMA ,


namespace linear_math
{
	namespace dot
		{ LOOP( T x[] COMMA T y[], x COMMA y, x[N] * y[N], +, x[0] * y[0] ); }
	namespace length
		{ LOOP( T v[], v, v[N] * v[N], +, v[0] * v[0] ); }

	template< int N, typename T = float >
	struct Vector
	{
		DEFAULT( N, T);
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
}
#undef COMMA
#undef LOOP
#undef DEFAULT
