#include <cstdio>

int main(){
	int T, x;
	scanf("%d", &T);
	for (int i = 0 ; i < T ; i++) {
		scanf("%d", &x);
		if (x <= 1000) printf("%d 0\n", x);
		else printf("%d 1000\n", x - 1000);
	}
	return 0;
}