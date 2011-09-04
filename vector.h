#pragma once
#include <math.h>


namespace linear_math
{
	namespace local
	{
		#define LOOP( TYPE_ARGS, ARGS, FUNCTION, ZERO ) \
			template< int N, typename T = float > \
			struct Loop \
				{ static inline T function( TYPE_ARGS ) \
					{ FUNCTION Loop<N-1, T>::function( ARGS ); }}; \
			template< typename T > \
			struct Loop<0, T> \
				{ static inline T function( TYPE_ARGS ) \
					{ ZERO; }};
		#define COMMA ,
		namespace dot
			{ LOOP( T x[] COMMA T y[], x COMMA y, return x[N] * y[N] +, return x[0] * y[0] ) }
		namespace length
			{ LOOP( T v[], v, return v[N] * v[N] +, return v[0] * v[0] ) }
		#undef COMMA
		#undef LOOP
		
	
		template< int N, typename T >
		struct VectorBase
		{
			VectorBase() {}
			void Zero() { for(int i(0); i < N; i++) values[i] = 0; }
			void Normalize()
			{
				T length = Length();
				for( int i(0); i < N; i++ )
					values[i] /= length;
			}
			T Length()
				{ return sqrt( length::Loop<N-1, T>::function( values ) ); }
			T inline Dot( VectorBase<N,T>& v )
				{ return dot::Loop<N-1, T>::function( values, v.values ); }
			T& operator[]( int n ) { return values[n]; }

			#define OPERATOR( OPERATION ) \
				/* Vector of same size */ \
				friend VectorBase<N,T> operator OPERATION( VectorBase<N,T>& v1, VectorBase<N,T>& v2 ) \
				{ \
					VectorBase<N,T> result; \
					for(int i(0); i < N; i++ ) \
						result[i] = v1[i] OPERATION v2[i]; \
					return result; \
				} \
				void operator OPERATION=( VectorBase<N,T>& v ) \
					{ for( int i(0); i < N; i++ ) values[i] OPERATION= v[i]; } \
				/* Scalar */ \
				friend VectorBase<N,T> operator OPERATION( VectorBase<N,T>& v1, T s ) \
				{ \
					VectorBase<N,T> result; \
					for(int i(0); i < N; i++ ) \
						result[i] = v1[i] OPERATION s; \
					return result; \
				} \
				friend VectorBase<N,T> operator OPERATION( T s, VectorBase<N,T>& v1 ) \
				{ \
					return v1 operator s; \
				} \
				void operator OPERATION=( T s ) \
					{ for( int i(0); i < N; i++ ) values[i] OPERATION= s; }
			OPERATOR(+)
			OPERATOR(-)
			#undef OPERATOR

			T values[N];
		};
	}
	
	template< int N, typename T = float >
	struct Vector : local::VectorBase<N,T>
	{
		Vector() {}
		Vector( VectorBase& v ) { memcpy( this, &v, sizeof(this) ); }
	};


	template< typename T >
	struct Vector<4,T> : local::VectorBase<4,T>
	{
		Vector() {}
		Vector( VectorBase& v ) { memcpy( this, &v, sizeof(this) ); }
		Vector( T x, T y, T z, T w )
		{
			values[0] = x;
			values[1] = y;
			values[2] = z;
			values[3] = w;
		}
	};
	
	template< typename T >
	struct Vector<3,T> : local::VectorBase<3,T>
	{
		Vector() {}
		Vector( VectorBase& v ) { memcpy( this, &v, sizeof(this) ); }
		Vector( T x, T y, T z ) 
		{
			values[0] = x;
			values[1] = y;
			values[2] = z;
		}
		Vector<3,T> Cross( Vector<3, T>& v )
		{
			Vector<3,T> result;
			result[0] = values[1] * v[2] - values[2] * v[1];
			result[1] = values[2] * v[0] - values[0] * v[2];
			result[2] = values[0] * v[1] - values[1] * v[0];
			return result;
		}
	};
	
	template< typename T >
	struct Vector<2,T> : local::VectorBase<2,T>
	{
		Vector() {}
		Vector( VectorBase& v ) { memcpy( this, &v, sizeof(this) ); }
		Vector( T x, T y )
		{
			values[0] = x;
			values[1] = y;
		}
	};
}
