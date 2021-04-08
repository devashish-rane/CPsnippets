// Segment tree
// space 4n linear
// update log
// query log

#include<bits/stdc++.h>

  using namespace std;

  //debugging functions
  #define show(x)               cout<<"\n"<<"showing... :"<<x<<"\n";
  #define _log                  cout<<"\niterated through\n";


int n=100;
vector<int> seg(4*n+1);
vector<int> lazy(4*n+1,0);

//lb and ub are major bounds  of input array
void build(vector<int> a,int v,int lb,int ub){
    if(lb==ub) 
      seg[v]=a[lb];
     else{
       int mid= (lb+ub)/2;
       build(a,v*2,lb,mid);
       build(a,v*2+1,mid+1,ub);
       seg[v]= seg[v*2] + seg[v*2+1];
     } 
}

int sum(int v,int lb,int ub,int l,int r){
     if(l>r) return 0; //if out of upper or lower bound
     if(r==ub and l==lb)  return seg[v];   //found value the return seg
     
     int mid =  (ub + lb)/2;
     int p1 = sum(2*v, lb, mid, l, min(r,mid));
     int p2 = sum(2*v+1, mid+1, ub, max(l,mid+1), r);
    return (p1 + p2);
}

//NOTE : SIMPLE UPDATE HAS IF ELSE CONSTRUCT RANGE DOSENT HAVE IT
void update(int v,int lb,int ub,int pos ,int val){  //position for vertex "v"
     
     if(/*r==ub and l==lb*/lb==ub)  {
        seg[v]+= val;   //adding update
        //return;
        }
      else{    
        int mid =  (ub + lb)/2;
        if(pos <= mid )
        update(2*v, lb, mid, pos,val);
        else
        update(2*v+1, mid+1, ub, pos ,val);
        seg[v] = seg[v*2] + seg[v*2+1];  
      }
}


void rangeupdate(int v,int lb,int ub,int l,int r,int add){
        if(l>r) return ; //if out of upper or lower bound
     if(/*r==ub and l==lb*/lb==ub)  {
        seg[v]= seg[v]+add;   //adding update
        return;
        }
    
        int mid =  (ub + lb)/2;
        rangeupdate(2*v, lb, mid, l, min(r,mid),add);
        rangeupdate(2*v+1, mid+1, ub, max(l,mid+1), r,add);
        
        seg[v] = seg[v*2] +seg[v*2+1];
}





=====================lazy updates in all functions NOTE
bool marked[1000]={0};
int t[1000]={0}
void push(int v) {
    if (marked[v]) {
        t[v*2] = t[v*2+1] = t[v];
        marked[v*2] = marked[v*2+1] = true;
        marked[v] = false;
    }
}

void update(int v, int tl, int tr, int l, int r, int new_val) {
    if (l > r) 
        return;
    if (l == tl && tr == r) {
        t[v] = new_val;
        marked[v] = true;
    } else {
        push(v);
        int tm = (tl + tr) / 2;
        update(v*2, tl, tm, l, min(r, tm), new_val);
        update(v*2+1, tm+1, tr, max(l, tm+1), r, new_val);
    }
}

int get(int v, int tl, int tr, int pos) {
    if (tl == tr) {
        return t[v];
    }
    push(v);
    int tm = (tl + tr) / 2;
    if (pos <= tm) 
        return get(v*2, tl, tm, pos);
    else
        return get(v*2+1, tm+1, tr, pos);
}




================================================
//persistent data segment tree
struct Vertex {
    Vertex *l, *r;
    int sum;

    Vertex(int val) : l(nullptr), r(nullptr), sum(val) {}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

Vertex* build(int a[], int tl, int tr) {
    if (tl == tr)
        return new Vertex(a[tl]);
    int tm = (tl + tr) / 2;
    return new Vertex(build(a, tl, tm), build(a, tm+1, tr));
}

int get_sum(Vertex* v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && tr == r)
        return v->sum;
    int tm = (tl + tr) / 2;
    return get_sum(v->l, tl, tm, l, min(r, tm))
         + get_sum(v->r, tm+1, tr, max(l, tm+1), r);
}

Vertex* update(Vertex* v, int tl, int tr, int pos, int new_val) {
    if (tl == tr)
        return new Vertex(new_val);
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return new Vertex(update(v->l, tl, tm, pos, new_val), v->r);
    else
        return new Vertex(v->l, update(v->r, tm+1, tr, pos, new_val));
}
=====================================================

int main(){
    
   
   vector<int > a ={1,2,3,4,5,6,7,8,9};
   for(int i: a) cout<<i<<" ";
   cout<<"\n";
   build(a,1,0,8);
   for(int i=0;i<16;i++){
     cout<<seg[i]<<" ";
   }
   cout<<"\nMaking query\n";
   cout<<sum(1,0,8,0,4)<<"\n";    //vertex index is default 1
     lazyupdate(1,0,8,0,4,10);
   cout<<sum(1,0,8,0,4);    //vertex index is default 1
  return 0;
}




//extra
// ================================================== 2D using x,y vwctors
int sum_y(int vx, int vy, int tly, int try_, int ly, int ry) {
    if (ly > ry) 
        return 0;
    if (ly == tly && try_ == ry)
        return t[vx][vy];
    int tmy = (tly + try_) / 2;
    return sum_y(vx, vy*2, tly, tmy, ly, min(ry, tmy))
         + sum_y(vx, vy*2+1, tmy+1, try_, max(ly, tmy+1), ry);
}

int sum_x(int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
    if (lx > rx)
        return 0;
    if (lx == tlx && trx == rx)
        return sum_y(vx, 1, 0, m-1, ly, ry);
    int tmx = (tlx + trx) / 2;
    return sum_x(vx*2, tlx, tmx, lx, min(rx, tmx), ly, ry)
         + sum_x(vx*2+1, tmx+1, trx, max(lx, tmx+1), rx, ly, ry);
}

// This function works in O(lognlogm) time, since it first descends the free
//  in the first coordinate, and for each traversed vertex in the tree it makes 
//  a query in the corresponding Segment Tree along the second coordinate.

// Finally we consider the modification query. We want to learn how to modify 
// the Segment Tree in accordance with the change in the value of some element a[x][y]=p.
//  It is clear, that the changes will occur only in those vertices of the first Segment 
//  Tree that cover the coordinate x (and such will be O(logn)), and for Segment Trees
//   corresponding to them the changes will only occurs at those vertices that 
//   covers the coordinate y (and such will be O(logm)). Therefore the implementation

//    will be not very different form the one-dimensional case, only now we first descend 
//    the first coordinate, and then the second.

void update_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int new_val) {
    if (ly == ry) {
        if (lx == rx)
            t[vx][vy] = new_val;
        else
            t[vx][vy] = t[vx*2][vy] + t[vx*2+1][vy];
    } else {
        int my = (ly + ry) / 2;
        if (y <= my)
            update_y(vx, lx, rx, vy*2, ly, my, x, y, new_val);
        else
            update_y(vx, lx, rx, vy*2+1, my+1, ry, x, y, new_val);
        t[vx][vy] = t[vx][vy*2] + t[vx][vy*2+1];
    }
}

void update_x(int vx, int lx, int rx, int x, int y, int new_val) {
    if (lx != rx) {
        int mx = (lx + rx) / 2;
        if (x <= mx)
            update_x(vx*2, lx, mx, x, y, new_val);
        else
            update_x(vx*2+1, mx+1, rx, x, y, new_val);
    }
    update_y(vx, lx, rx, 1, 0, m-1, x, y, new_val);
}