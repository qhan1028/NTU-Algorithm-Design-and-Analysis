#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

typedef struct {
	int a;
	int b;
	int dis;
} Edge;

int set[100001];

/* sorting */
int compare(Edge a,Edge b) {return a.dis<b.dis;}

template <class L>
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

template <class L>
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

/* spanning tree handling */
int find(int p){
	if(p==set[p])
		return p;
	else
		return (set[p]=find(set[p]));
}
void combine(int a,int b){ set[find(a)]=find(b);}

int main(){
	int cases;
	cin>>cases;
	int n,e;
	vector<Edge> edge;
	Edge node; // for push back into vector
	int x,y;
	vector<int> mst;
	vector<Edge> must;
	int weight,weight_mst;
	for(int i=0;i<cases;i++){
		cin>>n>>e;
		for(int i=0;i<=n;i++) set[i]=i; // init
		edge.clear();
		must.clear();
		mst.clear();
		weight=0;
		Edge *input = (Edge*)malloc((e+1)*sizeof(Edge));
		for(int j=0;j<e;j++){
			scanf("%d%d%d",&input[j].a,&input[j].b,&input[j].dis);
		}
		Edge *sorted = mergeSort(input, 0, e-1);
		for (int k = 0 ; k < e ; k++) edge.push_back(sorted[k]);
		// sort(edge.begin(),edge.end(),compare);
		for(x=0,y=0;(x<n-1)&&y<e;x++,y++){
			while( find(edge[y].a)==find(edge[y].b) && y!=e) {
				y++;
			}
			combine(edge[y].a,edge[y].b);
			weight+=edge[y].dis;
			mst.push_back(y);
		}
		/*for(int j=0;j<mst.size();j++){
			cout<<edge[mst[j]].a<<" "<<edge[mst[j]].b<<" "<<edge[mst[j]].dis<<endl;
		}*/
		for(int j=0;j<mst.size();j++){
			for(int i=0;i<=n;i++) set[i]=i; // init
			weight_mst=0;
			for(x=0,y=0;(x<n-1)&&y<e;x++,y++){
				if(y==mst[j])
					y++;
				while( find(edge[y].a)==find(edge[y].b)&&y!=e ) {
					y++;
					if(y==mst[j])
						y++;
				}
				combine(edge[y].a,edge[y].b);
				weight_mst+=edge[y].dis;
			}
			//cout<<"j="<<j<<" x="<<x<<" skiped edge:"<<mst[j]<<" weight_mst="<<weight_mst<<" weight="<<weight<<endl;
			
			if(x==n-1){
				if(weight_mst!=weight){
					must.push_back(edge[ mst[j] ]);
				}
			}
			else{
				must.push_back(edge[ mst[j] ]);
			}
		}
		cout<<must.size()<<" ";
		weight=0;
		for(int j=0;j<must.size();j++){
			weight+=must[j].dis;
		}
		cout<<weight<<endl;
		
		free(input); free(sorted);
	}
	return 0;
}
