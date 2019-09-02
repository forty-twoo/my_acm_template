const int maxn=2500*2500+3;
const int maxd=15;
const int seed=2500*2500+3;//是一个大素数
typedef long long LL;
struct HASH//哈希表
{
	int head[seed];
	int size;
	struct  NODE
	{
		int key;
		int value;
		int next;
	}edges[maxn];
	void init()
	{
		memset(head,-1,sizeof(head));
		size=0;
	}
	void insert(int key,int value)//插入值
	{
		int h=key%seed;
		for(int i=head[h];i!=-1;i=edges[i].next)
		{
			if(edges[i].key==key)
			{
				edges[i].value=max(value,edges[i].value);
				return;
			}
		}
		edges[size].key=key;
		edges[size].value=value;
		edges[size].next=head[h];
		head[h]=size++;
	}
	int search(int key)//寻找
	{
		int h=key%seed;
		for(int i=head[h];i!=-1;i=edges[i].next)
		{
			if(edges[i].key==key)
			{
				return edges[i].value;
			}
		}
		return -1;
	}
}tr;
