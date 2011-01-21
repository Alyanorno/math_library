#pragma once
#include "vector.h"

#define DEFAULT( M, N, T ) \
public: \
	Matrix() {} \
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
		Matrix<M,N,T> tempMatrix; \
		Vector<N,T> v[M]; \
		for( int i(0); i < M; i++ ) \
			for( int j(0); j < N; j++ ) \
				v[i][j] = m1[j][i]; \
		for( int i(0); i < N; i++ ) \
			for( int j(0); j < M; j++ ) \
				tempMatrix[i][j] = v[j].Dot( m2[i] ); \
		return tempMatrix; \
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
		Matrix<M,N,T> tempMatrix; \
		for( int i(0); i < N; i++ ) \
				tempMatrix[i] = m[i] * v[i]; \
		return tempMatrix; \
	} \
	void operator*=( Vector<N,T>& v ) \
		{ for( int i(0); i < N; i++ ) columns[i] *= v[j]; } \
	/* Scalar */ \
	friend Matrix<M,N,T> operator*( Matrix<M,N,T>& m, T s ) \
	{ \
		Matrix<M,N,T> tempMatrix; \
		for( int i(0); i < N; i++ ) \
				tempMatrix[i] = m[i] * s; \
		return tempMatrix; \
	} \
	void operator*=( T s ) \
		{ for( int i(0); i < N; i++ ) columns[i] *= s; } \
	Vector<M,T> columns[N]

#define OPERATOR( OPERATION, M, N, T ) \
	/* Matrix of same size */ \
	friend Matrix<M,N,T> operator OPERATION( Matrix<M,N,T>& m1, Matrix<M,N,T>& m2 ) \
	{ \
		Matrix<M,N,T> tempMatrix; \
		for( int i(0); i < N; i++ ) \
			tempMatrix[i] = m1[i] OPERATION m2[i]; \
		return tempMatrix; \
	} \
	void operator OPERATION=( Matrix<M,N,T>& m ) \
		{ for( int i(0); i < N; i++ ) columns[i] OPERATION##= m[i]; } \
	/* Vector */ \
	friend Matrix<M,N,T> operator OPERATION( Matrix<M,N,T>& m, Vector<N,T>& v ) \
	{ \
		Matrix<M,N,T> tempMatrix; \
		for( int i(0); i < N; i++ ) \
			tempMatrix[i] = m[i] OPERATION v[i]; \
		return tempMatrix; \
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
	struct Matrix<2,2,T>
	{
		DEFAULT( 2, 2, T );
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
		void Inverse() {}
		void Rotate( Vector<3,T> v ) {}
		void Scale( Vector<3,T> v ) {}
		void Translate( Vector<3,T> v ) {}
	};
}

#undef OPERATOR
#undef DEFAULT
