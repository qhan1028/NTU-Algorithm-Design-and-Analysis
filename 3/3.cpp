#include <cstdio>
#include <cstdlib>
#include <cmath>

typedef long long L;
using namespace std;
// (a*b)%m = (a%m * b%m)%m
// (a^p) % p  = a % p

int T, c, n, p;
L e;
L *Phistory, *Nhistory;
L prime[120] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139 ,149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 341, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 367, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659};

L compute(L a, L b, L exp)
{
	if (a+b == 1) return 1;
	if (exp >= p) return compute(a, b, exp%(L)(p-1)); 
	else if (exp > 1) 
	{
		L half = compute(a, b, exp/2);
		return ( (half * half)%p * compute(a, b, exp%2) ) % p;
	}
	else if (exp == 1) return (a+b)%p;
	else return 1;
}

bool compare(L a, L b)
{
	L num = a+b;
	L answer = 1;
	bool complete = false;
	if (Phistory[a+b] == -1) 
	{
		for (int i = 0 ; i < 120; i++)
		{
			if (complete) break;
			while (num % prime[i] == 0)
			{	
				if (Phistory[prime[i]] == -1) Phistory[prime[i]] = compute(1, prime[i]-1, e);
				answer *= Phistory[prime[i]];
				answer %= p;
				num /= prime[i];
				if (Phistory[num] != -1)
				{	
					complete = true;
					Phistory[a+b] = (answer * Phistory[num])%p;
					break;
				}
			}
		}
		if (!complete) Phistory[a+b] = (answer * compute(num-1, 1, e))%p;
	}
	if (Nhistory[abs(a-b)] == -1) Nhistory[abs(a-b)] = c*(a-b)%p+p;
	return (( Nhistory[abs(a-b)] * Phistory[a+b] )%p > p/2 );
}

L *merge(L *arr1, int size1, L *arr2, int size2)
{
	int index1 = 0, index2 = 0;
	L *arr = new L[size1+size2];
	for (int i = 0 ; i < size1 + size2 ; i++) 
	{
		if (index1 == size1 && index2 < size2) arr[i] = arr2[index2++];
		else if (index1 < size1 && index2 == size2) arr[i] = arr1[index1++];
		else if (compare(arr1[index1], arr2[index2])) arr[i] = arr1[index1++];
		else arr[i] = arr2[index2++];
	}
	delete [] arr1;
	delete [] arr2;
	return arr;
}

L *mergeSort(L *arr, int head, int end)
{
	if (head == end)
	{
		L *arr1 = new L[1];
		arr1[0] = arr[head];
		return arr1;
	}
	else if (head+1 == end)
	{
		L *arr1 = new L[1];
		L *arr2 = new L[1];
		arr1[0] = arr[head];
		arr2[0] = arr[end];
		return merge(arr1, 1, arr2, 1);
	}
	else 
	{
		int mid = (head+end)/2;
		L *arr1 = new L[mid-head+1];
		L *arr2 = new L[end-mid];
		arr1 = mergeSort(arr, head, mid);
		arr2 = mergeSort(arr, mid+1, end);
		return merge(arr1, mid-head+1, arr2, end-mid);
	}
}

int main(void)
{
	scanf("%d", &T);
	while(T>0)
	{
		scanf("%d%d%lld%d", &n, &c, &e, &p);
		L *input = new L[n];
		Phistory = new L[2*n];
		Nhistory = new L[n];
		for (int i = 0 ; i < n ; i++) 
		{
			input[i] = i+1;
			Phistory[2*i] = Phistory[2*i+1] = -1;
			Nhistory[i] = -1;
		}
		L *result = mergeSort(input, 0, n-1);
		for (int i = 0 ; i < n ; i++) printf("%lld ", result[i]);
		printf("\n");
		delete [] input; 
		delete [] Phistory;
		delete [] Nhistory;
		T--;
	}
	return 0;
}
