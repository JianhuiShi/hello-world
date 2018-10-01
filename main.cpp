using namespace std;

#include "CodingProject-2.h"

double counter = 0;    //计算函数调用次数

ostream &operator <<(ostream &os, RBNode & rbnode)   //重载<<
{
    return os<<rbnode.m_key<<endl;
}

RBNode::RBNode(double key): m_key(key)   //构造函数，初始化变量
{
    left = nullptr;
    right = nullptr;
    p = nullptr;
    m_color = RED;
}

RBTree::RBTree(): node_num(0)   //构造函数，初始化变量
{
    NIL = new RBNode(0);
    NIL->m_color = BLACK;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->p = NIL;
    root = NIL;
}

RBTree::~RBTree()   //析构函数，释放new分配的堆上的空间
{
    Delete_rbtree(this->root);
    delete this->NIL;
}

void RBTree::Delete_rbtree(RBNode* rbnode)  //辅助删除红黑树用的函数，在析构函数内会被调用
{
    if(rbnode == this->NIL)
        return;
    Delete_rbtree(rbnode->getleft());
    Delete_rbtree(rbnode->getright());
    delete rbnode;
    return;
}

void RBTree::Left_rotate(RBNode *x)  //P177
{
    RBNode *y = x->right;
    x->right = y->left;
    if(y->left != this->NIL)
        y->left->p = x;
    y->p = x->p;
    if(x->p == this->NIL)
        this->root = y;
    else if(x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->left = x;
    x->p = y;
}

void RBTree::Right_rotate(RBNode *x)  //P177(与左旋对称)
{
    RBNode *y = x->left;
    x->left = y->right;
    if(y->right != this->NIL)
        y->right->p = x;
    y->p = x->p;
    if(x->p == this->NIL)
        this->root = y;
    else if(x == x->p->right)
        x->p->right = y;
    else
        x->p->left = y;
    y->right = x;
    x->p = y;
}

void RBTree::Insert_fixup(RBNode *z)    //P178
{
    while(z->p->m_color == RED)
        if(z->p == z->p->p->left)
        {
            RBNode *y = z->p->p->right;
            if(y->m_color == RED)
            {
                z->p->m_color = BLACK;
                y->m_color = BLACK;
                z->p->p->m_color = RED;
                z = z->p->p;
            }
            else
            {
                if(z == z->p->right)
                {
                    z = z->p;
                    this->Left_rotate(z);
                }
                z->p->m_color = BLACK;
                z->p->p->m_color = RED;
                this->Right_rotate(z->p->p);
            }
        }
        else
        {
            RBNode *y = z->p->p->left;
            if(y->m_color == RED)
            {
                z->p->m_color = BLACK;
                y->m_color = BLACK;
                z->p->p->m_color = RED;
                z = z->p->p;
            }
            else
            {
                if(z == z->p->left)
                {
                    z = z->p;
                    this->Right_rotate(z);
                }
                z->p->m_color = BLACK;
                z->p->p->m_color = RED;
                this->Left_rotate(z->p->p);
            }
        }
    this->root->m_color = BLACK;
}

void RBTree::Insert(RBNode *z)    //P178
{
    this->node_num += 1;
    RBNode *y = this->NIL,
            *x = this->root;
    while(x != this->NIL)
    {
        y = x;
        if(z->m_key < x->m_key)
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;
    if(y == this->NIL)
        this->root = z;
    else if(z->m_key < y->m_key)
        y->left = z;
    else
        y->right = z;
    z->left = this->NIL;
    z->right = this->NIL;
    z->m_color = RED;
    this->Insert_fixup(z);
}

void RBTree::Inorder_tree_walk(RBNode *x)    //P162
{
    if(x != this->NIL)
    {
        Inorder_tree_walk(x->left);
        cout<<*x;
        Inorder_tree_walk(x->right);
    }
}

RBNode* RBTree::Minimum(RBNode* x)    //P164
{
    while(x->left != this->NIL)
        {
            counter ++;
            x = x->left;
        }
    return x;
}

RBNode* RBTree::Maximum(RBNode* x)    //P164(与寻找最小值对称)
{
    while(x->right != this->NIL)
        {
            counter ++;
            x = x->right;
        }
    return x;
}

RBNode* RBTree::Successor(RBNode *x)    //P164
{
    if(x->right != NIL)
    {
        counter ++;
        return this->Minimum(x->right);
    }
    else
    {
        RBNode*y = x->p;
        while(y != NIL && x == y->right)
        {
            counter ++;
            x = y;
            y = y->p;
        }
        return y;
    }
}

RBNode* RBTree::Predecessor(RBNode *x)    //P164(与寻找后继结点对称)
{
    if(x->left != NIL)
        {
            counter ++;
            return this->Maximum(x->left);
        }
    else
    {
        RBNode*y = x->p;
        while(y != NIL && x == y->left)
        {
            counter ++;
            x = y;
            y = y->p;
        }
        return y;
    }
}

ostream &operator <<(ostream &os, IntNode & intnode)  //重载<<
{
    if(intnode.m_low > intnode.m_high)
        return os<<"未找到重叠区间";
    return os<<"["<<intnode.m_low<<", "<<intnode.m_high<<"]"<<endl;
}

IntNode::IntNode(const double low, const double high): m_low(low), m_high(high), m_key(low)   //构造函数，初始化变量
{
    left = nullptr;
    right = nullptr;
    p = nullptr;
    m_color = RED;
    m_max = high;
}

IntTree::IntTree(): node_num(0)   //构造函数，初始化变量
{
    NIL = new IntNode(DBL_MAX, DBL_MIN);
    NIL->m_color = BLACK;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->p = NIL;
    root = NIL;
}

IntTree::~IntTree()     //析构函数，释放new分配的堆上的空间
{
    Delete_inttree(this->root);
    delete this->NIL;
}

void IntTree::Delete_inttree(IntNode* intnode)      //辅助删除区间树用的函数，在析构函数内会被调用
{
    if(intnode == this->NIL)
        return;
    Delete_inttree(intnode->getleft());
    Delete_inttree(intnode->getright());
    delete intnode;
    return;
}

void IntTree::Left_rotate(IntNode *x)  //P177
{
    IntNode *y = x->right;
    //如图13-2，计算alpha.max,beta.max,x.high的最大值作为x.max
    double x_max = max(x->m_high, max(x->left->m_max, y->left->m_max));
    //如图13-2，y.max即原来的x.max
    y->m_max = x->m_max;
    x->m_max = x_max;
    x->right = y->left;
    if(y->left != this->NIL)
        y->left->p = x;
    y->p = x->p;
    if(x->p == this->NIL)
        this->root = y;
    else if(x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->left = x;
    x->p = y;
}

void IntTree::Right_rotate(IntNode *x)  //P177(与左旋对称)
{
    IntNode *y = x->left;
    double x_max = max(x->m_high, max(x->right->m_max, y->right->m_max));
    y->m_max = x->m_max;
    x->m_max = x_max;
    x->left = y->right;
    if(y->right != this->NIL)
        y->right->p = x;
    y->p = x->p;
    if(x->p == this->NIL)
        this->root = y;
    else if(x == x->p->right)
        x->p->right = y;
    else
        x->p->left = y;
    y->right = x;
    x->p = y;
}

void IntTree::Insert_fixup(IntNode *z)  //P178(导致树结构变化的操作在其它三个函数中，这个函数与红黑树相比无变化)
{
    while(z->p->m_color == RED)
        if(z->p == z->p->p->left)
        {
            IntNode *y = z->p->p->right;
            if(y->m_color == RED)
            {
                z->p->m_color = BLACK;
                y->m_color = BLACK;
                z->p->p->m_color = RED;
                z = z->p->p;
            }
            else
            {
                if(z == z->p->right)
                {
                    z = z->p;
                    this->Left_rotate(z);
                }
                z->p->m_color = BLACK;
                z->p->p->m_color = RED;
                this->Right_rotate(z->p->p);
            }
        }
        else
        {
            IntNode *y = z->p->p->left;
            if(y->m_color == RED)
            {
                z->p->m_color = BLACK;
                y->m_color = BLACK;
                z->p->p->m_color = RED;
                z = z->p->p;
            }
            else
            {
                if(z == z->p->left)
                {
                    z = z->p;
                    this->Right_rotate(z);
                }
                z->p->m_color = BLACK;
                z->p->p->m_color = RED;
                this->Left_rotate(z->p->p);
            }
        }
    this->root->m_color = BLACK;
}

void IntTree::Insert(IntNode *z)  //P178(导致树结构变化的操作在上面三个函数中，这个函数与红黑树相比无变化)
{
    this->node_num += 1;
    IntNode *y = this->NIL,
             *x = this->root;
    while(x != this->NIL)
    {
        //每次下降一层，计算新插入的结点对经过结点的影响
        if(x->m_max < z->m_max)
            x->m_max = z->m_max;
        y = x;
        if(z->m_key < x->m_key)
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;
    if(y == this->NIL)
        this->root = z;
    else if(z->m_key < y->m_key)
        y->left = z;
    else
        y->right = z;
    z->left = this->NIL;
    z->right = this->NIL;
    z->m_color = RED;
    this->Insert_fixup(z);
}

IntNode* IntTree::Search(const double low, const double high)  //P200(保证若存在区间重叠则一定能找到一个)
{
    decltype(this->root) x = this->root;
    while(x != this->NIL && (low > x->m_high || high < x->m_low))
    {
        if(x->left != this->NIL && x->left->m_max >= low)
            x = x->left;
        else
            x = x->right;
        counter ++;
    }
    return x;
}

double Cor(vector<double> x, vector<double> y)
{
    int n = x.size();
    double sxx = 0, sxy = 0, syy = 0, xmean = 0, ymean = 0;
    for(int k = 0; k != n; k ++)
    {
        xmean += x[k];
        ymean += y[k];
    }
    xmean /= n;
    ymean /= n;
    for(int k = 0; k != n; k ++)
    {
        sxx += x[k]*x[k];
        syy += y[k]*y[k];
        sxy += x[k]*y[k];
    }
    sxx -= n * xmean * xmean;
    syy -= n * ymean * ymean;
    sxy -= n * xmean * ymean;
    return sxy / sqrt(sxx) / sqrt(syy);
}

int main()
{
    cout<<endl;
    cout<<"-----------------------测试红黑树函数基本功能---------------------------"<<endl<<endl;
    {
        RBTree rbtree = RBTree();
        srand((int)time(NULL));
        //产生20个随机关键字做成结点插入红黑树进行测试
        for(int k = 0; k != 20; k ++)
        {
            double key = Min + (Max - Min) * rand() / double(RAND_MAX);     //产生Min - Max之间的随机数
            RBNode *rbnode = new RBNode(key);
            rbtree.Insert(rbnode);
        }
        cout<<"中序遍历:"<<endl;
        rbtree.Inorder_tree_walk(rbtree.root);
        RBNode *p = nullptr;
        p = rbtree.Minimum(rbtree.root);
        cout<<endl<<"最小值:"<<p->getkey()<<endl;
        cout<<"从最小值结点开始依次取后继遍历:"<<endl;
        for(int i = 0; i != rbtree.node_num; i ++)
        {
            cout<<p->getkey()<<endl;
            p = rbtree.Successor(p);
        }
        p = rbtree.Maximum(rbtree.root);
        cout<<endl<<"最大值:"<<p->getkey()<<endl;
        cout<<"从最大值结点开始依次取前驱遍历:"<<endl;
        for(int i = 0; i != 20; i ++)
        {
            cout<<p->getkey()<<endl;
            p = rbtree.Predecessor(p);
        }
        cout<<endl;
    }

    cout<<"-----------------------测试区间树函数基本功能---------------------------"<<endl<<endl;
    {
        IntTree inttree;
        srand((int)time(NULL));
        //产生1000个随机关键字做成区间插入区间树进行测试
        for(int k = 0; k != 1000; k ++)
        {
            double key = Min + (Max - Min) * rand() / double(RAND_MAX);     //产生Min - Max之间的随机数
            IntNode *intnode = new IntNode(key, 1.1*key);   //生成随机区间
            inttree.Insert(intnode);
        }
        cout<<"下面寻找与[70,75]重叠的区间:"<<endl<<*inttree.Search(70,75)<<endl;
    }

    cout<<"-----------------------下面测试函数的性能和时间复杂度---------------------------"<<endl<<endl;
    {  //Minimum
        cout<<endl;
        vector<double> n_array;
        vector<double> count_array;
        //结点数量级从N1到N2，每个数量级测试batchsize次取平均值
        for(int n = N1; n <= N2; n *= 10)
        {
            counter = 0;
            //计算Batchsize次调用函数关键部分执行次数对数的均值
            for(int k = 0; k != Batchsize; k ++)
            {
                RBTree rbtree = RBTree();
                //随机生成结点构造红黑树
                for(int i = 0; i != n; i ++) //随机生成结点构造红黑树
                {
                    //产生Min - Max之间的随机数
                    double key = Min + (Max - Min) * rand() / double(RAND_MAX);
                    RBNode *rbnode = new RBNode(key);
                    rbtree.Insert(rbnode);
                }
                rbtree.Minimum(rbtree.root);
            }
            n_array.push_back(log2(n));
            count_array.push_back(counter/Batchsize);
        }
        double cor = Cor(n_array, count_array);
        //计算相关系数检验线性相关性，若接近1则接受线性相关假设，否则拒绝
        cout<<"logn与执行次数相关系数为:"<<cor<<endl;
        if(1 - cor < 0.01)
            cout<<"接受Minimun函数时间复杂度为logn数量级的假设"<<endl;
        else
            cout<<"拒绝Minimum函数时间复杂度不是logn数量级的假设"<<endl;
    }
    {  //Maximum
        cout<<endl;
        vector<double> n_array;
        vector<double> count_array;
        //结点数量级从N1到N2，每个数量级测试batchsize次取平均值
        for(int n = N1; n <= N2; n *= 10)
        {
            counter = 0;
            //计算Batchsize次调用函数关键部分执行次数对数的均值
            for(int k = 0; k != Batchsize; k ++)
            {
                RBTree rbtree = RBTree();
                //随机生成结点构造红黑树
                for(int i = 0; i != n; i ++)
                {
                    //产生Min - Max之间的随机数
                    double key = Min + (Max - Min) * rand() / double(RAND_MAX);
                    RBNode *rbnode = new RBNode(key);
                    rbtree.Insert(rbnode);
                }
                rbtree.Maximum(rbtree.root);
            }
            n_array.push_back(log2(n));
            count_array.push_back(counter/Batchsize);
        }
        double cor = Cor(n_array, count_array);
        //计算相关系数检验线性相关性，若接近1则接受线性相关假设，否则拒绝
        cout<<"logn与执行次数相关系数为:"<<cor<<endl;
        if(1 - cor < 0.01)
            cout<<"接受Maximum函数时间复杂度为logn数量级的假设"<<endl;
        else
            cout<<"拒绝Maximum函数时间复杂度不是logn数量级的假设"<<endl;
    }
    { //Successor
        cout<<endl;
        vector<double> n_array;
        vector<double> count_array;
        //结点数量级从N1到N2，每个数量级测试batchsize次取平均值
        for(int n = N1; n <= N2; n *= 10)
        {
            counter = 0;
            //计算Batchsize次调用函数关键部分执行次数对数的均值
            for(int k = 0; k != Batchsize; k ++)
            {
                RBTree rbtree = RBTree();
                //随机生成结点构造红黑树
                for(int i = 0; i != n; i ++)
                {
                    //产生Min - Max之间的随机数
                    double key = Min + (Max - Min) * rand() / double(RAND_MAX);
                    RBNode *rbnode = new RBNode(key);
                    rbtree.Insert(rbnode);
                }
                rbtree.Successor(rbtree.root);
            }
            n_array.push_back(log2(n));
            count_array.push_back(counter/Batchsize);
        }
        double cor = Cor(n_array, count_array);
        //计算相关系数检验线性相关性，若接近1则接受线性相关假设，否则拒绝
        cout<<"logn与执行次数相关系数为:"<<cor<<endl;
        if(1 - cor < 0.01)
            cout<<"接受Successor函数时间复杂度为logn数量级的假设"<<endl;
        else
            cout<<"拒绝Successor函数时间复杂度不是logn数量级的假设"<<endl;
    }
    { //Predecessor
        cout<<endl;
        vector<double> n_array;
        vector<double> count_array;
        //结点数量级从N1到N2，每个数量级测试batchsize次取平均值
        for(int n = N1; n <= N2; n *= 10)
        {
            counter = 0;
            //计算Batchsize次调用函数关键部分执行次数对数的均值
            for(int k = 0; k != Batchsize; k ++)
            {
                RBTree rbtree = RBTree();
                //随机生成结点构造红黑树
                for(int i = 0; i != n; i ++)
                {
                    //产生Min - Max之间的随机数
                    double key = Min + (Max - Min) * rand() / double(RAND_MAX);
                    RBNode *rbnode = new RBNode(key);
                    rbtree.Insert(rbnode);
                }
                rbtree.Predecessor(rbtree.root);
            }
            n_array.push_back(log2(n));
            count_array.push_back(counter / Batchsize);
        }
        double cor = Cor(n_array, count_array);
        //计算相关系数检验线性相关性，若接近1则接受线性相关假设，否则拒绝
        cout<<"logn与执行次数相关系数为:"<<cor<<endl;
        if(1 - cor < 0.01)
            cout<<"接受Predecessor函数时间复杂度为logn数量级的假设"<<endl;
        else
            cout<<"拒绝Predecessor函数时间复杂度不是logn数量级的假设"<<endl;
    }
    {  //Search
        cout<<endl;
        vector<double> n_array;
        vector<double> count_array;
        //结点数量级从N1到N2，每个数量级测试batchsize次取平均值
        for(int n = N1; n <= N2; n *= 10)
        {
            counter = 0;
            //计算Batchsize次调用函数关键部分执行次数对数的均值
            for(int k = 0; k != Batchsize; k ++)
            {
                IntTree inttree = IntTree();
                //随机生成区间树
                for(int i = 0; i != n; i ++)
                {
                    //产生0 - n * Max之间的随机数(区间规模应随着问题的规模相应变大)
                    double key = 0 + (n * Max - 0) * rand() / double(RAND_MAX);
                     //生成随机区间
                    IntNode *intnode = new IntNode(key, 1.1*key);
                    inttree.Insert(intnode);
                }
                inttree.Search(70, 75);
            }
            n_array.push_back(log2(n));
            count_array.push_back(counter/Batchsize);
        }
        double cor = Cor(n_array, count_array);
        //计算相关系数检验线性相关性，若接近1则接受线性相关假设，否则拒绝
        cout<<"logn与执行次数相关系数为:"<<cor<<endl;
        if(1 - cor < 0.01)
            cout<<"接受Search函数时间复杂度为logn数量级的假设"<<endl;
        else
            cout<<"拒绝Search函数时间复杂度不是logn数量级的假设"<<endl;
    }
}
