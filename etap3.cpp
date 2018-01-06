#include <iostream>
#include <cstring> 
#include <cstdlib>
#include <string.h>
#include <fstream>
using namespace std;

void print_matrix(int **&a, int &n, int &m){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}

void delete_matrix(int **&a, int &n){
	for (int i = 0; i < n; i++) delete[] a[i];
	delete [] a;
}

void sum_matrixs(int **&a, int &n, int &m){
	cout << "Input new matrix " << n << "x" << m << endl;
	int **b = new int*[n];
	for (int i = 0; i < n; i++)
		b[i] = new int[m];
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			cin >> b[i][j];
			a[i][j] = a[i][j] + b[i][j];
		}
	}
	delete_matrix(b, n);
}

void multiplacation_matrixs(int **&a, int &n, int &m){
	cout << "Input a size of new matrix" << endl;
	int m1 = 0, k = 0;
	char size_mult[256], nmult[256], mmult[256];
	cin >> size_mult;
	int l = 0, l1 = 0;
	bool flag_size = true;
	while (size_mult[l] != 'x'){
		nmult[l] = size_mult[l];
		l++;
	}
	l++;
	while (l < strlen(size_mult)){
		mmult[l1] = size_mult[l];
		l++;
		l1++;
	}
	m1 = atoi(nmult);
	k = atoi(mmult);
	if (m1 == m){
		int **c = new int*[m1];
		for (int i = 0; i < m1; i++)
			c[i] = new int[k];
		cout << "Input new matrix " << m1 << "x" << k << endl;
		for (int i = 0; i < m1; i++){
			for (int j = 0; j < k; j++){
				cin >> c[i][j];
			}	
		}
		int **a1 = new int*[n];
		for (int i = 0; i < n; i++)
			a1[i]=new int[m];
		for (int i = 0; i < n; i++){
			for (int j = 0; j < m; j++){
				a1[i][j] = a[i][j];
			}
		}
		delete_matrix(a, n);
		m = k;
		a = new int*[n];
		for (int i = 0; i < n; i++)
			a[i] = new int[m];
		for (int i = 0; i < n; i++){
			for (int j = 0; j < m; j++){
				a[i][j] = 0;
			}
		}

		for (int i = 0; i < n; i++){
			for (int j = 0; j < k; j++){
				for (int r = 0; r < m1; r++){
					a[i][j] = a[i][j] + a1[i][r] * c[r][j];
				}
			}
		}
		delete_matrix(c, m1);
		delete_matrix(a1, n);
	}
	else cout << "Wrong size" << endl;
}

void transpose_matrix(int **&a, int &n, int &m){
	int **d = new int*[n];
	for(int i = 0; i < n; i++)
		d[i]=new int[m];
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			d[i][j] = a[i][j];
		}
	}
	delete_matrix(a, n);
	int save = n;
	n = m;
	m = save;
	a = new int*[n];
	for(int i = 0; i < n; i++)
		a[i] = new int[m];
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			a[i][j] = d[j][i];
		}
	}
	delete_matrix(d, n);
}

void save_matrix(int **&a, int &n, int &m) {
	string name;
	cout << "Enter a name of the file" << endl;
	cin >> name;
	ifstream fin(name, ios_base::in);
	string answer = "y";
	if (fin.is_open()){
		cout << "Do you want to rewrite file?(y/n)" << endl;
		cin >> answer;
	}
	fin.close();
	if ((answer == "y") || (answer == "yes") || (answer == "Y") || (answer == "Yes") || (answer == "YES")){
		ofstream fout(name, ios_base::out);
		fout << n << " " << m << endl;
            	for (int i = 0; i < n; i++){
                	for (int j = 0; j < m; j++)
				if (j != m - 1) fout << a[i][j]<< " ";
				else fout << a[i][j];
               		if (i != n - 1) fout << endl;
           	}
		fout.close();
        }
}

