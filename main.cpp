using namespace std;

#include "CodingProject-2.h"

double counter = 0;    //���㺯�����ô���

ostream &operator <<(ostream &os, RBNode & rbnode)   //����<<
{
    return os<<rbnode.m_key<<endl;
}

RBNode::RBNode(double key): m_key(key)   //���캯������ʼ������
{
    left = nullptr;
    right = nullptr;
    p = nullptr;
    m_color = RED;
}

RBTree::RBTree(): node_num(0)   //���캯������ʼ������
{
    NIL = new RBNode(0);
    NIL->m_color = BLACK;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->p = NIL;
    root = NIL;
}

RBTree::~RBTree()   //�����������ͷ�new����Ķ��ϵĿռ�
{
    Delete_rbtree(this->root);
    delete this->NIL;
}

void RBTree::Delete_rbtree(RBNode* rbnode)  //����ɾ��������õĺ����������������ڻᱻ����
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

void RBTree::Right_rotate(RBNode *x)  //P177(�������Գ�)
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

RBNode* RBTree::Maximum(RBNode* x)    //P164(��Ѱ����Сֵ�Գ�)
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

RBNode* RBTree::Predecessor(RBNode *x)    //P164(��Ѱ�Һ�̽��Գ�)
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

ostream &operator <<(ostream &os, IntNode & intnode)  //����<<
{
    if(intnode.m_low > intnode.m_high)
        return os<<"δ�ҵ��ص�����";
    return os<<"["<<intnode.m_low<<", "<<intnode.m_high<<"]"<<endl;
}

IntNode::IntNode(const double low, const double high): m_low(low), m_high(high), m_key(low)   //���캯������ʼ������
{
    left = nullptr;
    right = nullptr;
    p = nullptr;
    m_color = RED;
    m_max = high;
}

IntTree::IntTree(): node_num(0)   //���캯������ʼ������
{
    NIL = new IntNode(DBL_MAX, DBL_MIN);
    NIL->m_color = BLACK;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->p = NIL;
    root = NIL;
}

IntTree::~IntTree()     //�����������ͷ�new����Ķ��ϵĿռ�
{
    Delete_inttree(this->root);
    delete this->NIL;
}

void IntTree::Delete_inttree(IntNode* intnode)      //����ɾ���������õĺ����������������ڻᱻ����
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
    //��ͼ13-2������alpha.max,beta.max,x.high�����ֵ��Ϊx.max
    double x_max = max(x->m_high, max(x->left->m_max, y->left->m_max));
    //��ͼ13-2��y.max��ԭ����x.max
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

void IntTree::Right_rotate(IntNode *x)  //P177(�������Գ�)
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

void IntTree::Insert_fixup(IntNode *z)  //P178(�������ṹ�仯�Ĳ������������������У������������������ޱ仯)
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

