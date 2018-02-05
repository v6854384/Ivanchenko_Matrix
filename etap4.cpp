#include <iostream>
//Чтобы можно было выводить текст с помощью cout и вводить с помощью cin
#include <string>
//чтобы программа без ошибок работала на всех платформах
#include <cstring> 
//Чтобы работала функции strlen
#include <fstream>
//Для работы с файлами, конкретно для ifstream
using namespace std;
//Для того, чтобы не писать std:: перед каждой библиотечной функцией 

void print_matrix(int **a, int n, int m){ //объявление функции, которая не возвращает никаких значений
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}

void delete_matrix(int **a, int &n, int &m){
	for (int i = 0; i < n; i++) delete[] a[i];
	delete[] a;
	n = 0;
	m = 0;
}

void sum_matrixs(int **a, int n, int m){
	cout << "Input new matrix" << n << "x" << m << endl;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			int v; //в эту переменную вводится очередной элемент новой матрицы
			cout << "b[" << i << "][" << j << "]=";
			cin >> v;
			a[i][j] = a[i][j] + v;
		}
	}
}

void multiplacation_matrixs(int **&a, int &n, int &m){
	cout << "Input the number of columns for new matrix" << endl;
	int k;
	cin >> k;

	int **b = new int*[m];
	for (int i = 0; i < m; i++){
		b[i] = new int[k];
	}

	int **c = new int*[n];
	for (int i = 0; i < n; i++){
		c[i] = new int[k];
	}

	cout << "Input matrix" << endl;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < k; j++) {
			cout << "b[" << i << "][" << j << "]=";
			cin >> b[i][j];
		}
	}
	//здесь перемножаются матрицы А и В, и записываются в матрицу С
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			c[i][j] = 0;
			for (int r = 0; r < m; r++) {
				c[i][j] += a[i][r] * b[r][j];
			}
		}
	}
	int new_n = n, new_m = k; //новые размеры матрицы и чтобы не потерять значения n и m, после удаления матриц а и b значения n и m останутся старыми
	delete_matrix(a, n, m); //очищаем память, выделенную под  матрицу а
	delete_matrix(b, m, k); //очищаем память, выделенную под  матрицу b
	a = c; //здесь мы говорим что С указывает в памяти туда же, куда и А, то есть А и С указывают на одни и те же данные
	n = new_n;
	m = new_m;
}

void transpose_matrix(int **&a, int &n, int &m){
	int **d = new int*[m];
	for (int i = 0; i < m; i++)
		d[i] = new int[n];
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			d[j][i] = a[i][j];
		}
	}
	int new_n = m, new_m = n;
	delete_matrix(a, n, m);
	n = new_n; m = new_m;
	a = d;
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
				if (j != m - 1) fout << a[i][j] << " ";
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
		delete_matrix(a, n, m);
		string inpn, inpm;
		fin >> inpn >> inpm;
		n = atoi(inpn.c_str());
		m = atoi(inpm.c_str());
		a = new int*[n];
		for (int i = 0; i < n; i++)
			a[i] = new int[m];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				a[i][j] = 0;
		int counta = 0, countf = 0;
		string numeric;
		// Читаем число значений в файле (матрице)
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



// Идея: ищем минимальный элемент и меняеем его с первым, он на своем месте, далее делаем тоже с массивом размерности на 1 меньшей и т.д.
void sort1(int *p, int n)
{
	for (int i = 0; i<n - 1; i++) // Массив начинается с i-го элемента
	{
		int min = p[i], // Считаем минимальным i-ый элемент
			imin = i;
		for (int j = i + 1; j<n; j++) // Просматриваем все последующие элементы за i-м
			if (p[j]<min) // Нашли меньший элемент
			{
			min = p[j]; // Запоминаем его
			imin = j; // и его индекс
			}
		if (i != imin) // Меняем два элемента местами
		{
			p[imin] = p[i];
			p[i] = min;
		}
	}
}

