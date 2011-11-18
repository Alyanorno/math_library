#pragma once
#include "vector.h"
#include <math.h>
#include <iostream>
#include <string>


namespace linear_math
{
	namespace local
	{
		template < template< int M, int N, typename T > class Matrix, int M, int N, typename T >
		struct MatrixBase
		{
			MatrixBase() {}
			void Transpose()
			{
				for( int i(0); i < M; i++ )
					for ( int j(1); j < N; j++ )
					{
						/* switch place */
						T temp;
						temp = columns[i+j][i];
						columns[i+j][i] = columns[i][i+j];
						columns[i][i+j] = temp;
					}
			}
			void Identity()
			{
				for( int i(0); i < N; i++ )
				{
					columns[i].Zero();
					columns[i][i] = 1;
				}
			}
			Vector<N,T>& operator[]( int n ) { return columns[n]; }
	
			#define OPERATOR( OPERATION ) \
				/* Matrix of same size */ \
				friend Matrix<M,N,T> operator OPERATION( Matrix<M,N,T>& m1, Matrix<M,N,T>& m2 ) \
				{ \
					Matrix<M,N,T> result; \
					for( int i(0); i < M; i++ ) \
						for( int j(0); j < N; j++ ) \
							result[i][j] = m1[i][j] OPERATION m2[i][j]; \
					result[0] = Vector<2>( 5, 2 );\
					result[1] = Vector<2>( 1, 4 );\
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
			OPERATOR(+)
			OPERATOR(-)
			#undef OPERATOR
	
			/* Matrix of same size */
			friend Matrix<M,N,T> operator*( Matrix<M,N,T>& m1, Matrix<M,N,T>& m2 )
			{
				Matrix<M,N,T> result;
				Vector<N,T> v[M];
				for( int i(0); i < M; i++ )
					for( int j(0); j < N; j++ )
						v[i][j] = m1[j][i];
				for( int i(0); i < N; i++ )
					for( int j(0); j < M; j++ )
						result[i][j] = v[j].Dot( m2[i] );
				return result;
			}
			void operator*=( Matrix<M,N,T>& m )
			{
 				Vector<N,T> v[M];
				for( int i(0); i < M; i++ )
					for( int j(0); j < N; j++ )
						v[i][j] = columns[j][i];
				for( int i(0); i < N; i++ )
					for( int j(0); j < M; j++ )
						columns[i][j] = v[j].Dot( m[i] );
			}
			/* Vector */
			friend Matrix<M,N,T> operator*( Matrix<M,N,T>& m, Vector<N,T>& v )
			{
				Vector<N,T> result[M];
				Vector<N,T> tempVector[M];
				for( int i(0); i < M; i++ )
					for( int j(0); j < N; j++ )
						tempVector[i][j] = columns[j][i];
				for( int i(0); i < N; i++ )
						result[i] = v.Dot( tempVector[i] );
				return result;
			}
			/* Scalar */
			friend Matrix<M,N,T> operator*( Matrix<M,N,T>& m, T s )
			{
				Matrix<M,N,T> result;
				for( int i(0); i < N; i++ )
						result[i] = m[i] * s;
				return result;
			}
			void operator*=( T s )
				{ for( int i(0); i < N; i++ ) columns[i] *= s; }
			Vector<M,T> columns[N];
		};
	}
	template < int M, int N = M, typename T = float >
	struct Matrix : local::MatrixBase< Matrix, M, N, T > {};


	template < typename T >
	struct Matrix<3,3,T> : local::MatrixBase< Matrix, 3, 3, T >
	{
		Matrix() {}
#define MATRIX_A columns[0][0]
#define MATRIX_B columns[1][0]
#define MATRIX_C columns[2][0]
#define MATRIX_D columns[0][1]
#define MATRIX_E columns[1][1]
#define MATRIX_F columns[2][1]
#define MATRIX_G columns[0][2]
#define MATRIX_H columns[1][2]
#define MATRIX_K columns[2][2]
		void Inverse()
		{
			result[0][0] = MATRIX_E * MATRIX_K - MATRIX_F * MATRIX_H;
			result[0][1] = MATRIX_F * MATRIX_G - MATRIX_D * MATRIX_K;
			result[0][2] = MATRIX_D * MATRIX_H - MATRIX_E * MATRIX_G;
			result[1][0] = MATRIX_C * MATRIX_H - MATRIX_B * MATRIX_K;
			result[1][1] = MATRIX_A * MATRIX_K - MATRIX_C * MATRIX_G;
			result[1][2] = MATRIX_B * MATRIX_G - MATRIX_A * MATRIX_H;
			result[2][0] = MATRIX_B * MATRIX_F - MATRIX_C * MATRIX_E;
			result[2][1] = MATRIX_C * MATRIX_D - MATRIX_A * MATRIX_F;
			result[2][2] = MATRIX_A * MATRIX_E - MATRIX_B * MATRIX_D;
		}
		T Determinant() 
			{ return MATRIX_A * MATRIX_E * MATRIX_K + 
				 MATRIX_B * MATRIX_F * MATRIX_G + 
				 MATRIX_C * MATRIX_D * MATRIX_H -
				 MATRIX_C * MATRIX_E * MATRIX_C -
				 MATRIX_B * MATRIX_D * MATRIX_K -
				 MATRIX_A * MATRIX_F * MATRIX_H; }
#undef MATRIX_A
#undef MATRIX_B
#undef MATRIX_C
#undef MATRIX_D
#undef MATRIX_E
#undef MATRIX_F
#undef MATRIX_G
#undef MATRIX_H
#undef MATRIX_K
	};
	
	template < typename T >
	struct Matrix<2,2,T> : local::MatrixBase< Matrix, 2, 2, T > 
	{
		Matrix() {}
		Matrix<2,2,T> Inverse()
		{
			Matrix<2,2,T> result;
			T c = 1 / ( columns[1][0] * columns[1][1] - columns[0][0] * columns[0][1] );
			result[0][0] = c * columns[1][1];
			result[0][1] = c * -columns[0][1];
			result[1][0] = c * -columns[1][0];
			result[1][1] = c * columns[0][0];
			return result;
		}
		T Determinant() 
			{ return columns[0][0] * columns[1][1] - columns[0][1] * columns[1][0]; }
	};
}