void IntTree::Insert(IntNode *z)  //P178(�������ṹ�仯�Ĳ������������������У������������������ޱ仯)
{
    this->node_num += 1;
    IntNode *y = this->NIL,
             *x = this->root;
    while(x != this->NIL)
    {
        //ÿ���½�һ�㣬�����²���Ľ��Ծ�������Ӱ��
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

IntNode* IntTree::Search(const double low, const double high)  //P200(��֤�����������ص���һ�����ҵ�һ��)
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
    cout<<"-----------------------���Ժ����������������---------------------------"<<endl<<endl;
    {
        RBTree rbtree = RBTree();
        srand((int)time(NULL));
        //����20������ؼ������ɽ������������в���
        for(int k = 0; k != 20; k ++)
        {
            double key = Min + (Max - Min) * rand() / double(RAND_MAX);     //����Min - Max֮��������
            RBNode *rbnode = new RBNode(key);
            rbtree.Insert(rbnode);
        }
        cout<<"�������:"<<endl;
        rbtree.Inorder_tree_walk(rbtree.root);
        RBNode *p = nullptr;
        p = rbtree.Minimum(rbtree.root);
        cout<<endl<<"��Сֵ:"<<p->getkey()<<endl;
        cout<<"����Сֵ��㿪ʼ����ȡ��̱���:"<<endl;
        for(int i = 0; i != rbtree.node_num; i ++)
        {
            cout<<p->getkey()<<endl;
            p = rbtree.Successor(p);
        }
        p = rbtree.Maximum(rbtree.root);
        cout<<endl<<"���ֵ:"<<p->getkey()<<endl;
        cout<<"�����ֵ��㿪ʼ����ȡǰ������:"<<endl;
        for(int i = 0; i != 20; i ++)
        {
            cout<<p->getkey()<<endl;
            p = rbtree.Predecessor(p);
        }
        cout<<endl;
    }

    cout<<"-----------------------����������������������---------------------------"<<endl<<endl;
    {
        IntTree inttree;
        srand((int)time(NULL));
        //����1000������ؼ�����������������������в���
        for(int k = 0; k != 1000; k ++)
        {
            double key = Min + (Max - Min) * rand() / double(RAND_MAX);     //����Min - Max֮��������
            IntNode *intnode = new IntNode(key, 1.1*key);   //�����������
            inttree.Insert(intnode);
        }
        cout<<"����Ѱ����[70,75]�ص�������:"<<endl<<*inttree.Search(70,75)<<endl;
    }

    cout<<"-----------------------������Ժ��������ܺ�ʱ�临�Ӷ�---------------------------"<<endl<<endl;
    {  //Minimum
        cout<<endl;
        vector<double> n_array;
        vector<double> count_array;
        //�����������N1��N2��ÿ������������batchsize��ȡƽ��ֵ
        for(int n = N1; n <= N2; n *= 10)
        {
            counter = 0;
            //����Batchsize�ε��ú����ؼ�����ִ�д��������ľ�ֵ
            for(int k = 0; k != Batchsize; k ++)
            {
                RBTree rbtree = RBTree();
                //������ɽ�㹹������
                for(int i = 0; i != n; i ++) //������ɽ�㹹������
                {
                    //����Min - Max֮��������
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
        //�������ϵ��������������ԣ����ӽ�1�����������ؼ��裬����ܾ�
        cout<<"logn��ִ�д������ϵ��Ϊ:"<<cor<<endl;
        if(1 - cor < 0.01)
            cout<<"����Minimun����ʱ�临�Ӷ�Ϊlogn�������ļ���"<<endl;
        else
            cout<<"�ܾ�Minimum����ʱ�临�ӶȲ���logn�������ļ���"<<endl;
    }
    {  //Maximum
        cout<<endl;
        vector<double> n_array;
        vector<double> count_array;
        //�����������N1��N2��ÿ������������batchsize��ȡƽ��ֵ
        for(int n = N1; n <= N2; n *= 10)
        {
            counter = 0;
            //����Batchsize�ε��ú����ؼ�����ִ�д��������ľ�ֵ
            for(int k = 0; k != Batchsize; k ++)
            {
                RBTree rbtree = RBTree();
                //������ɽ�㹹������
                for(int i = 0; i != n; i ++)
                {
                    //����Min - Max֮��������
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
        //�������ϵ��������������ԣ����ӽ�1�����������ؼ��裬����ܾ�
        cout<<"logn��ִ�д������ϵ��Ϊ:"<<cor<<endl;
        if(1 - cor < 0.01)
            cout<<"����Maximum����ʱ�临�Ӷ�Ϊlogn�������ļ���"<<endl;
        else
            cout<<"�ܾ�Maximum����ʱ�临�ӶȲ���logn�������ļ���"<<endl;
    }
    { //Successor
        cout<<endl;
        vector<double> n_array;
        vector<double> count_array;
        //�����������N1��N2��ÿ������������batchsize��ȡƽ��ֵ
        for(int n = N1; n <= N2; n *= 10)
        {
            counter = 0;
            //����Batchsize�ε��ú����ؼ�����ִ�д��������ľ�ֵ
            for(int k = 0; k != Batchsize; k ++)
            {
                RBTree rbtree = RBTree();
                //������ɽ�㹹������
                for(int i = 0; i != n; i ++)
                {
                    //����Min - Max֮��������
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
        //�������ϵ��������������ԣ����ӽ�1�����������ؼ��裬����ܾ�
        cout<<"logn��ִ�д������ϵ��Ϊ:"<<cor<<endl;
        if(1 - cor < 0.01)
            cout<<"����Successor����ʱ�临�Ӷ�Ϊlogn�������ļ���"<<endl;
        else
            cout<<"�ܾ�Successor����ʱ�临�ӶȲ���logn�������ļ���"<<endl;
    }
    { //Predecessor
        cout<<endl;
        vector<double> n_array;
        vector<double> count_array;
        //�����������N1��N2��ÿ������������batchsize��ȡƽ��ֵ
        for(int n = N1; n <= N2; n *= 10)
        {
            counter = 0;
            //����Batchsize�ε��ú����ؼ�����ִ�д��������ľ�ֵ
            for(int k = 0; k != Batchsize; k ++)
            {
                RBTree rbtree = RBTree();
                //������ɽ�㹹������
                for(int i = 0; i != n; i ++)
                {
                    //����Min - Max֮��������
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
        //�������ϵ��������������ԣ����ӽ�1�����������ؼ��裬����ܾ�
        cout<<"logn��ִ�д������ϵ��Ϊ:"<<cor<<endl;
        if(1 - cor < 0.01)
            cout<<"����Predecessor����ʱ�临�Ӷ�Ϊlogn�������ļ���"<<endl;
        else
            cout<<"�ܾ�Predecessor����ʱ�临�ӶȲ���logn�������ļ���"<<endl;
    }
    {  //Search
        cout<<endl;
        vector<double> n_array;
        vector<double> count_array;
        //�����������N1��N2��ÿ������������batchsize��ȡƽ��ֵ
        for(int n = N1; n <= N2; n *= 10)
        {
            counter = 0;
            //����Batchsize�ε��ú����ؼ�����ִ�д��������ľ�ֵ
            for(int k = 0; k != Batchsize; k ++)
            {
                IntTree inttree = IntTree();
                //�������������
                for(int i = 0; i != n; i ++)
                {
                    //����0 - n * Max֮��������(�����ģӦ��������Ĺ�ģ��Ӧ���)
                    double key = 0 + (n * Max - 0) * rand() / double(RAND_MAX);
                     //�����������
                    IntNode *intnode = new IntNode(key, 1.1*key);
                    inttree.Insert(intnode);
                }
                inttree.Search(70, 75);
            }
            n_array.push_back(log2(n));
            count_array.push_back(counter/Batchsize);
        }
        double cor = Cor(n_array, count_array);
        //�������ϵ��������������ԣ����ӽ�1�����������ؼ��裬����ܾ�
        cout<<"logn��ִ�д������ϵ��Ϊ:"<<cor<<endl;
        if(1 - cor < 0.01)
            cout<<"����Search����ʱ�临�Ӷ�Ϊlogn�������ļ���"<<endl;
        else
            cout<<"�ܾ�Search����ʱ�临�ӶȲ���logn�������ļ���"<<endl;
    }
}
