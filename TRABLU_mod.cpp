#include <iostream>
#include <cmath>
#include <tuple>
#include <fstream>
#include <vector>

using namespace std;

vector<float> read_b(){
	ifstream vectorb;
	vectorb.open("b_vector.txt");

	float num;
	vector<float> b;

	while(vectorb.good()){
		vectorb >> num;
		b.push_back(num);
	}

	vectorb.close();
	return b;
}

void write_x(vector<float> x){
	ofstream vectorx("x_vector.txt");

	int n = x.size();
	for(int i=0; i<n; i++){
		float vIn = x[i];
		char vOut [17];
		char* buffer = _gcvt_s(vOut,sizeof(vOut),vIn,8);
		vectorx.write(buffer, 64);
	}

}

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

 tuple<vector<vector<float>>,vector<vector<float>>, vector<float>> 
 ch_line(vector<vector<float>> U, vector<vector<float>> L, vector<float> x, int n, int p, int line){
	vector<float> temp1, temp2;
	float temp3;

	for(int i=0; i<n; i++){
		temp1.push_back(U[line][i]);
		U[line][i] = U[p][i];
		U[p][i] = temp1[i];
	}
	for(int i=0; i<p; i++){
		temp2.push_back(L[line][i]);
		L[line][i] = L[p][i];
		L[p][i] = temp2[i];
	}
	temp3 = x[line];
	x[line] = x[p];
	x[p] = temp3;

	return {U, L, x};
}

tuple<vector<vector<float>>,vector<vector<float>>, vector<float>> 
piv(vector<vector<float>> U, vector<vector<float>> L, vector<float> x , int n, int p){
	float pivo = U[p][p];

	for(int i=p+1; i<n; i++){
		float coef = U[i][p];
		for(int j=0; j<n; j++){
			U[i][j]=U[i][j]-(coef/pivo)*U[p][j];
			L[i][p] = coef/pivo;
		}
	}
	return {U, L, x};
}

vector<float> solve_systemL(vector<vector<float>> L, vector<float> b, int n){
	vector<float> c;
	c.push_back(b[0]);
	float sum = 0;

	for(int i=1; i<n; i++){
		for(int j=0; j<i; j++){
			sum += L[i][j]*c[j];
		}
		c.push_back(b[i]-sum);
		sum = 0;
	}
	return c;
}

vector<float> solve_systemU(vector<vector<float>> U, vector<float> c, int n){
	vector<float> x_inv, x;
	x_inv.push_back(c[n-1]/(U[n-1][n-1]));
	float sum = 0;

	for(int i=n-2; i>=0; i--){
		for(int j=n-1; j>i; j--){
			sum += U[i][j]*x_inv[n-(1+j)];
		}
		x_inv.push_back((c[i]-sum)/(U[i][i]));
		sum = 0;
	}
	for(int i=n-1; i>=0; i--){
		x.push_back(x_inv[i]);
	}

	return x;
}

void print_matrix(vector<vector<float>> Matrix, int n){
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				cout<<Matrix[i][j]<<' ';
		}
		cout<<endl;
	}
}

void print_vector(vector<float> b, int n){
	for(int i=0; i<n; i++){
		cout<<b[i]<<' ';
	}
	cout<<endl;
}

int main(){
	int line;
	vector<float> b;

	vector<vector<float>> A = { {3, 1, 6}, {2, 1, 3}, {1, 1, 1}};

	b = read_b();
	int n = b.size();

	vector<float> c, x;
	vector<vector<float>> U, L;
	
	U = A;
	
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
		tuple<vector<vector<float>>, vector<vector<float>>, vector<float>> temp;
		line = find_piv(U, n, p);
		temp = ch_line(U, L, b, n, p, line);
		U = get<0>(temp);
		L = get<1>(temp);
		b = get<2>(temp);
		temp = piv(U, L, b, n, p);
		U = get<0>(temp);
		L = get<1>(temp);
	}
	c = solve_systemL(L, b, n);
	x = solve_systemU(U, c, n);
	
	cout<<"L="<<endl;
	print_matrix(L, n);
	cout<<endl;
	cout<<"U="<<endl;
	print_matrix(U, n);
	cout<<endl;
	cout<<"b="<<endl;
	print_vector(b, n);
	cout<<endl;
	cout<<"c="<<endl;
	print_vector(c, n);
	cout<<endl;
	cout<<"x="<<endl;
	print_vector(x, n);

	write_x(x);
	
	return 0;
}