#include <math.h>
#include <stdio.h>

void printMenu() {
	printf("Выбери действие\n");
	printf("0. Выход\n");
	printf("1. Сложение\n");
	printf("2. Вычитание\n");
	printf("3. Умножение\n");
	printf("4. Деление\n");
	printf("--------------------------------------------------\n");
	printf("Выберите действие: ");
}

#include <stdio.h>

#include "calc.h"

int main() {
	int choice;
	double a, b, res;

	while (1) {
		printMenu();
		if (scanf("%d", &choice) != 1) break;

		if (choice == 0) {
			printf("Выход из программы.\n");
			break;
		}

		if (choice < 1 || choice > 4) {
			printf("Ошибка: Неверный пункт меню. Попробуйте снова.\n");
			continue;
		}
		printf("Введите два числа через пробел: ");
		if (scanf("%lf %lf", &a, &b) != 2) {
			printf("Ошибка: Некорректный ввод чисел.\n");
			while (getchar() != '\n')
				;
			continue;
		}

		switch (choice) {
			case 1:
				res = sum_two(a, b);
				printf("Результат: %.2f + %.2f = %.2f\n", a, b, res);
				break;
			case 2:
				res = sub(a, b);
				printf("Результат: %.2f - %.2f = %.2f\n", a, b, res);
				break;
			case 3:
				res = mul(a, b);
				printf("Результат: %.2f * %.2f = %.2f\n", a, b, res);
				break;
			case 4:
				res = div(a, b);
				if (res == INFINITY) {
					printf("Результат: Деление на ноль!\n");
				} else {
					printf("Результат: %.2f / %.2f = %.2f\n", a, b, res);
				}
				break;
		}
	}
	return 0;
}