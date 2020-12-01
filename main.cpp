#include <iostream>
#include <stack>
#include <queue>
#include <string.h>
using namespace std;
typedef char SqBiTree[100];
SqBiTree bt;
typedef struct BiTNode{
    char data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
//typedef struct CSNode{   //树的二叉链表（孩子-兄弟）存储表示
//    char data;
//    struct CSNode *firstchild,*nextsibling;
//}CSNode,*CSTree;
//可以继续使用二叉树的结构体
int number=0;   //节点总数，也包括空节点
void CreateBiTree(BiTree &T)   //采用先序输入，二叉链存储二叉树
{
    char ch=getchar();
    if(ch==' ') T=NULL;
    else {
    if(!(T=(BiTNode*)malloc((sizeof(BiTNode)))))
        cout<<"OVERFLOW";
    T->data=ch;
    CreateBiTree(T->lchild);
    CreateBiTree(T->rchild);
    }
}

BiTree CreateBiTree_List(char str[])   //接受类广义表形式输入二叉树并创建二叉链树
{
    BiTNode* root=NULL;
    int n=strlen(str);
    stack <BiTNode*> S;
    int k=-1;
    for(int i=0;i<n;i++)
    {
        if(str[i]=='(')
            k=0;
        else if(str[i]==',')
        {
            k=1;
            S.pop();
        }
        else if(str[i]==')')
            S.pop();
        else {
            BiTNode* temp=(BiTNode*)malloc((sizeof(BiTNode)));
            temp->data=str[i];
            temp->lchild=NULL;
            temp->rchild=NULL;
            if(k==-1)   //单独处理根节点
            {
                S.push(temp);
                root=S.top();
            }
            else if(k==0)
            {
                S.top()->lchild=temp;
                S.push(temp);
            }
            else if(k==1)
            {
                S.top()->rchild=temp;
                S.push(temp);
            }
        }
    }
    return root;
}
void CreateSqBiTree(SqBiTree &bt)   //采用层次输入，顺序存储二叉树
{
    while(1)
    {
     char ch=getchar();
     if(ch=='$') break;  //以$结尾，0代表不存在此节点
     bt[number]=ch;
     number++;
    }
}
void TranslateSqBitoBi(BiTree &T,char *a,int len,int loc)   //将顺序存储的二叉树转换为用二叉链表存储
{
    T=(BiTNode*)malloc(sizeof(BiTNode));
    if(loc>=len||a[loc]=='0'){T=NULL; return;}
    T->data=a[loc];
    TranslateSqBitoBi(T->lchild,a,len,2*loc+1);   //下标从0开始
    TranslateSqBitoBi(T->rchild,a,len,2*(loc+1));
}
void TreestoForest(queue <BiTree> trees,BiTree &root)   //树转换为森林，树都以孩子-兄弟存储
{
    root=trees.front();
    trees.pop();
    while(!trees.empty())
    {
        root->rchild=trees.front();
        trees.pop();
    }
}
void ForesttoTrees(BiTree root,queue <BiTree> &trees)
{
    BiTree temp=root;
    while(temp)
    {
        trees.push(temp);
        temp=temp->rchild;
    }
}
void InOrderTraverse2(BiTree T)   //非递归方式实现二叉树的中序遍历
{
    cout<<"中序遍历：";
    stack <BiTNode*> S;
    BiTNode* p=T;
    while(p||!S.empty())
    {
        if(p){
            S.push(p);
            p=p->lchild;
        }
        else {
            p=S.top();
            cout<<p->data;
            S.pop();
            p=p->rchild;
        }
    }
    cout<<endl;
}
void PostOrderTraverse2(BiTree T)   //非递归方式实现二叉树的后序遍历
{
    cout<<"后序遍历：";
    stack <BiTNode*> S;
    BiTNode* cur=T;
    BiTNode* last=NULL;
    while(cur||!S.empty())
    {
        while(cur!=NULL)
        {
            S.push(cur);
            cur=cur->lchild;
        }
        if(S.top()->rchild==NULL||S.top()->rchild==last)   //若右子树不存在或右子树已经遍历完成，则输出栈顶结点
        {
            cout<<S.top()->data;
            last=S.top();
            S.pop();
            cur=NULL;
        }
        else cur=S.top()->rchild;
    }
    cout<<endl;
}
void PreOrderTraverse2(BiTree T)   //非递归方式实现二叉树的前序遍历
{
    cout<<"前序遍历：";
    stack <BiTNode*> S;
    BiTNode* p=T;
    while(p||!S.empty())
    {
        while(p!=NULL)
        {
            cout<<p->data;
            S.push(p);
            p=p->lchild;
        }
        if(!S.empty())
        {
            p=S.top();
            S.pop();
            p=p->rchild;
        }
    }
    cout<<endl;
}
void print(BiTree T)   //输出二叉树的广义表形式
{
    if(T==NULL)
    return;
    cout<<T->data;
    if(T->lchild){cout<<"("; print(T->lchild);}
    if(!T->lchild &&T->rchild) cout<<"(";
    if(T->rchild){cout<<","; print(T->rchild); cout<<")";}
    if(T->lchild &&!T->rchild) cout<<")";
    return;
}
void InOrderTraverse(BiTree T)   //递归方式实现二叉树的中序遍历
{
    if(T)
    {
        InOrderTraverse(T->lchild);
        cout<<T->data;
        InOrderTraverse(T->rchild);
    }
}
void PreOrderTraverse(BiTree T)   //递归方式实现二叉树的先序遍历
{
    if(T)
    {
        cout<<T->data;
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}
void PostOrderTraverse(BiTree T)   //递归方式实现二叉树的后序遍历
{
    if(T)
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        cout<<T->data;
    }
}
void LevelOrderTraverse(BiTree T)   //实现二叉树的层次遍历，也称广度优先遍历
{
    cout<<"层次遍历：";
    queue <BiTNode*> Q;
    Q.push(T);
    while(!Q.empty())
    {
        BiTNode* temp=Q.front();
        cout<<temp->data;
        Q.pop();
        if(temp->lchild)
            Q.push(temp->lchild);
        if(temp->rchild)
            Q.push(temp->rchild);
    }
    cout<<endl;
}
int Leaf(BiTree T)   //求二叉树的叶子节点数
{
    if(T==NULL)
        return 0;
    else
    if(T->lchild==NULL && T->rchild==NULL)
    return 1;
    else
    return Leaf(T->lchild) + Leaf(T->rchild);
}
int Height(BiTree T)   //求二叉树的树高
{
    if(T==NULL)
        return 0;
    else{
        int hl,hr;
        hl=Height(T->lchild);
        hr=Height(T->rchild);
        return 1+(hl>hr?hl:hr);
    }
}
void FindAncestor(BiTree T,BiTNode* p)   //输出该节点的所有祖先
{
    int tag=0;   //默认没有找到目标结点
    stack <BiTNode*> S;
    BiTNode* cur=T;
    BiTNode* last=NULL;
    while(cur||!S.empty())
    {
        while(cur!=NULL)
        {
            S.push(cur);
            cur=cur->lchild;
        }
        if(S.top()->rchild==NULL||S.top()->rchild==last)   //若右子树不存在或右子树已经遍历完成，则输出栈顶结点
        {
            if(S.top()==p)
            {
                tag=1;
                break;
            }
            last=S.top();
            S.pop();
            cur=NULL;
        }
        else cur=S.top()->rchild;
    }
    if(tag==1)
    {
    while(S.size()>1)
    {
        cout<<S.top()->data<<"<-";
        S.pop();
    }
    cout<<S.top()->data;
    }
    else cout<<"不存在该节点";
    cout<<endl;
}
void FindDescendant(BiTree T,BiTNode* p)   //按广义表形式输出该节点的所有子孙
{
    print(p);
    cout<<endl;
}
BiTNode* FindSibling(BiTree T,BiTNode* p)   //返回兄弟节点的指针
{
    int tag=0;   //默认没有找到目标节点
    queue <BiTNode*> Q;
    BiTNode* temp=NULL;
    Q.push(T);
    while(!Q.empty())
    {
        temp=Q.front();
        if(temp->lchild==p||temp->rchild==p)
        {
            if(temp->lchild==p)   //左孩子是目标节点tag=1，否则为2
                tag=1;
            else tag=2;
            break;
        }
        Q.pop();
        if(temp->lchild)
            Q.push(temp->lchild);
        if(temp->rchild)
            Q.push(temp->rchild);
    }
    if(tag==0)
    {
        cout<<"不存在该节点";
        return NULL;
    }
    else {
        if(tag==1)
            return temp->rchild;
        else return temp->lchild;
    }
    cout<<endl;
}
BiTNode* FindParent(BiTree T,BiTNode* p)
{
    queue <BiTNode*> Q;
    Q.push(T);
    while(!Q.empty())
    {
        BiTNode* temp=Q.front();
        if(p==temp->lchild||p==temp->rchild)
            return temp;
        Q.pop();
        if(temp->lchild)
            Q.push(temp->lchild);
        if(temp->rchild)
            Q.push(temp->rchild);
    }
}
void FindCousin(BiTree T,BiTNode* p)   //输出该节点的堂兄弟
{
    BiTNode* parent=FindParent(T,p);
    BiTNode* uncle=FindSibling(T,parent);
    if(uncle->lchild)
        cout<<uncle->lchild->data;
    if(uncle->rchild)
        cout<<uncle->rchild->data;
    cout<<endl;
}
void menu()
{
    //按1顺序存储，按2二叉链存储，按3接受类广义表输入
    cout<<"按1顺序存储，按2二叉链存储，按3接受类广义表输入"<<endl;
    cout<<"请输入：";
    int button;
    cin>>button;
    if(button==2)
    {
        getchar();
        BiTree T;
        CreateBiTree(T);
        BiTree p=T->lchild->lchild->lchild;
        cout<<"树高是："<<Height(T)<<endl;
        cout<<"叶子节点数是："<<Leaf(T)<<endl;
        cout<<"递归中序遍历：";
        InOrderTraverse(T);
        cout<<endl;
        cout<<"递归先序遍历：";
        PreOrderTraverse(T);
        cout<<endl;
        cout<<"递归后序遍历：";
        PostOrderTraverse(T);
        cout<<endl;
        InOrderTraverse2(T);
        PreOrderTraverse2(T);
        PostOrderTraverse2(T);
        LevelOrderTraverse(T);
        cout<<"e的祖先为：";
        FindAncestor(T,p);
        cout<<"e的堂兄弟为：";
        FindCousin(T,p);
        cout<<"d的兄弟为：";
        cout<<FindSibling(T,T->lchild->lchild)->data<<endl;
        cout<<"a的子孙为：";
        FindDescendant(T,T);
    }
    if(button==1)
    {
        getchar();
        BiTree T;
        CreateSqBiTree(bt);
        TranslateSqBitoBi(T,bt,number,0);
        cout<<"树高是："<<Height(T)<<endl;
        cout<<"叶子节点数是："<<Leaf(T)<<endl;
        cout<<"递归中序遍历：";
        InOrderTraverse(T);
        cout<<endl;
        cout<<"递归先序遍历：";
        PreOrderTraverse(T);
        cout<<endl;
        cout<<"递归后序遍历：";
        PostOrderTraverse(T);
        cout<<endl;
        InOrderTraverse2(T);
        PreOrderTraverse2(T);
        PostOrderTraverse2(T);
        LevelOrderTraverse(T);
    }
    if(button==3)
    {
        getchar();
        char str[100];
        gets(str);
        BiTree T=CreateBiTree_List(str);
        cout<<"树高是："<<Height(T)<<endl;
        cout<<"叶子节点数是："<<Leaf(T)<<endl;
        cout<<"递归中序遍历：";
        InOrderTraverse(T);
        cout<<endl;
        cout<<"递归先序遍历：";
        PreOrderTraverse(T);
        cout<<endl;
        cout<<"递归后序遍历：";
        PostOrderTraverse(T);
        cout<<endl;
        InOrderTraverse2(T);
        PreOrderTraverse2(T);
        PostOrderTraverse2(T);
        LevelOrderTraverse(T);
    }
    menu();
}
int main()
{
//   CreateBiTree(T);
//    cout<<Height(T)<<endl;
//    cout<<Leaf(T)<<endl;
//    BiTNode*p=T->lchild->lchild->lchild;
//    FindAncestor(T,p);
//    InOrderTraverse(T);
//    PreOrderTraverse(T);
//    PostOrderTraverse(T);
//    InOrderTraverse2(T);
//    PreOrderTraverse2(T);
//    PostOrderTraverse2(T);
//    LevelOrderTraverse(T);
//    char str[100];
//    gets(str);
//    BiTree T=CreateBiTree_List(str);
//    cout<<Leaf(T)<<endl;
//    PreOrderTraverse2(T);
//    CreateSqBiTree(bt);
//    TranslateSqBitoBi(T,bt,number,0);
//    LevelOrderTraverse(T);
    menu();
    return 0;
}
//测试样例
//abde   fg   c h i  //
//A(B(C,F),G(H,I))
//abcdf0he00g0i$
