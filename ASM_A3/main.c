#define _CRT_SECURE_NO_WARNINGS

/*
���� ������ �� ������� ���������� ����. ���� ������ ��� ����� �� ��������� �
������ ���������, �� �������� ������ ����� ������ ������ � ������� (���� ���
��������), ����� � �������� ��������� ��� ����� ���������
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
			printf("������� ������ �� 4 ���� ��� ��������:\n");
			scanf("%s", &str);
			if (!isdigit(str[0]) || !isdigit(str[1]) || !isdigit(str[2]) || !isdigit(str[3])) {
				printf("��������� ����.\n");
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
			mov al, str[0]; // �������� 1-�� ����� � AL
			mov bl, str[1]; // �������� 2-�� ����� � BL
			cmp al, bl; // ���������� 1-�� � 2-�� �����
			jz ELSE; // ���� �����, �� ������� �� ELSE
			mov cl, str[3]; // �������� 4-�� ����� � CL
			cmp cl, al; // ���������� 4-�� � 1-�� �����
			jge ELSE; // ���� 4-�� ����� >= 1-��, �� ������� �� ELSE
			cmp cl, bl; // ���������� 4-�� � 2-�� �����
			jge ELSE; // ���� 4-�� ����� >= 2-��, �� ������� �� ELSE
			mov dl, str[2];
			sub al, 48;
			sub dl, 48;
			add al, dl; // ���������� 1-�� � 3-� �����
			cmp al, 10; // ���������� ����� � 10
			jge ELSE; // ���� ����� >= 10, �� ������� �� ELSE
			add al, 48;
			mov str[1], al; // �������� ����� ������ 2-�� �����
			jmp EXIT; // ����������� ������� �� �����
		ELSE: // �������� ����, ���� �� ���������� ����� �� �������
			mov str[2], 57; // �������� ������������� ����� �� 9
			mov str[3], 57; // �������� ��������� ����� �� 9
		EXIT: nop; // ������ ������� (����� ��� �������)
		}

		printf("��������� ������ ��������� �� ����� ��: %s\n", str_copied);
		printf("��������� ������ ��������� �� ����������: %s\n\n", str);

		clear_input();

		printf("������ ����������?\n0 - ���\n1 - ��\n");

		int term = 1;
		while (term == 1) {
			if (scanf("%d", &tmp) != 1 || (tmp != 0 && tmp != 1)) {
				printf("������� �������� ��������\n");
				printf("������ ����������?\n0 - ���\n1 - ��\n");
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