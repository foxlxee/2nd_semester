#include <iostream>

#define N 1000
#define TYPE int

void copy(TYPE* srcArr, TYPE* dstArr) {
	// Получаем указатели, указывающие на начало массивов
	size_t* llptr1 = reinterpret_cast<size_t*>(srcArr);
	size_t* llptr2 = reinterpret_cast<size_t*>(dstArr);

	// Вычисляем количество элементов, которые копируются за одну итерацию
	size_t amountOfElementsToCopyOnce = sizeof(size_t) / sizeof(TYPE);

	// Вычисляем количество итераций
	size_t iterations = N / amountOfElementsToCopyOnce;

	// Пробегаем массивы и копируем по 8 байт
	for (size_t i = 0; i < iterations; i++) {
		*llptr2++ = *llptr1++;
	}

	// Вычисляем количество оставшихся байт и копируем их если нужно
	if ((iterations = (N - iterations * amountOfElementsToCopyOnce) * sizeof(TYPE)) > 0) {
		// Получаем указатели, указывающие на начало оставшихся элементов
		char* cptr1 = reinterpret_cast<char*>(llptr1);
		char* cptr2 = reinterpret_cast<char*>(llptr2);
		
		// Пробегаем массивы и копируем по 1 байт
		for (size_t i = 0; i < iterations; i++) {
			*cptr2++ = *cptr1++;
		}
	}
}

void print(TYPE* arr) {
	for (size_t i = 0; i < N; i++) {
		std::cout << arr[i] << ',';
		if (i != N - 1) {
			std::cout << ' ';
		}
	}
	std::cout << std::endl;
}

int main() {
	// Выделяем память под массивы
	TYPE arr_a[N] = { 0 };
	TYPE arr_b[N] = { 0 };

	// Заполняем первый массив
	for (size_t i = 0; i < N; i++) {
		arr_a[i] = i;
	}

	// Копируем первый массив во второй
	copy(arr_a, arr_b);
	
	// Выводим второй массив
	print(arr_b);
}