#include <iostream>
#include <cmath>
#include <tuple>
#include <fstream>
#include <vector>

using namespace std;

int find_piv(vector<vector<float>> U, int n, int p){
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

vector<vector<float>> ch_line(vector<vector<float>> U, int n, int p, int line){
	vector<float> temp;

	for(int i=0; i<n; i++){
		temp.push_back(U[line][i]);
		U[line][i] = U[p][i];
		U[p][i] = temp[i];
	}
	return U;
}

tuple<vector<vector<float>>,vector<vector<float>>> piv(vector<vector<float>> U, vector<vector<float>> L, int n, int p){
	float pivo = U[p][p];

	for(int i=p+1; i<n; i++){
		float coef = U[i][p];
		for(int j=0; j<n; j++){
			U[i][j]=U[i][j]-(coef/pivo)*U[p][j];
			L[i][p] = coef/pivo;
		}
	}
	return {U, L};
}

void print_matrix(vector<vector<float>> Matrix, int n){
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				cout<<Matrix[i][j]<<' ';
		}
		cout<<endl;
	}
}

int main(){
	int line;

	//ifstream input1("A_matrix.txt");
	//ifstream input2("b_vector.txt");

	//string n1;
	//string n2;
	//getline(input1, n1);
	//getline(input2, n2);

	//if(n1!=n2){
	//	cout<<"Tamanho da matriz nao e compativel com o vetor"<<endl;
	//	return 0;
	//}else{
	//	n = stoi(n1);
	//}

	vector<vector<float>> A = { {2, -1, 4, 0}, {4, -1, 5, 1}, {-2, 2, -2, 3}, {0, 3, -9, 4} };
	vector<float> x = { 5, 9, 1, -2 };
	int n = 4;

	
	vector<vector<float>> U;
	U = A;

	vector<vector<float>> L;
	for(int i=0; i<n; i++){
		vector<float> temp;
		for(int j=0; j<n; j++){
			if(i==j){
				temp.push_back(1);
			}else{
				temp.push_back(0);
			}
		}
		L.push_back(temp);
	}

	for(int p=0; p<n-1; p++){
		tuple<vector<vector<float>>, vector<vector<float>>> temp;
		line = find_piv(U, n, p);
		U = ch_line(U, n, p, line);
		temp = piv(U, L, n, p);
		U = get<0>(temp);
		L = get<1>(temp);
	}
	
	cout<<"L="<<endl;
	print_matrix(L, n);
	cout<<endl;
	cout<<"U="<<endl;
	print_matrix(U, n);
	
	return 0;
}