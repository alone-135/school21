/* Реверс массива
    было:  1 2 3 4 5 6 7 8 9
    стало: 9 8 7 6 5 4 3 2 1 */
int N = 9;
int mas[N];

for (int i = 0; i < N / 2; ++i) {
    int tmp = mas[i];
    A[i] = A[N - 1 - i];
    A[N - 1 - i] = tmp;
}
///////////

/* Свиг массива влево
    было:  1 2 3 4 5 6 7 8 9
    стало: 2 3 4 5 6 7 8 9 1 */
int N = 9;
int mas[N];
int tmp = A[0];

for (int i = 0; i < N / 2; ++i) {
    A[i] = A[i + 1];
}
A[N - 1] = tmp;
///////////

/* Свиг массива вправо
    было:  1 2 3 4 5 6 7 8 9
    стало: 9 1 2 3 4 5 6 7 8 */
int N = 9;
int mas[N];
int tmp = A[N - 1];

for (int i = N - 1; i > 0; --i) {
    A[i] = A[i - 1];
}
A[0] = tmp;
///////////

/* Проверка на дроби */
void check() {
    char ch;
    if ((scanf("%c", &ch) == 1) &&
        (ch != '\0' && ch != '\n' && ch != ' ' && ch != EOF)) {
        err();
    }
}
///////////

/* Ошибка*/
void err() {
    printf("n/a");
    exit(0);
}
///////////

/* Выделение динамической памяти матрице*/
int** DATA;
DATA = allocate(STR, STL);

int** allocate(int SRT, int STL) {
    int** TMP = malloc(SRT * sizeof(int*));
    for (int i = 0; i < SRT; i++) *(TMP + i) = malloc(STL * sizeof(int));
    return TMP;
}

void free_Space(int*** DATA) {
    for (int i = 0; i < STR; i++) {
        free(DATA[i]);
    }
    free(DATA);
}
///////////

// Выделение динамической памяти массиву
int* DATA;
alloc(&DATA, N);

void alloc(int** DATA, int N) { *DATA = malloc(N * sizeof(int)); }

void free_Space(int** DATA) {
    free(*DATA);
    *DATA = NULL;
}
//////////

// Массив указателей на сегменты второго массива
const int M = 4, N = 4;
int** pointer_array = malloc(M * sizeof(int*));
int* values_array = malloc(M * N * sizeof(int));

for (int i = 0; i < M; i++) {
    pointer_array[i] = values_array + N * i;
}

free(values_array);
free(pointer_array);
////////////

// Массив указателей на масивы
const int M = 4, N = 4;

int** pointer_array = malloc(M * sizeof(int*));
for (int i = 0; i < M; i++) {
    pointer_array[i] = malloc(N * sizeof(int));
}

for (int i = 0; i < M; i++) {
    free(pointer_array[i]);
}
free(pointer_array);
///////////////

// Массив указателей нп сегменты массива в пределах одного буфера
const int M = 4, N = 4;
int** single_array_matrix = malloc(M * N * sizeof(int) + M * sizeof(int*));
int* ptr = (int*)(single_array_matrix + M);

for (int i = 0; i < M; i++) {
    single_array_matrix[i] = ptr + N * i;
}

free(single_array_matrix);
////////////

// Быстрая рекурсивная сортировка
void sort(int* a, int size) {
    //Указатели в начало и в конец массива
    int i = 0;
    int j = size - 1;

    //Центральный элемент массива
    int mid = a[size / 2];

    //Делим массив
    do {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые
        //меньше центрального
        while (a[i] < mid) {
            i++;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while (a[j] > mid) {
            j--;
        }

        //Меняем элементы местами
        if (i <= j) {
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);

    //Рекурсивные вызовы, если осталось, что сортировать
    if (j > 0) {
        //"Левый кусок"
        sort(a, j + 1);
    }
    if (i < size) {
        //"Првый кусок"
        sort(&a[i], size - i);
    }
}
///////////////////////////

// Сортировка пирамидой
void sort_pyr(int* numbers, int array_size) {
    // Формируем нижний ряд пирамиды
    for (int i = (array_size / 2); i >= 0; i--)
        siftDown(numbers, i, array_size - 1);
    // Просеиваем через пирамиду остальные элементы
    for (int i = array_size - 1; i >= 1; i--) {
        int temp = numbers[0];
        numbers[0] = numbers[i];
        numbers[i] = temp;
        siftDown(numbers, 0, i - 1);
    }
}

void siftDown(int* numbers, int root, int bottom) {
    int maxChild;  // индекс максимального потомка
    int done = 0;  // флаг того, что куча сформирована
    // Пока не дошли до последнего ряда
    while ((root * 2 <= bottom) && (!done)) {
        if (root * 2 == bottom)  // если мы в последнем ряду,
            maxChild = root * 2;  // запоминаем левый потомок
        // иначе запоминаем больший потомок из двух
        else if (numbers[root * 2] > numbers[root * 2 + 1])
            maxChild = root * 2;
        else
            maxChild = root * 2 + 1;
        // если элемент вершины меньше максимального потомка
        if (numbers[root] < numbers[maxChild]) {
            int temp = numbers[root];  // меняем их местами
            numbers[root] = numbers[maxChild];
            numbers[maxChild] = temp;
            root = maxChild;
        } else         // иначе
            done = 1;  // пирамида сформирована
    }
}
//////////////////////////////////