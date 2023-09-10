#include <stdio.h>

void PrintBits(unsigned int x) {
    int i;
    for (i = 8 * sizeof(x)-1; i >= 0; i--) 
    {
    (x & (1 << i)) ? putchar('1') : putchar('0');
    }
    printf("\n");
}

void PrintBitsOfByte(unsigned int x) {
    int i;
    for (i = 7; i >= 0; i--) 
    {
    (x & (1 << i)) ? putchar('1') : putchar('0');
    }
    printf("\n");
}

int bitAnd(int x, int y)
{
    int result;
// Ap dung cong thuc De Morgan: ~(a & b) = ~a | ~b
    PrintBits(x);
    PrintBits(y);
    PrintBits(~x);
    PrintBits(~y);
    PrintBits(~x | ~y);
    PrintBits(~(~x | ~y));
    result = ~(~x | ~y);
    return result;
}

int negative(int x)
{
    int result;
    PrintBits(x);
    PrintBits(~x); //số bù 1
    PrintBits(~x + 1); // số bù 2 là số đối của số nguyên cần tìm
    result = ~x + 1;
    return result;
}

int getByte(int x, int n)
{
    int result;
    PrintBits(x);
    PrintBits(n);
    PrintBits(n << 3); // n* (2^3) = n*8, lấy số bit tương ứng
    PrintBits(x >> (n << 3)); // dịch phải n*8 lần để lấy giá trị Byte cần tìm
    PrintBits(x >> (n << 3) & 255); // cần giữ lại Byte cuối nên ta & với mask 255 = 1111 1111
    result =  x >> (n << 3) & 255;
    return result;
}

int getnbit(int x, int n) 
{
    int result;
    PrintBits(x);
    PrintBits(n);
    PrintBits((1 << n) + (~1) + 1); // lấy 2^n - 1 làm số bị chia, tức là lấy n bit cuối cùng của số 1
    PrintBits(x & (1 << n) + (~1) + 1); // lấy x and với 2^n -1 để lấy được n bit cuối cùng bên phải
    result = x & (1 << n) + (~1) + 1;
    return result;
}

int mulpw2(int x, int n)
{
    int result;
    PrintBits(x);
    PrintBits(n);
    PrintBits(~n + 1); // lấy số bù 2 của n
    PrintBits(x >> (~n + 1)); // dịch phải để lấy x chia cho 2^n
    result = x >> (~n + 1);
    return result;
 }


int main()
{
	int score = 0;
	printf("Your evaluation result:");
	printf("\n1.1 bitAnd");
	if (bitAnd(3, -9) == (3 & -9))
	{
		printf("\tPass.");
		score += 1;
	}
	else
		printf("\tFailed.");

	printf("\n1.2 negative");
	if (negative(0) == 0 && negative(9) == -9 && negative(-5) == 5)
	{
		printf("\tPass.");
		score += 1;
	}
	else
		printf("\tFailed.");

	//1.3
	printf("\n1.3 getByte");
	if (getByte(8, 0) == 8 && getByte(0x11223344, 1) == 0x33)
	{
		printf("\tPass.");
		score += 2;
	}
	else
		printf("\tFailed.");

	printf("\n1.4 getnbit");
	if (getnbit(0, 0) == 0 && getnbit(31, 3) == 7 && getnbit(16, 4) == 0)
	{
		printf("\tPass.");
		score += 3;
	}
	else
		printf("\tFailed.");
	//1.5
	printf("\n1.5 mulpw2");
	if (mulpw2(10, -1) == 5 && mulpw2(15, -2) == 3 && mulpw2(32, -4) == 2)
	{
		if (mulpw2(10, 1) == 20 && mulpw2(50, 2) == 200)
		{
			printf("\tAdvanced Pass.");
			score += 4;
		}
		else
		{
			printf("\tPass.");
			score += 3;
		}
	}
	else
		printf("\tFailed.");





	printf("\n--- FINAL RESULT ---");
	printf("\nScore: %.1f", (float)score / 2);
	if (score < 5)
		printf("\nTrouble when solving these problems? Contact your instructor to get some hints :)");
	else
	{
		if (score < 8)
			printf("\nNice work. But try harder.");
		else
		{
			if (score >= 10)
				printf("\nExcellent. We found a master in bit-wise operations :D");
			else
				printf("\nYou're almost there. Think more carefully in failed problems.");
		}
	}

	printf("\n\n\n");
}
