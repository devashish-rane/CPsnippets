// construction takes (n.log)
// overlap friendly functions and associtive property
// logarithmic access generic
// doesnt support updates

long long st[MAXN][K + 1];

for (int i = 0; i < N; i++)
    st[i][0] = array[i];

for (int j = 1; j <= K; j++)
    for (int i = 0; i + (1 << j) <= N; i++)
        st[i][j] = st[i][j-1] + st[i + (1 << (j - 1))][j - 1];




//RMQ
//access constant time

// Range Minimum Queries (RMQ)
// These are the queries where the Sparse Table shines. 
// When computing the minimum of a range, it doesn't matter 
// if we process a value in the range once or twice. Therefore
//  instead of splitting a range into multiple ranges, we can also 
// split the range into only two overlapping ranges with power of two 
// length. E.g. we can split the range [1,6] into the ranges [1,4] and 
// [3,6]. The range minimum of [1,6] is clearly the same as the minimum 
// of the range minimum of [1,4] and the range minimum of [3,6]. So we can 
// compute the minimum of the range [L,R] with:

// min(st[L][j],st[R−2j+1][j]) where j=log2(R−L+1)
// This requires that we are able to compute log2(R−L+1) fast. 
// You can accomplish that by precomputing all logarithms:

int log[MAXN+1];
log[1] = 0;
for (int i = 2; i <= MAXN; i++)
    log[i] = log[i/2] + 1;

// Afterwards we need to precompute the Sparse Table structure.
 // This time we define f with f(x,y)=min(x,y).

int st[MAXN][K + 1];

for (int i = 0; i < N; i++)
    st[i][0] = array[i];

for (int j = 1; j <= K; j++)
    for (int i = 0; i + (1 << j) <= N; i++)
        st[i][j] = min(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
// And the minimum of a range [L,R] can be computed with:

int j = log[R - L + 1];
int minimum = min(st[L][j], st[R - (1 << j) + 1][j]);
// Time complexity for a Range Minimum Query is O(1).