#include <iostream>
#include <vector>
#include <algorithm>
#include<cmath>
#include <string>
//kd树是二叉树的一种，体会函数中迭代方法的应用
//////author:tobking time:2018.5.19
using namespace std;
int raw_data[8][2]={{1,4},{3,7},{5,4},{9,6},{4,8},{6,2},{8,1},{3,9}};
class kdtree{
public:
    vector<double> data;
    kdtree* parent;
    kdtree* leftChild;
    kdtree* rightChild;
    //构造函数
    kdtree(){parent=leftChild=rightChild= nullptr;}
    //判断是否为空
    bool isEmppty()
    {
        return data.empty();
    }
    //判断是否为单叶节点，即无child
    bool isLeaf()
    {
        return (!data.empty())&&rightChild== nullptr&&leftChild== nullptr;
    }
    //判断是否为根节点
    bool isRoot(){
        return parent== nullptr&&(!isEmppty());
    }
    //判断是左节点还是右节点
    int left_or_right(){
        if (parent->leftChild->data==data)
            return 1;
        else
            return 0;

    }
};

//模板，转置
//template <typename T>
//vector<vector<T>> TransPose(vector<vector<T>> Matrix)
//{
//    unsigned long row=Matrix.size();
//    unsigned long col=Matrix[0].size();
//    vector<vector<T>> Trans(col,vector<T>(row,0));
//    for (int i=0;i<col;i++)
//    {
//        for(int j=0;j<row;j++)
//        {
//            Trans[i][j]=Matrix[j][i];
//        }
//    }
//    return Trans;
//}
//寻找中位数
template <typename T>
T findMiddleValue(vector<vector<T>> Matrix,int axis)
{
    unsigned long row=Matrix.size();
    //unsigned long col=Matrix[0].size();
    vector<T> values;
    for(int i=0;i<row;i++)
    {
        values.push_back(Matrix[i][axis]);
    }
    sort(values.begin(),values.end());
    auto pos=values.size()/2;
    return values[pos];
}
//构造kd树
template <typename T>
void buildTree(kdtree* tree,vector<vector<T>> data, int depth)
{
    //样本数量
    unsigned long sampleNum=data.size();
    //终止条件
    if (sampleNum==0)
    {
        return;
    }
    if (sampleNum==1)
    {
        tree->data=data[0];
    }
    //样本维度
    int k=data[0].size();
    //选择切分维度
    int splitD=depth%k;
    //选择切分值
   auto splitVaule=findMiddleValue(data,splitD);
   vector<vector<T>> subset1;
   vector<vector<T>> subset2;
   //若某一维中位数存在多个样本中，如何处理
    int flage=0;//设置一个标志位，只执行一次
   for (int i=0;i<sampleNum;i++)
   {
       if (data[i][splitD]<splitVaule)
           subset1.push_back(data[i]);
       if (data[i][splitD]>splitVaule)
           subset2.push_back(data[i]);
       if(flage==0&&data[i][splitD]==splitVaule)
       {
           tree->data=data[i];
           flage+=1;
       }

   }
   //左右节点递归调用buildtree
   if (!subset1.empty())//若不为空
   {
       tree->leftChild=new kdtree;//构建类对象，调用构造函数
       tree->leftChild->parent=tree;//将指针付给指针
       buildTree(tree->leftChild,subset1,depth+1);
   }
   if(!subset2.empty())
   {
       tree->rightChild=new kdtree;
       tree->rightChild->parent=tree;
       buildTree(tree->rightChild,subset2,depth+1);
   }

}

//打印kd树
void printKdtree(kdtree* tree,int depth)
{
    for (int i = 0; i <depth ; ++i) {
        cout<<'\t';
    }
    //for (vector<double>::size_type j=0;j<tree->data.size();j++)
    for (auto j:tree->data)// new usage
    {
        cout<<j<<',';
    }
    cout<<endl;
    //若为叶子节点
    if(tree->rightChild== nullptr&&tree->leftChild== nullptr)
        return;
    else//若为根节点，迭代打印左右节点
    {
        if(tree->leftChild!= nullptr)
        {
            cout<<"leftChild:";
            printKdtree(tree->leftChild,depth+1);
        }
        if(tree->rightChild!= nullptr)
        {
            cout<<"rightChild:";
            printKdtree(tree->rightChild,depth+1);
        }
        //cout<<endl;
    }

}

int main()
{
    vector<vector<double>> train(8,vector<double>(2));//使用vector构造二维数组，声明空间
    cout<<"start"<<endl;
    for (int i = 0; i <8 ; ++i) {
        //vector<double> temp;
        for (int j = 0; j <2; ++j) {
            //cout<<"raw_data:"<<raw_data[i][j]
            //cout<<"j:"<<j;
            //temp.push_back(raw_data[i][j]);
            train[i][j]=raw_data[i][j];
        }
        //train[i]=temp;
    }
    auto* tree=new kdtree;
    buildTree(tree,train,0);
    printKdtree(tree,0);
    return 0;
}