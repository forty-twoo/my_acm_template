/*
    左偏树模板题，包括合并，删除操作
*/
#include<iostream>
#include<cstdio>
#define maxn 100010
using namespace std;
int n,m;
struct node{
    int v,dis,l,r,f;
}heap[maxn];
int find(int x){
    if(x==heap[x].f)return x;
    return heap[x].f=find(heap[x].f);
}
int merge(int a,int b){
    if(a==0)return b;
    if(b==0)return a;
    if(heap[a].v<heap[b].v)swap(a,b);
    heap[a].r=merge(heap[a].r,b);
    heap[heap[a].r].f=a;
    if(heap[heap[a].l].dis<heap[heap[a].r].dis)swap(heap[a].l,heap[a].r);
    if(heap[a].r==0)heap[a].dis=0;
    else heap[a].dis=heap[heap[a].r].dis+1;
    return a;
}
int pop(int a){
    int l=heap[a].l;
    int r=heap[a].r;
    heap[l].f=l;
    heap[r].f=r;
    heap[a].l=heap[a].r=heap[a].dis=0;
    return merge(l,r);
}
void work(){
    for(int i=1;i<=n;i++){
        scanf("%d",&heap[i].v);
        heap[i].dis=heap[i].l=heap[i].r=0;
        heap[i].f=i;
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        int a,b;scanf("%d%d",&a,&b);
        int aa=find(a),bb=find(b);
        if(aa==bb){puts("-1");continue;}
        heap[aa].v/=2;int u1=pop(aa);u1=merge(u1,aa);
        heap[bb].v/=2;int u2=pop(bb);u2=merge(u2,bb);
        printf("%d\n",heap[merge(u1,u2)].v);
    }
}
int main(){
   // freopen("Cola.txt","r",stdin);
    while(scanf("%d",&n)!=EOF)work();
    return 0;
}