// Сортировка методом прямого обмена (метод "пузырька")
/* Идея: за 1 просмотр массива (с начала массива) сравниваем 2 соседних элемента, при необходимости меняем их между собой,
за 1 просмотр максимальный элемент окажется на своем месте (как бы всплывет, поэтому метод "пузырька"),
минимальный элемент переместиться на 1 место к началу. Максимум необходимо n-1 таких просмотров массива,
может быть меньше, если массив частично отсортирован */
void sort2(int *p, int n)
{
	for (int i = 0; i<n - 1; i++) // Максимальное число просмотров массива
	{
		bool zamena = false; // Флаг показывает, что был выполнен обмен элементов 
		for (int j = 0; j<n - 1 - i; j++) // Просматриваем массив (последние элементы могут быть отсортированы на предыдущих шагах)
			if (p[j]>p[j + 1]) // Элементы меняем местами
			{
			int buf = p[j];
			p[j] = p[j + 1];
			p[j + 1] = buf;
			zamena = true;
			}
		if (!zamena) // Замен не было массив уже отсортирован
			break;

	}
}

// Сортировка методом вставки
/* Идея: Вставляем элемент, начиная со второго, в нужное место в уже отсортированный массив,  элементы следующие за вставляемым сдвигаем на 1 место вправо */
void sort3(int *p, int n)
{
	for (int i = 1; i<n; i++) // Берем i-ый элемент и вставляем его в уже отсортированные элементы перед ним
	{
		for (int j = 0; j<i; j++) // Просматриваем элементы до i-го
			if (p[i]<p[j]) // Нашли нужное место, i-ый элемент нужно вставить вместо j-го, начиная с j-го элемента сдвигаем элементы
			{
			int buf = p[i]; // Сохраняем значение i-го элемента
			for (int k = i; k>j; k--) p[k] = p[k - 1];  // Сдвигаем отсорированные элементы на 1 место
			p[j] = buf; // i-ый элемент ставим вместо j-го
			break; // Выход из цикла
			}
	}
}

void sort_matrix(int **a, int n, int m){
	int *s = new int[n * m];
	int counts = 0;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			s[counts] = a[i][j];
			counts++;
		}
	}
	cout << "Select the sort method:" << endl;
	cout << "s: metod prymogo vybora" << endl;
	cout << "h: metod prymogo obmena (puzirka)" << endl;
	cout << "i: metod vstavki" << endl;
	//cout << "b: back" << endl;
	char ch1 = '0';
	cin >> ch1;
	int z = 0;
	if ((ch1 == 's') || (ch1 == 'h') || (ch1 == 'i') || (ch1 == 'b')){
		switch (ch1){
		case 's':
			sort1(s, counts);
			break;
		case 'h':
			sort2(s, counts);
			break;
		case 'i':
			sort3(s, counts);
			break;
	/*	case 'b':
			sort4(a, n, m, s, counts);
			break;*/
		}
		for (int i = 0; i < n; i++){
			for (int j = 0; j < m; j++){
				a[i][j] = s[z];
				z++;
			}
		}
	}
	else cout << "Wrong sort method" << endl;
	delete[] s;
}

