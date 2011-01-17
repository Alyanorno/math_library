#pragma once
#include <math.h>

#define DEFAULT( N, T ) \
public: \
	Vector() { for(int i(0); i < N; i++) values[i] = 0; } \
	void Normalize() \
	{ \
		T n = values[0]; \
		for( int i(1); i < N; i++ ) \
			if( n < values[i] ) \
				n = values[i]; \
		n = 1 / n; \
		for( int i(0); i < N; i++ ) \
			values[i] *= n; \
	} \
	T Length() \
		{ return sqrt( length::Loop<N-1, T>::function( &values ) ); } \
	T inline Dot( Vector<N, T>& v ) \
		{ return dot::Loop<N-1, T>::function( values, v.values ); } /* = ( values[i], v[i] ) ? */ \
	T operator[]( int n ) { return values[n]; } \
	T values[N]


namespace linear_math
{
	namespace dot
	{
		template< int N, typename T = float >
		struct Loop
			{ static inline T function( T x[], T y[] ) 
				{ return x[N] * y[N] + Loop<N-1, T>::function( x, y ); }};
		template< typename T >
		struct Loop<0, T>
			{ static inline T function( T x[], T y[] ) 
				{ return x[0] * y[0]; }};
	}
	namespace length
	{
		template< int N, typename T = float >
		struct Loop
			{ static inline T function( T* v ) 
				{ return v[n] * function<N-1, T>( v ); }};
		template< typename T >
		struct Loop<0, T>
			{ static inline T function( T* v ) 
				{ return v[0]; }};
	}

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
#undef DEFAULT
