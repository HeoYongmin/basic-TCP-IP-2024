#include <stdio.h>

int main(int argc, char* argv[])
{
	printf("�����ϴ� ���ڰ���: %d\n", argc);
	printf("��������: %s\n", argv[0]);

	for (int i = 1; i < argc; i++) {
		printf("��������: %s\n", argv[i]);
	}

	return 0;
}