int main(int argc, char *argv[]){
	//С этого места запускается программа
	//В argc количество входных параметров
	//argv - массив этих параметров
	int n = 0, m = 0;
	//n - кол-во строк, m - кол-во стобцов
	if (argc == 1) cout << "You haven`t entered any data" << endl;
	if (argc == 2) cout << "You haven`t entered the matrix" << endl;
	if (argc > 2){
		int g = 0;
		//Для того чтобы можно было бегать по строке
		bool flagn = true, flagm = true, probel = false, zapyataya = false;
		//flagn и flagm = false когда n и m неправильные.
		// В цикле из строки читаем n
		while (argv[1][g] != 'x'){
			//Здесь идет считывание размера матрицы n
			if ((argv[1][g] >= '0') && (argv[1][g] <= '9')) n = n * 10 + argv[1][g] - '0'; // Символ - цифра (код символа превращаем в занчение)
			//Проверяем что параметр, который мы берем является цифрой
			//Далее, мы берем "n", которому присваиваем значение взятого параметра
			else flagn = false;   // Символ не цифра
			g++;
		}
		g++; // Симов следующий за х
		// В цикле из строки читаем m
		while (g < strlen(argv[1])){ // Пока не дошли до конца строки
			//Здесь идет считывание размера матрицы m
			//Проверка на то, что до тех пор пока мы не дайдем до конца взятой строки, будет выполняться условие:
			if ((argv[1][g] >= '0') && (argv[1][g] <= '9')) m = m * 10 + argv[1][g] - '0'; // Символ цифра 
			else flagm = false; // Символ не цифра
			g++;
		}
		for (int i = 0; i < strlen(argv[2]); i++){
			//Этот цикл нужен для того, чтобы понять как будут заданы параметры
			if (argv[2][i] == ','){  // Разделитель запятая, а не пробел
				zapyataya = true;    
			}
		}
		if (zapyataya == false) probel = true; //  Разделитель пробел

		//n элементов в массиве, каждый из которых указывает какую-то (int) область памяти
		//выделяю память для указателя на столбцы
		//выделяю память на сами стобцы
		int **a = new int*[n];
		for (int i = 0; i < n; i++)
			//выделяем по i-ый столбец память з
			a[i] = new int[m];
		//далее мы указываем что каждый элемент матрицы равен нулю
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				a[i][j] = 0;

		//inpn - номер строки, inpm - номер стобца (индексы матрицы)
		int inpn = 0, inpm = 0, v = 0;
		bool flag_matrix = true, flag_end_of_matrix = false, flag_total_count = true;
		if (zapyataya == true){   // Разделитель запятая все числа в одной строке

			int counta = 0;  // Общий счетчик чисел
			//рассматриваем случай, когда параметры, которые задают содержимое матрицы, заданы через запятые
			// проходим по каждому символу в строке
			for (int i = 0; i < strlen(argv[2]); i++){  // Просмотр строки
				// i - это индекс символа в строке argv2
				//здесь мы начинаем считывать очередной элемент в матрицу а
				//counta текущий не нулевой элемент матрицы
				if (counta < n * m){  // Не все числа прочитаны
					//если это цифра, то мы продолжаем считывать этот элемент матрицы и как только встречаем запятую, переходим к след.
					if ((argv[2][i] >= '0') && (argv[2][i] <= '9')) a[inpn][inpm] = a[inpn][inpm] * 10 + argv[2][i] - '0'; // Символ цифра
					//
					else{  // Симовл не цифра
						if (argv[2][i] == ','){ // Символ , (разделитель)
							//если текущий столбец не последний и текущий элемент, который мы заполняли не последний
							if ((inpm != m - 1) && (counta != n * m - 1)){  // Переход к след символу в этой же строке матрицы
								//тогда переходим к след. элементу и столбцу, если что-то убрать то будем заполнять не по верному адресу
								inpm++; // Номер столбца
								counta++; // Общее чимсло элементов
							}
							else{ // Иначе
								if (counta != n * m - 1){ // Символ не последний в матрице (последний в строке)
									//здесь мы дошли до конца первой строки матрицы и переходим на новую
									inpm = 0;
									inpn++;
									counta++;
								}
								else{    // Символ последний в матрице
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
		else{ // Разделитель пробелл
			//v - кол-во элементов матрицы, которые заданы из командной строки
			// проверка на колво максимально возможных элементво в матрице
			if (argc - 2 > n * m) v = n * m;  // Общее число параметров - строк символов, каждая строка отдельное значение 
			else v = argc - 2;
			for (int i = 0; i < v; i++){	//i номер элемента матрица из командно строки, пробегаем по элементам в командной строке			
				//проверям что параметр argv i+2 состоит только из цифр
				for (int j = 0; j < strlen(argv[i + 2]); j++){ //J индекс символа в строке
					if (!((argv[i + 2][j] >= '0') && (argv[i + 2][j] <= '9')))   // Если символ не цифра

						flag_matrix = false;
				}
				//если матрица задана верна, то элемент матрицы из строкового вида переводим в обычное число типа int
				if (flag_matrix == true) a[inpn][inpm] = atoi(argv[i + 2]);  // Преобразование строки в целое
				//если столбец не последний, идем к след.
				if (inpm != m - 1){
					inpm++;
				}
				//но если последний стоблец, то 
				else{
					inpm = 0;
					inpn++;
				}
			}
		}

		if ((flagn == false) || (flagm == false) || (flag_matrix == false)) cout << "You entered incorrect data" << endl; // Проверка разных ошибок
		else{ // Данные введены без ошибок
			while (true){ // Бесконечный цикл
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
				cout << "8. Exit" << endl;
				cin >> ch;
				switch (ch){
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
				case 7:
					sort_matrix(a, n, m);
					break;
				case 8:
					// Освобождение памяти
					for (int i = 0; i < n; i++) delete[] a[i];
					delete[] a;
					return 0;
				}
			}
		}
	}
	return  0;
	//Для того чтобы программа сообщила оперативной памяти успешное завершение работы
}
