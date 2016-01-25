#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long L;
using namespace std;
// (a*b)%m = (a%m * b%m)%m
// (a^p) % p  = a % p

L T, c, n, p, e;

L compute(L a, L b, L exp)
{
	if (exp >= p) return compute(a, b, exp%(p-1)); 
	else if (exp > 1) 
	{
		return ( (compute(a, b, exp/2) * compute(a, b, exp/2))%p * compute(a, b, exp%2) ) % p;
	}
	else if (exp == 1) return (a+b)%p;
	else return 1;
}

bool compare(L a, L b){ return (( ((c*(a-b))%p+p) * compute(a, b, e))%p > p/2 );}

int main(void)
{
	scanf("%lld", &T);
	while(T>0)
	{
		scanf("%lld%lld%lld%lld", &n, &c, &e, &p);
		vector<L> input;
		for (int i = 0 ; i < n ; i++) input.push_back(i+1);
		sort(input.begin(), input.end(), compare);
		for (int i = 0 ; i < n ; i++) printf("%lld ", input[i]);
		printf("\n");
		T--;
	}
}
