//
// Created by miss on 2/5/19.
//

/*
 *  巴什博弈（Bash Game）
 *巴什博弈是我认为的最简单最能理解的博弈论了其他的算法我头都晕了。
    巴什博弈（同余理论）：一堆n个物品，两个人从轮流中取出（1~m）个；最后取光者胜。
    n=K*(m+1)+r;先取者拿走r个，那么后者无论拿走（1~m）个
    先者只要拿的数目的和为m+1那么先手就必赢。
    反之若n=k*(m+1)，那么先者不论怎样都会输。
 */

int Bgame(int n,int m)
{
    if(n%(m+1)) return 0;
    return 1;
}

/*
 * 尼姆博弈论（Nimm Game)
 * 尼姆博弈论（异或理论）：n堆物品，两人轮流取，每次取某堆中不少于1个，最后取完者胜。
我理解Nimm Game 就是将他当做一种规律来理解的至于为什么会有这种规律我们先暂时不去讨论想看的可以看这：尼姆游戏

假如有3堆物品(a,b,c)
（0，0，0）状态时先手是一个必输局势因为没有东西可取，(0,n,n) 状态时也是必输局势只要后者在另一堆取得物品与前者一样多时那么前者也就是必输局势。
 慢慢分析(1,2,3)也是一个必输局势。如果我们将其转化为二进制形式并通过异或运算(^)我们会发现：
0001^0010^0011=0000
通过验证所有的堆数量累^后只要为0就都是必输局势，所以我们就只要记住这个规则就好了。
 */


// Last One Take Win.
int Ngame(int n)
{
    int flag=0;
    for(int i=0; i < n; i++) { flag^=f[i];}
    if(flag)return 1;
    return 0;
}

// Last One Take Lose.
int misèrenim() {
    int n, a, flag, c, max, over;
    while (scanf("%d", &n) != EOF) {
        flag = 0, c = 0, max = 0, over = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a);
            flag ^= a;
            if (a > 1)
                c++;
            if (a > max)
                max = a;
            if (a > 0)
                over++;
        }
        if (c <= 1) {
            if (max == 1 && over % 2 == 1)
                printf("orzwang9897\n");
            else
                printf("orzwym6912\n");
            continue;
        }

        if (flag == 0)
            printf("orzwang9897\n");
        else
            printf("orzwym6912\n");
    }
    return 0;
}

/*
 * 威佐夫博奕（Wythoff Game）
 * 威佐夫博奕（黄金分割）：两堆（ak,bk）(ak<=bk)个物品，两人轮流取，每次从一堆中取k个或者从2堆中同时取k个，最后面对(0,0)局面的输（设ak<=bk是为了忽略顺序的影响）。
这里的必输局势：（0，0）、（1，2）、（3，5）、（4，7）、（6，10）、（8，13）、（9，15）、（11，18）、（12，20）。
从这些必输局势发现如下公式：
ak=[k*(1+√5)/2] bk=ak+k （k=0，1，2，…,n 方括号表示取整函数)
如果给出的ak和bk满足这个公式那么它就是一个必输局势
 */

int Wgame(int a,int b)
{
a=min(a,b);
b=max(a,b);//先交换大小位置
int k=b-a;
double path=(sqrt(5)+1)/2;
if(a==floor(path*k) return 1;
return 0;
}

/*
 * 斐波那契博弈（Fibonacci Nim Game）
 *
 * 斐波那契博弈（斐波那契额定理）：一堆石子有n个，两人轮流取，先取者第1次可以取任意多个，但不能全部取完，以后每次取的石子数不能超过上次取子数的2倍。取完者胜.
这同样是一个规律：先手胜当且仅当n不是斐波那契数（n为物品总数）；
 */

int FNgame(int n)
{
    if(n==1) return 1;
    int f[1e5];
    f[0]=f[1]=1;
    for(int i=2;f[i-1]<n;i++)
    {
        f[i]=f[i-1]+f[i-2];
        if(f[i]==n)return 1;
    }
    return 0;
}

/*
 * Sprague-Grundy定理（SG定理）
 *
 * SG函数可以说是博弈论中很重要的运用，有了SG函数就可以解决很多很难解决的博弈问题，也是解决例如nim博弈和翻硬币博弈的一些基础。
先引入一道题：两个玩家，一堆石子n个；规则：轮流取石子每次只能取1，3或4个；谁取走最后一枚石子谁就获胜。
先引入一个概念：
P点 即必败点，某玩家位于此点，只要对方无失误，则必败。
N点 即必胜点，某玩家位于此点，只要自己无失误，则必胜。
定理：
1，所有总结点都是P点；
2，无论任何操作，必败点P都能进入必胜点N；
3，从任何必胜点N，至少有一种方式进入必败点P；
所以:
当n=0时，为P点，因为你没有石子可取；
当n=1，2或3时，为N点，因为你都可以一次取完；
当n=4时，为P点，因为你一次不可能全部去完但下一次的操作可以全部取完；
如此类推：
n:0 1 2 3 4 5 6 7 8 9…
position:P N N P N N P N N P…
SG函数：
先引进一个定理mex(miniml,excludant)运算，就是对集合求运算，表示不属于这个集合的最小非负整数。例如： mex{1，2，4}=0，mex{0,2,3,6}=1。
对于任意的状态x，定义SG(x)=mex(S),其中S是x后继状态(相当于一个树节点下的子节点)的SG函数值集合。假如x的后继状态有三个a,b,c,那么SG(x)=mex{SG(a),SG(b),SG(c)}。如果SG(x)=0,那么x就是P点。
如上题所示每次只能取{1，3，4}；
SG(0)=0,f[]={1,3,4};

x=1 时，可以取走1 - f{1}个石子，剩余{0}个，所以 SG[1] = mex{ SG[0] }= mex{0} = 1;

x=2 时，可以取走2 - f{1}个石子，剩余{1}个，所以 SG[2] = mex{ SG[1] }= mex{1} = 0;

x=3 时，可以取走3 - f{1,3}个石子，剩余{2,0}个，所以 SG[3] = mex{SG[2],SG[0]} = mex{0,0} =1;

x=4 时，可以取走4- f{1,3,4}个石子，剩余{3,1,0}个，所以 SG[4] = mex{SG[3],SG[1],SG[0]} = mex{1,1,0} = 2;

x=5 时，可以取走5 - f{1,3,4}个石子，剩余{4,2,1}个，所以SG[5] = mex{SG[4],SG[2],SG[1]} =mex{2,0,1} = 3;
以此类推：
x： 0 1 2 3 4 5 6 7 8….

SG[x]： 0 1 0 1 2 3 2 0 1….
 */

int f[N],SG[N_MAX],s[N_MAX];
void getSG(int n)
{
    int i,j;
    memset(SG,0,sizeof(SG));
    for(i=1;i<=n;i++)
    {
        memset(S,0,sizeof(S));//每次后继状态都清空
        for(j=0;f[j]<=i&&j<=N;j++)
            S[SG[i-f[j]]=1;//对所有的后继状态SG值标记
        for(j=0;;j++)//查询当前的
        {
            if(!S[j]){SG[i]=j;break;}
        }
    }
}



// https://blog.csdn.net/tomorrowtodie/article/details/52145645