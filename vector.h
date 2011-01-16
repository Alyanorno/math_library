#pragma once
#include <math.h>

#define DEFAULT( N, T ) \
public: \
	Vector() { for(int i(0); i < N; i++) values[i] = 0; } \
	void Normalize() {} \
	T Length() {} \
	T inline Dot( Vector<N, T>* v ) \
	{ \
		return dot::Loop<N-1, T>::function( values[i], v[i] ); /* = ( values[i], v[i] ) ? */ \
	} \
	T operator[]( int n ) { return values[n]; } \
private: \
	T values[N]


namespace linear_math
{
	namespace dot
	{
		template<int N, class T = float>
		struct Loop
			{ static inline T function( T* x, T* y ) 
				{ return x[N] * y[N] + function<N-1, T>( x, y ); }};
		template<class T>
		struct Loop<0, T>
			{ static inline T function( T* x, T* y ) 
				{ return x[0] * y[0]; }};
	}

	template< int N, class T = float >
	class Vector
	{
		DEFAULT( N, T);
	};

	template< class T >
	class Vector<3, T>
	{
		DEFAULT( 3, T );
	public:
		Vector( T x, T y, T z ) : values[0](x),
					  values[1](y).
					  values[2](x) {}
		Vector<3, T> Cross( Vector<3, T>* v ) {}
	};
}
#undef DEFAULT
