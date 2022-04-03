// Массив указателей на сегменты второго массива

const int M = 4, N = 4;
int** pointer_array = malloc(M * sizeof(int*));
int* values_array = malloc(M * N * sizeof(int));

for (int i = 0; i < M; i++) {
    pointer_array[i] = values_array + N * i;
}

free (values_array);
free (pointer_array);

////////////

// Массив указателей на масивы

const int M = 4, N = 4; 

int** pointer_array = malloc(M * sizeof(int *));
for (int i = 0; i < M; i++) {
    pointer_array[i] = malloc(N * sizeof(int));
}

for (int i = 0; i < M; i++) {
    free (pointer_array[i]);
}
free (pointer_array);

///////////////

// Массив указателей нп сегменты массива в пределах одного буфера

const int M = 4, N = 4;
int** single_array_matrix = malloc(M * N * sizeof(int) + M * sizeof(int*));
int* ptr = (int*) (single_array_matrix + M); 

for (int i = 0; i < M; i++) {
    single_array_matrix[i] = ptr + N * i;
}

free (single_array_matrix);

////////////
