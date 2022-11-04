//backup do codigo 02/11/2022 as 18:53

#include <iostream>
#include <cmath>
#include <string>
//#include <algorithm>

using namespace std;

int find_piv(float **U, int n, int p){
	float par = fabs(U[p][p]);
	int line = p;

	for(int i=p; i<n; i++){
		if(fabs(U[i][p])>par){
			par=fabs(U[i][p]);
			line = i;
		}
	}
	return line;
}

void ch_line(float **U, int n, int p, int line){
	float temp[n];

	for(int i=0; i<n; i++){
		temp[i] = U[line][i];
		U[line][i] = U[p][i];
		U[p][i] = temp[i];
	}
}

void piv(float **U, float **L, int n, int p){
	float pivo = U[p][p];

	for(int i=p+1; i<n; i++){
		float coef = U[i][p];
		for(int j=0; j<n; j++){
			U[i][j]=U[i][j]-(coef/pivo)*U[p][j];
			L[i][p] = coef/pivo;
		}
	}
}



void print_matrix(float **Matrix, int n){
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				cout<<Matrix[i][j]<<' ';
		}
		cout<<endl;
	}
}



int main(){
	const int n = 4;
	int line; 
	
	float A[n][n] = { {2, -1, 4, 0}, {4, -1, 5, 1}, {-2, 2, -2, 3}, {0, 3, -9, 4} };
	float x[n] = { 5, 9, 1, -2 };

	float **U = new float* [n];
	for(int i=0; i<n; i++){
		U[i] = new float[n];
		for(int j=0; j<n; j++){
			U[i][j] = A[i][j];
		}
	}

	float **L = new float* [n];
	for(int i=0; i<n; i++){
		L[i] = new float[n];
		for(int j=0; j<n; j++){
			if(i==j){
				L[i][j] = 1;
			}else{
				L[i][j] = 0;
			}
		}
	}

	for(int p=0; p<n-1; p++){
		line = find_piv(U, n, p);
		ch_line(U, n, p, line);
		piv(U, L, n, p);
	}
	
	cout<<"L="<<endl;
	print_matrix(L, n);
	cout<<endl;
	cout<<"U="<<endl;
	print_matrix(U, n);
	
	return 0;
}