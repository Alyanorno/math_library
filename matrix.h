#pragma once
#include "vector.h"
#include <math.h>

#define DEFAULT( M, N, T ) \
public: \
	Matrix() {} \
	void Transpose() \
	{ \
		for( int i(0); i < N; i++ ) \
			for ( int j(1); j < N; j++ )\
			{ \
				/* switch place */ \
				T temp; \
				temp = columns[i+j][i]; \
				columns[i+j][i] = columns[i][i+j]; \
				columns[i][i+j] = temp; \
			} \
	} \
	void Identity() \
	{ \
		for( int i(0); i < N; i++ ) \
		{ \
			columns[i].Zero(); \
			columns[i][i] = 1; \
		} \
	} \
	Vector<N,T>& operator[]( int n ) { return columns[n]; } \
	OPERATOR(+, M, N, T) \
	OPERATOR(-, M, N, T) \
	\
	/* Matrix of same size */ \
	friend Matrix<M,N,T> operator*( Matrix<M,N,T>& m1, Matrix<M,N,T>& m2 ) \
	{ \
		Matrix<M,N,T> result; \
		Vector<N,T> v[M]; \
		for( int i(0); i < M; i++ ) \
			for( int j(0); j < N; j++ ) \
				v[i][j] = m1[j][i]; \
		for( int i(0); i < N; i++ ) \
			for( int j(0); j < M; j++ ) \
				result[i][j] = v[j].Dot( m2[i] ); \
		return result; \
	} \
	void operator*=( Matrix<M,N,T>& m ) \
	{ \
		Vector<N,T> v[M]; \
		for( int i(0); i < M; i++ ) \
			for( int j(0); j < N; j++ ) \
				v[i][j] = columns[j][i]; \
		for( int i(0); i < N; i++ ) \
			for( int j(0); j < M; j++ ) \
				columns[i][j] = v[j].Dot( m[i] ); \
	} \
	/* Vector */ \
	friend Matrix<M,N,T> operator*( Matrix<M,N,T>& m, Vector<N,T>& v ) \
	{ \
		Vector<N,T> result[M]; \
		Vector<N,T> tempVector[M]; \
		for( int i(0); i < M; i++ ) \
			for( int j(0); j < N; j++ ) \
				tempVector[i][j] = columns[j][i]; \
		for( int i(0); i < N; i++ ) \
				result[i] = v.Dot( tempVector[i] ); \
		return result; \
	} \
	/* Scalar */ \
	friend Matrix<M,N,T> operator*( Matrix<M,N,T>& m, T s ) \
	{ \
		Matrix<M,N,T> result; \
		for( int i(0); i < N; i++ ) \
				result[i] = m[i] * s; \
		return result; \
	} \
	void operator*=( T s ) \
		{ for( int i(0); i < N; i++ ) columns[i] *= s; } \
	Vector<M,T> columns[N]

#define OPERATOR( OPERATION, M, N, T ) \
	/* Matrix of same size */ \
	friend Matrix<M,N,T> operator OPERATION( Matrix<M,N,T>& m1, Matrix<M,N,T>& m2 ) \
	{ \
		Matrix<M,N,T> result; \
		for( int i(0); i < N; i++ ) \
			result[i] = m1[i] OPERATION m2[i]; \
		return result; \
	} \
	void operator OPERATION=( Matrix<M,N,T>& m ) \
		{ for( int i(0); i < N; i++ ) columns[i] OPERATION##= m[i]; } \
	/* Vector */ \
	friend Matrix<M,N,T> operator OPERATION( Matrix<M,N,T>& m, Vector<N,T>& v ) \
	{ \
		Matrix<M,N,T> result; \
		for( int i(0); i < N; i++ ) \
			result[i] = m[i] OPERATION v[i]; \
		return result; \
	} \
	void operator OPERATION=( Vector<N,T>& v ) \
		{ for( int i(0); i < N; i++ ) columns[i] OPERATION##= v[i]; }


namespace linear_math
{
	template < int M, int N = M, typename T = float >
	struct Matrix
	{
		DEFAULT( M, N, T );
	};

	template < typename T >
	struct Matrix<4,4,T>
	{
		DEFAULT( 4, 4, T );
	public:
		void Inverse() {}
		void Rotate( Vector<4,T> v ) {}
		void Scale( Vector<4,T> v ) {}
		void Translate( Vector<4,T> v ) {}
	};

	template < typename T >
	struct Matrix<3,3,T>
	{
		DEFAULT( 3, 3, T );
	public:
		void Inverse() {} /* NOT DONE */
		void RotateX( T angle ) {} /* NOT DONE */
		void RotateY( T angle ) {} /* NOT DONE */
		void RotateZ( T angle ) {} /* NOT DONE */
		void ScaleX( T scale ) 
			{ columns[0][0] *= scale; }
		void ScaleY( T scale )
			{ columns[1][1] *= scale; }
		void ScaleZ( T scale )
			{ columns[2][2] *= scale; }
		T Determinant() 
			{ return columns[0][0] * columns[1][1] * columns[2][2] + 
				 columns[1][0] * columns[2][1] * columns[0][2] + 
				 columns[2][0] * columns[0][1] * columns[1][2] -
				 columns[2][0] * columns[1][1] * columns[0][2] -
				 columns[1][0] * columns[0][1] * columns[2][2] -
				 columns[0][0] * columns[2][1] * columns[1][2]; }
	};
	
	template < typename T >
	struct Matrix<2,2,T>
	{
		DEFAULT( 2, 2, T );
	public:
		void Inverse() {} /* NOT DONE */
		void RotateX( T angle ) {} /* NOT DONE */
		void RotateY( T angle ) {} /* NOT DONE */
		void ScaleX( T scale ) 
			{ columns[0][0] *= scale; }
		void ScaleY( T scale )
			{ columns[1][1] *= scale; }
		T Determinant() 
			{ return columns[0][0] * columns[1][1] - columns[0][1] * columns[1][0]; }
	};
}

#undef OPERATOR
#undef DEFAULT
