//Mo's algorithm   ()
//sqrt decomposition  (sqrt(n))
#include<bits/stdc++.h>
using namespace std;



////sqrt decomposition
int n;
vector<int> a (n);

// preprocessing
int len = (int) sqrt (n + .0) + 1; // size of the block and the number of blocks
vector<int> b (len);
for (int i=0; i<n; ++i)
    b[i / len] += a[i];

// answering the queries
for (;;) {
    int l, r;
  // read input data for the next query
    int sum = 0;
    for (int i=l; i<=r; )
        if (i % len == 0 && i + len - 1 <= r) {
            // if the whole block starting at i belongs to [l, r]
            sum += b[i / len];
            i += len;
        }
        else {
            sum += a[i];
            ++i;
        }
}


//floating division operation
int sum = 0;
int c_l = l / len,   c_r = r / len;   //shrinking the index to smaller "sqrt array index"

if (c_l == c_r)     //if in same block
    for (int i=l; i<=r; ++i)
        sum += a[i];
else {
    //left part in case of ------*==== > === is considered part
    for (int i=l, end=(c_l+1)*len-1; i<=end; ++i)   
        sum += a[i];
    //iterrate the sqrt array index
    for (int i=c_l+1; i<=c_r-1; ++i)
        sum += b[i];
    //right part ========*--------  > ===is considered
    for (int i=c_r*len; i<=r; ++i)
        sum += a[i];
}





/// Mo's algorithm
void remove(idx);  // TODO: remove value at idx from data structure
void add(idx);     // TODO: add value at idx from data structure
int get_answer();  // TODO: extract the current answer of the data structure

int block_size;

struct Query {
    int l, r, idx;
    bool operator<(Query other) const
    {
        return make_pair(l / block_size, r) <
               make_pair(other.l / block_size, other.r);
    }
};

vector<int> mo_s_algorithm(vector<Query> queries) {
    vector<int> answers(queries.size());
    sort(queries.begin(), queries.end());

    // TODO: initialize data structure

    int cur_l = 0;
    int cur_r = -1;
    // invariant: data structure will always reflect the range [cur_l, cur_r]
    for (Query q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(cur_r);
            cur_r--;
        }
        answers[q.idx] = get_answer();
    }
    return answers;
}

//make sense
// In odd blocks sort the right index in ascending order and in even blocks sort
//  it in descending order. This will minimize the movement of right pointer, 
//  as the normal sorting will move the right pointer from the end back to the
//   beginning at the start of every block. With the improved version this resetting
//    is no more necessary.
bool cmp(pair<int, int> p, pair<int, int> q) {
    if (p.first / BLOCK_SIZE != q.first / BLOCK_SIZE)
        return p < q;
    return (p.first / BLOCK_SIZE & 1) ? (p.second < q.second) : (p.second > q.second);
}


// Sorting all queries will take O(QlogQ).
// How about the other operations? How many times will the add and remove be called?
// Let's say the block size is S.
// If we only look at all queries having the left index in the same block, 
// the queries are sorted by the right index. Therefore we will call add(cur_r) 
// and remove(cur_r) only O(N) times for all these queries combined. This gives O(NSN)
//  calls for all blocks.

// The value of cur_l can change by at most O(S) during between two queries. 
// Therefore we have an additional O(SQ) calls of add(cur_l) and remove(cur_l).
// For S≈N−−√ this gives O((N+Q)N−−√) operations in total. Thus the complexity 
// is O((N+Q)FN−−√) where O(F) is the complexity of add and remove function.






int main(){   
    
    int s
    return 0;
}