void input_matrix(int **&a, int &n, int &m){
	cout << "Enter the directory of the file" << endl;
	string directory;
	cin >> directory;
	ifstream fin(directory);
	if (fin.is_open()){
		delete_matrix(a, n);
		string inpn, inpm;
		fin >> inpn >> inpm;
		n = atoi(inpn.c_str());
		m = atoi(inpm.c_str());
		a = new int*[n];
		for(int i = 0; i < n; i++)
			a[i] = new int[m];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				a[i][j] = 0;
		int counta = 0, countf = 0;
		string numeric;
		while (!(fin.eof())){
			fin >> numeric;
			countf++;
		}
		numeric = "";
		fin.close();
		fin.open(directory, ios::in);
		fin >> inpn >> inpm;
		for (int i = 0; i < n; i++){
			for (int j = 0; j < m; j++){
				if (counta < countf){
					fin >> numeric;
					a[i][j] = atoi(numeric.c_str());
					counta++;
				}
			}
		}
	}
	else cout << "There is no such file in this directory" << endl;
}

int main(int argc, char *argv[]){
	int n = 0, m = 0;
	if (argc == 1) cout << "You haven`t entered any data" << endl;
	if (argc == 2) cout << "You haven`t entered the matrix" << endl;
	if (argc > 2){
		int g = 0;
		bool flagn = true, flagm = true, probel = false, zapyataya = false;
		while (argv[1][g] != 'x'){
			if ((argv[1][g] >= '0') && (argv[1][g] <= '9')) n = n * 10 + argv[1][g] - 48;
			else flagn = false;
			g++;
		}
		g++;
		while (g < strlen(argv[1])){
			if ((argv[1][g] >= '0') && (argv[1][g] <= '9')) m = m * 10 + argv[1][g] - 48;
			else flagm = false;
			g++;
		}
		for (int i = 0; i < strlen(argv[2]); i++){
			if (argv[2][i] == ','){
				zapyataya = true;
			}
		}
		if (zapyataya == false) probel = true;
		
		int **a = new int*[n], counta = 0;
		for(int i = 0; i < n; i++)
			a[i]=new int[m];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				a[i][j] = 0;
		
		int inpn = 0, inpm = 0, v = 0;
		bool flag_matrix = true, flag_end_of_matrix = false, flag_total_count = true;
		if (zapyataya == true){
				for (int i = 0; i < strlen(argv[2]); i++){
					if (counta < n * m){
						if ((argv[2][i] >= '0') && (argv[2][i] <= '9')) a[inpn][inpm] = a[inpn][inpm] * 10 + argv[2][i] - 48;
						else{
							if (argv[2][i] == ','){
								if ((inpm != m - 1) && (counta + 1 != n * m)){
									inpm++;
									counta++;
								}
								else{
									if (counta + 1 != n * m){
										inpm = 0;
										inpn++;
										counta++;
									}
									else{
										flag_end_of_matrix = true;
										counta++;
									}
								}
							}
							else flag_matrix = false;
						}
					}
				}
		}
		else{
			if (argc - 2 > n * m) v = n * m;
			else v = argc - 2;
			for (int i = 0; i < v; i++){
				for (int j = 0; j < strlen(argv[i + 2]); j++){
					if ((argv[i + 2][j] >= '0') && (argv[i + 2][j] <= '9'))
						;
					else flag_matrix = false;
				}
				if (flag_matrix == true) a[inpn][inpm] = atoi(argv[i + 2]);
				if (inpm != m - 1){
					inpm++;
					counta++;
				}
				else{
					inpm = 0;
					inpn++;
				}
			}
			counta++;
		}
		if (flag_end_of_matrix == false) counta++;
		
		if ((flagn == false) || (flagm == false) || (flag_matrix == false)) cout << "You entered incorrect data" << endl;
		else{
			while(true){
				int ch = 0;
				cout << endl;
				cout << "Select operation:" << endl;
    				cout << "1. Print matrix" << endl;
    				cout << "2. Sum matrixs" << endl;
    				cout << "3. Multiplacation matrixs" << endl;
    				cout << "4. Transpose matrix" << endl;
    				cout << "5. Save to file" << endl;
    				cout << "6. Load from file" << endl;
    				cout << "7. Sort matrix" << endl;
				cin >> ch;
				switch(ch){
					case 1:
						print_matrix(a, n, m);
						break;
					case 2:
						sum_matrixs(a, n, m);
						break;
					case 3:
						multiplacation_matrixs(a, n, m);
						break;
					case 4:
						transpose_matrix(a, n, m);
						break;
					case 5:
						save_matrix(a, n, m);
						break;
					case 6:
						input_matrix(a, n, m);
						break;
				
				}
			}
		}
	}
}
