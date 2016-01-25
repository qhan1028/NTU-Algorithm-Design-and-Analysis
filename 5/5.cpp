#include <cstdio>

#define MAX_DG 1800
#define MAX_DAY 1000

// dg is num of exponential of ten
void findS(int days)
{
	int checkSum[MAX_DAY];
	// input check sum
	for (int i = 0 ; i < days ; i++) scanf("%d", &checkSum[i]);
	int sum[MAX_DAY][MAX_DG] = {0};
	int dg = 0;
	int first = checkSum[0];
	// put int first number	
	while (first > 0){
		if (first > 9) {
			sum[0][dg] += 9;
			dg++;
		}
		else if (first == 9) sum[0][dg] += 9;
		else sum[0][dg] += first;
		first -= 9;
	}
	int pre_dg = dg;
	int pre_c = checkSum[0];
	for (int i = 1 ; i < days ; i++) {
		// copy the previous content
		for (int j = 0 ; j < MAX_DG ; j++) sum[i][j] = sum[i-1][j];
		// if c is larger
		int c = checkSum[i];
		if (c > pre_c) {
			int rest = c - pre_c;
			dg = 0;
			// add numbers from lowest digit
			while (rest > 0) {
				if (sum[i][dg] < 9) {
					sum[i][dg]++;
					rest--;
				} else dg++;
			}
		}
		// if c is smaller or equal
		else if (c <= pre_c) {
			int rest = c - pre_c; // rest must <= 0
			dg = 0;
			// collect numbers from lowest digit
			// and make "rest" > 0
			while(rest <= 0) {
				rest += sum[i][dg];
				sum[i][dg] = 0;
				dg++;
			}
			int add_dg = dg-1;
			dg = 0;
			int bigger = 0;
			while (rest > 0) {
				// enlarge the sum
				if (!bigger) {
					// simple case
					if (rest > sum[i-1][add_dg] && sum[i-1][add_dg] < 9) {
						sum[i][add_dg] += (sum[i-1][add_dg]+1);
						rest -= (sum[i-1][add_dg]+1);
						bigger = 1;
					}
					// complicated case
					// when the current digit is 9
					// or the higher digit which is not 9
					// collect "9" during finding the digit which is < 9
					else if (rest <= sum[i-1][add_dg] || sum[i-1][add_dg] == 9) {
						int temp = add_dg+1;
						while (sum[i][temp] == 9) {
							sum[i][temp] = 0;
							temp++;
							rest += 9;
						}
						sum[i][temp]++;
						rest--;
						bigger = 1;
					}
				}
				// add the rest from the lowest digit
				else {
					if (sum[i][dg] < 9) {
						sum[i][dg]++;
						rest--;
					} else dg++;
				}
			}
		}
		pre_c = c;
	}
	// print result
	dg = 0;
	for (int i = 0 ; i < days ; i++) {
		// find the first digit which is not 0
		for (int j = MAX_DG-1 ; j >= 0 ; j--) {
			if (sum[i][j] != 0) {
				dg = j;
				break;
			}
		}
		// start printing
		for (int j = dg ; j >= 0 ; j--) {
			printf("%d", sum[i][j]);
		}
		// avoid trivial space
		if (i < days-1) printf(" ");
	}
	printf("\n");
}

int main(void)
{
	int T;
	int days = 0;
	scanf("%d", &T);
	for (int i = 0 ; i < T ; i++) {
		scanf("%d", &days);
		findS(days);
	}
	return 0;
}
