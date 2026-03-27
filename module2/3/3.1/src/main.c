#include <stdio.h>

#include "chmod.h"

void printMenu() {
	printf("\n--- Меню работы с правами доступа ---\n");
	printf("1. Перевести маску (755 или rwxr-xr-x) в биты\n");
	printf("2. Показать права доступа файла\n");
	printf("3. Симуляция изменения прав (chmod)\n");
	printf("0. Выход\n");
	printf("-------------------------------------\n");
	printf("Выберите действие: ");
}

int main() {
	int choice;
	char buf1[256], buf_file[256], resStr[10];

	while (1) {
		printMenu();
		if (scanf("%d", &choice) != 1 || choice == 0) break;

		if (choice == 1) {
			printf("Введите маску: ");
			scanf("%s", buf1);
			uint16_t mask = getBitMask(buf1);
			if (mask == 0xFFFF) {
				printf("Ошибка: Неверный формат маски!\n");
			} else {
				printf("Результат для '%s':\n", buf1);
				printf("Восьмеричная: %o\n", mask);
				printf("Битовая:      ");
				printBinary(mask);
				printf("\n");
			}
		} else if (choice == 2) {
			printf("Имя файла: ");
			scanf("%s", buf_file);
			int mode = getStatString(buf_file, resStr);
			if (mode == -1) {
				printf("Ошибка: Файл не найден!\n");
			} else {
				printf("Права: %s (%o)\n", resStr, mode);
			}
		} else if (choice == 3) {
			printf("Введите новую маску: ");
			scanf("%s", buf1);
			printf("Введите имя файла: ");
			scanf("%s", buf_file);

			char currentRwx[10];
			int currentMode = getStatString(buf_file, currentRwx);
			uint16_t finalMode = simulateChmod(buf1, buf_file);

			if (currentMode == -1 || finalMode == 0xFFFF) {
				printf(
					"Ошибка: Не удалось выполнить симуляцию. Проверьте файл и "
					"маску.\n");
			} else {
				printf("--- Симуляция chmod %s для %s ---\n", buf1, buf_file);
				printf("Было:  %o (%s)\n", currentMode, currentRwx);
				printf("Стало: %o (", finalMode);
				printBinary(finalMode);
				printf(")\n");
			}
		}
	}
	return 0;
}