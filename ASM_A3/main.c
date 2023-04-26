#define _CRT_SECURE_NO_WARNINGS

/*
Дана строка из четырех десятичных цифр. Если первые две цифры не совпадают и
больше четвертой, то заменить вторую цифру суммой первой и третьей (если это
возможно), иначе — заменить последние две цифры девятками
*/

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

void clear_input() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}

int char_to_int(char x) {
	return x - '0';
}

char int_to_char(int x) {
	return x + '0';
}

int main() {
	setlocale(LC_ALL, "rus");
	setlocale(LC_NUMERIC, "eng");

	char str[4], str_copied[4];
	unsigned flag = 1, tmp = 1;
	while (tmp) {
		
		while (flag) {
			printf("Введите строку из 4 цифр без пробелов:\n");
			scanf("%s", &str);
			if (!isdigit(str[0]) || !isdigit(str[1]) || !isdigit(str[2]) || !isdigit(str[3])) {
				printf("Повторите ввод.\n");
			}
			else { flag = 0; }
		}

		strcpy(str_copied, str);

		if (str_copied[0] != str_copied[1] && str_copied[0] > str_copied[3] && str_copied[1] > str_copied[3]) {
			if (char_to_int(str_copied[0]) + char_to_int(str_copied[2]) < 10) {
				str_copied[1] = int_to_char(char_to_int(str_copied[0]) + char_to_int(str_copied[2]));
			}
		}
		else {
			str_copied[2] = int_to_char(9);
			str_copied[3] = int_to_char(9);
		}

		__asm {
			mov al, str[0]; // помещаем 1-ую цифру в AL
			mov bl, str[1]; // помещаем 2-ую цифру в BL
			cmp al, bl; // сравниваем 1-ую и 2-ую цифры
			jz ELSE; // если равны, то переход на ELSE
			mov cl, str[3]; // помещаем 4-ую цифру в CL
			cmp cl, al; // сравниваем 4-ую и 1-ую цифры
			jge ELSE; // если 4-ая цифра >= 1-ой, то переход на ELSE
			cmp cl, bl; // сравниваем 4-ую и 2-ую цифры
			jge ELSE; // если 4-ая цифра >= 2-ой, то переход на ELSE
			mov dl, str[2];
			sub al, 48;
			sub dl, 48;
			add al, dl; // складываем 1-ую и 3-ю цифры
			cmp al, 10; // сравниваем сумму с 10
			jge ELSE; // если сумма >= 10, то переход на ELSE
			add al, 48;
			mov str[1], al; // помещаем сумму вместо 2-ой цифры
			jmp EXIT; // безусловный переход на выход
		ELSE: // попадаем сюда, если не выполнется любое из условий
			mov str[2], 57; // заменяем предпоследнюю цифру на 9
			mov str[3], 57; // заменяем последнюю цифру на 9
		EXIT: nop; // пустая команда (конец асм вставки)
		}

		printf("Результат работы программы на языке Си: %s\n", str_copied);
		printf("Результат работы программы на ассемблере: %s\n\n", str);

		clear_input();

		printf("Хотите продолжить?\n0 - Нет\n1 - Да\n");

		int term = 1;
		while (term == 1) {
			if (scanf("%d", &tmp) != 1 || (tmp != 0 && tmp != 1)) {
				printf("Введено неверное значение\n");
				printf("Хотите продолжить?\n0 - Нет\n1 - Да\n");
				clear_input();
			}
			else {
				term = 0;
				flag = 1;
			}
		}
	}
	exit(0);
}