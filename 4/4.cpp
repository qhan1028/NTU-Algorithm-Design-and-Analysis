#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

// digit, head, num of 7, num of 4, mod 7
long long int table[20][10][20][20][7] = {0};

void init_table()
{
	for (int i = 0 ; i < 10 ; i++){
		if (i != 4 && i != 7){
			table[0][i][0][0][i%7]++;
		}
	}
	table[0][4][0][1][4]++;
	table[0][7][1][0][0]++;

	for (int dg = 0 ; dg < 19 ; dg++) {
		for (int head = 0 ; head < 10 ; head++) {
			for (int n7 = 0 ; n7 < 19 ; n7++) {
				for (int n4 = 0 ; n4 < 19 ; n4++) {
					for (int m7 = 0 ; m7 < 7 ; m7++) {
						for (int num = 0 ; num < 10 ; num++) {
							if (num == 7) {
								table[dg+1][head][n7+1][n4][(m7*10+num)%7] +=
								table[dg][head][n7][n4][m7];
							}
							else if (num == 4) {
								table[dg+1][head][n7][n4+1][(m7*10+num)%7] +=
								table[dg][head][n7][n4][m7];
							}
							else {
								table[dg+1][head][n7][n4][(m7*10+num)%7] +=
								table[dg][head][n7][n4][m7];
							}
						}
					}
				}
			}
		}
	}
	table[18][1][0][0][1]++;
}

long long int counted_range(int head, int expo)
{
	long long int result = head;
	for (int i = 0 ; i < expo ; i++) result *= 10;
	return result;
}

// 23456
long long int luckyNum(long long int num)
{
	// put into array
	int number[20];
	int pos = 0;
	while (num > 0) {
		number[pos] = num%10;
		num /= 10;
		pos++;
	}
	int len = pos-1; // 4
	long long count = 0;
	// within 10000
	for (int dg = len-1 ; dg >= 0 ; dg--) {
		for (int n7 = dg+1 ; n7 >= 3 ; n7--) {
			for (int n4 = n7-1 ; n4 >= 0 ; n4--) {
				for (int head = 9 ; head >= 1 ; head--) {
					count += table[dg][head][n7][n4][0];
				}
			}
		}
	}
	// 10001 ~ 20000
	for (int n7 = len+1 ; n7 >= 3 ; n7--) {
		for (int n4 = n7-1 ; n4 >= 0 ; n4--) {
			for (int head = number[len]-1 ; head >= 1 ; head--) {
				count += table[len][head][n7][n4][0];
			}
		}
	}
	// printf("temp count 1 : %lld\n", count);
	// 3456
	int e7 = 0; // existed 7
	int e4 = 0; // existed 4
	if (number[len] == 7) e7++;
	if (number[len] == 4) e4++;
	long long counted = 0;
	counted += counted_range(number[len], len);
	for (int dg = len-1 ; dg >= 0 ; dg--) {
		// 20000 + 0~3000 + 0~400 + 0~50 + 0~6
		for (int n7 = dg+1 ; n7 >= 0 ; n7--) {
			for (int n4 = dg+1 ; n4 >= 0 ; n4--) {
				for (int head = number[dg]-1 ; head >= 0 ; head--) {
					if ( (e7+n7) >= 3 && (e7+n7) > (e4+n4) ) {
						count += table[dg][head][n7][n4][(7-(counted%7))%7];
					}
				}
			}
		}
		if (number[dg] == 7) e7++;
		if (number[dg] == 4) e4++;
		counted += counted_range(number[dg], dg);
	}
	// printf("temp count 2 : %lld\n", count);
	// original number
	if (counted%7 == 0 && e7 >= 3 && e7 > e4) count++;
	return count;
}

int main()
{
	init_table();
	long long T, a, b;
	scanf("%lld", &T);
	while(T > 0) {
		scanf("%lld%lld", &a, &b);
		printf("%lld\n", luckyNum(b)-luckyNum(a-1));
		T--;
	}
	return 0;
}
