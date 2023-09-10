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

/* int mulpw2(int x, int n)
{
    int result;
    PrintBits(x);
    PrintBits(n);
    PrintBits(~n + 1); // lấy số bù 2 của n
    PrintBits(x >> (~n + 1)); // dịch phải để lấy x chia cho 2^n
    result = x >> (~n + 1);
    return result;
 }

*/

int mulpw2(int x, int n)
{
	int result;
	PrintBits(x);
	PrintBits(n);
	int i = n >> 31 ; // lấy bit dấu của n để xem n âm hay n dương
	PrintBits(i);
	int x1 = x >> (~n + 1); // x1 tính 2^n với n âm
	int x2 = x << n; // x2 tính 2^n với n dương
    result = (~i & (x2)) | (i & (x1)); // ta dùng cấu trúc MUX 2 to 1 
	// để chọn xem nên lấy giá trị x1 hay x2. Nếu i = 0 tức là số dương
	// thì nó sẽ chọn x2, ngược lại nó sẽ chọn x1
	PrintBits(result);
	return result;
}

int isSameSign(int x, int y)
{
	int result;
	PrintBits(x);
	PrintBits(y);
	PrintBits((x >> 31)); // dịch phải 31 bit để lấy bit dấu của x
	PrintBits((y >> 31)); // dịch phải 31 bit để lấy bit dấu của y
	PrintBits(!((x >> 31) ^(y >> 31))); // ta XOR hai bit dấu lại 
	// rồi lấy giá trị phủ định để được kết quả như đề yêu cầu
	result =  !((x >> 31) ^(y >> 31));
	return result;
}

int is8x(int x)
{
	int result;
	PrintBits(x);
	PrintBits((x ^ 0x111) & 1); // nếu x chia hết cho 8 thì 3 bit cuối
	// của x phải là 0. Ta XOR với 0x111 để ra kết quả như đề yêu cầu 
	// rồi AND với '1' để lấy bit bên phải cùng nhất
	result =(x ^ 0x111) & 1;
	return result;

}

int isPositive(int x)
{
	int result;
	PrintBits(x);
	PrintBits((x >> 31));
	PrintBits((!x) ^ !(x >> 31)) ; // lấy bit dấu XOR với nhau.
	// Nếu bit dấu là 0 (số dương) thì kết quả trả về 1, ngược lại trả về 0
	result = ((!x) ^ !(x >> 31)) ;
	return result;
}


int isLess2n(int x, int n)
{
	int result;
	PrintBits(x);
	PrintBits(n);
	PrintBits(x >> n); // dịch x sang phải n lần để lấy cái bit có 
	//số thứ tự cao hơn n của x, nếu kết quả = 0 nghĩa là các bit thứ tự
	// cao hơn n = 0 nên suy ra x bé hơn 2^n
	PrintBits((x >> n) ^ 1); // XOR kết quả ở trên với 1 
	PrintBits(((x >> n) ^ 1) & 0x1); // AND với 0x1 để lấy bit bên phải cùng duy nhất theo đề bài
	result = (((x >> n) ^ 1) & 0x1 );
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

	printf("\n2.1 isSameSign");
	if (isSameSign(4, 2)==1 && isSameSign(13, -4)==0 && isSameSign(0, 10)==1)
	{
		printf("\tPass.");
		score += 2;
	}
	else
		printf("\tFailed.");

	printf("\n2.2 is8x");
	if (is8x(16)==1 && is8x(3)==0 && is8x(0)==1)
	{
		printf("\tPass.");
		score += 2;
	}
	else
		printf("\tFailed."); 

	printf("\n2.3 isPositive");
	if (isPositive(10)==1 && isPositive(-5)==0 && isPositive(0)==0)
	{
		printf("\tPass.");
		score += 3;
	}
	else
		printf("\tFailed.");

	printf("\n2.4 isLess2n");
	if (isLess2n(12, 4)==1 && isLess2n(8, 3)==0 && isLess2n(15, 2)==0)
	{
		printf("\tPass.");
		score += 3;
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
