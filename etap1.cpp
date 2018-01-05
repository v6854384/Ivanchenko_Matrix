#include <iostream>
#include <cstring> 
#include <cstdlib>
using namespace std;

void print_matrix(int **&a, int n, int m){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
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
    				cout << "3. Multiplacation matrix" << endl;
    				cout << "4. Transpose matrix" << endl;
    				cout << "5. Save to file" << endl;
    				cout << "6. Load from file" << endl;
    				cout << "7. Sort matrix" << endl;
				cin >> ch;
				if ( ch == 1 ){
					print_matrix(a, n, m);
					break;
				}
			}
		}
	}
}
