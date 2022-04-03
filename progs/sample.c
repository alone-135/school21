/* Реверс массива
    было:  1 2 3 4 5 6 7 8 9
    стало: 9 8 7 6 5 4 3 2 1 */

    int N = 9;
    int mas[N];

    for (int i = 0; i < N/2; ++i) {
        int tmp = mas[i];
        A[i] = A[N - 1 - i];
        A[N - 1 - i] = tmp;
    } 


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


/* Проверка на дроби */
void check() {
    char ch;
    if ((scanf("%c", &ch) == 1) && (ch != '\0' && ch != '\n' && ch != ' ' && ch != EOF)) {
    err();
    }
}


/* Ошибка*/
void err() {
    printf("n/a");
    exit(0);
}


/* Выделение динамической памяти матрице*/
int** DATA;
DATA = allocate(STR, STL);

int** allocate(int SRT, int STL) {
    int** TMP = malloc(SRT * sizeof(int*));
    for (int i = 0; i < SRT; i++)
        *(TMP + i) = malloc(STL * sizeof(int));
    return TMP;
}



void free_Space(int ***DATA) {
    for (int i = 0; i < STR; i++) {
        free(DATA[i]);
    }
    free(DATA);
}


/* Выделение динамической памяти массиву*/
int* DATA;
alloc(&DATA, N);

void alloc(int **DATA, int N) {
    *DATA = malloc(N * sizeof(int));
}

void free_Space(int **DATA) {
    free(*DATA);
    *DATA = NULL;
}