#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAXN 65536
#define MAXLG 17

char A[MAXN];

struct entry
{
	int nr[2];
	int p;
} L[MAXN];

int P[MAXLG][MAXN];
int N,i;
int stp, cnt;



//   N.log^2N complexity   [difference between this and n.logn is negligible upto 10^5]
int cmp(struct entry a, struct entry b)
{
	return a.nr[0]==b.nr[0] ?(a.nr[1]<b.nr[1] ?1: 0): (a.nr[0]<b.nr[0] ?1: 0);
}

int main()
{
	gets(A);
	for(N=strlen(A), i = 0; i < N; i++)
		P[0][i] = A[i] - 'a';
	
	for(stp=1, cnt = 1; cnt < N; stp++, cnt *= 2)
	{
		for(i=0; i < N; i++)
		{
			L[i].nr[0]=P[stp- 1][i];
			L[i].nr[1]=i +cnt <N? P[stp -1][i+ cnt]:-1;
			L[i].p= i;
		}
		sort(L, L+N, cmp);
		for(i=0; i < N; i++)
			P[stp][L[i].p] =i> 0 && L[i].nr[0]==L[i-1].nr[0] && L[i].nr[1] == L[i- 1].nr[1] ? P[stp][L[i-1].p] : i;
	}
	return 0;
}


//linear complexity  Kasai's algorithm O(n)
vector<int> kasai(string s, vector<int> sa)
{
    int n=s.size(),k=0;
    vector<int> lcp(n,0);
    vector<int> rank(n,0);

    for(int i=0; i<n; i++) rank[sa[i]]=i;

    for(int i=0; i<n; i++, k?k--:0)
    {
        if(rank[i]==n-1) {k=0; continue;}
        int j=sa[rank[i]+1];
        while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
        lcp[rank[i]]=k;
    }
    return lcp;
}