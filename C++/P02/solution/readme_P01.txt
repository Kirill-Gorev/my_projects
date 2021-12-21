Практическое задание 1.
Разреженная матрица.
Индексация матрицы начинает с 1(как строки, так и столбцы), т.е. самая левая верхняя ячейка - а[1][1].
Неинициализированные элементы матрицы считаются равными 0.
Я написал вспомогательный класс StringMatrix для работы со строками матрицы.
Класс SparseMatrix состоит из следующих данных:
	1) size_t string; - число строк в матрице
	2) size_t pillars; - число столбцов в матрице
	3) StringMatrix **matrix; - массив указателей на объекты типа StringMatrix
	4) SparseMatrix *copy_m; - лишняя копия матрицы после суммы и произведения
А также из методов:
    	1) SparseMatrix(size_t a, size_t b); - конструктор с двумя параметрами, первый число строк, 
	второй число столбцов в матрице.
    	2) SparseMatrix(SparseMatrix &M); - конструктор копирования
    	3) StringMatrix &operator [] (size_t k); - индексация
    	4) double get(size_t a, size_t b) const; - значение ячейки матрицы по ее индексам
    	5) void set(size_t a, size_t b, double val) const; - изменение ячейки матрицы по индексам
    	6) size_t num_rows() const; - вывод количества строк матрицы
    	7) size_t num_collums() const; - вывод количества столбцов матрицы
    	8) ~SparseMatrix(); - деструктор 
    	9) bool operator == (SparseMatrix const &M) const; - сравнение матриц на равенство
    	10) bool operator != (SparseMatrix const &M) const; - сравнение матриц на неравенство
    	11) SparseMatrix& operator = (SparseMatrix const &M); - присваивание
    	12) SparseMatrix& operator + (SparseMatrix const &M); - сложение матриц
    	13) StringMatrix* operator + (size_t k); - адресная арифметика
    	14) SparseMatrix& operator * (SparseMatrix const &M) const; - умножение матриц
Класс StringMatrix состоит из следующих данных:
	1) List* string; - список, состоящий из ячеек одной строки
А также из методов:
    	StringMatrix(); - конструктор строки
    	double& operator [] (size_t k); - индексация ячейки в строке 
    	double* operator + (size_t k); - адресная арифметика для ячейки в строке
    	StringMatrix(StringMatrix const &str); - конструктор копирования строки
    	void delete_List(); - удаление списка ячеек одной строки
    	double get(size_t b) const; - поиск ячейки в строке
    	bool operator != (StringMatrix const &str) const; - сравнение строк на неравенство
    	bool operator == (StringMatrix const &str) const; - сравнение строк на равенство 
    	StringMatrix& operator = (StringMatrix const &str); - присваивание строк
    	StringMatrix& operator + (StringMatrix const &str) const; - сложение строк
    	~StringMatrix(); - дестрруктор строки
Структура List состоит из данных:
	double a; - значение ячейки
    	size_t n_pillars; - индекс стобца в матрице у ячейки
    	List *next, *prev; - связность списка
	List(double value, size_t n); - конструктор списка