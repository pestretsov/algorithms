#include "rbtree.hpp"

RedBlackNode::~RedBlackNode()
{
    delete left_;
    delete right_;
}

RedBlackTree::RedBlackTree() : sz_(0) { root_ = nullptr; }

RedBlackTree::RedBlackTree(std::initializer_list<int> ls) : sz_(0)
{
    root_ = nullptr;
    for (auto i : ls)
        insert(i);
}

RedBlackNode * RedBlackTree::root() { return root_; }


RedBlackNode * RedBlackTree::min(RedBlackNode * pNode)
{
    while (pNode->left_)
        pNode = pNode->left_;
    return pNode;
}

void RedBlackTree::left_rotate(RedBlackNode * pNode)
{
    // init mNode
    RedBlackNode * mNode = pNode->right_;
    pNode->right_ = mNode->left_;
    if (mNode->left_)
        mNode->left_->parent_ = pNode;
    mNode->parent_ = pNode->parent_;
    // set mNode parent
    if (!pNode->parent_)
        root_ = mNode;
    else if (pNode->parent_->left_ == pNode)
        pNode->parent_->left_ = mNode;
    else
        pNode->parent_->right_ = mNode;
    mNode->left_ = pNode;
    // set pNode parent
    pNode->parent_ = mNode;
}

void RedBlackTree::right_rotate(RedBlackNode * pNode)
{
    // init mNode
    RedBlackNode * mNode = pNode->left_;
    pNode->left_ = mNode->right_;
    if (mNode->right_)
        mNode->right_->parent_ = pNode;
    mNode->parent_ = pNode->parent_;
    // set pNode parent
    if (!pNode->parent_)
        root_ = mNode;
    else if (pNode->parent_->left_ == pNode)
        pNode->parent_->left_ = mNode;
    else
        pNode->parent_->right_ = mNode;
    mNode->right_ = pNode;
    // set pNode parent
    pNode->parent_ = mNode;
}

void RedBlackTree::insert(int key)
{
    //init new node
    RedBlackNode * mNode = new RedBlackNode;
    mNode->key_ = key;
    mNode->left_ = nullptr;
    mNode->right_ = nullptr;
    mNode->color_ = Color::RED;
    // travels through the tree
    RedBlackNode * temp = root_;
    // parent of mNode
    RedBlackNode * mParent = nullptr;

    // find where to add
    while (temp)
    {
        mParent = temp;
        if (temp->key_ > mNode->key_)
            temp = temp->left_;
        else
            temp = temp->right_;
    }
    // connect to parent
    mNode->parent_ = mParent;
    // if no root make current node root
    if (!mParent)
        root_ = mNode;
    else if (mParent->key_ > mNode->key_)
        mParent->left_ = mNode;
    else
        mParent->right_ = mNode;
    // increment tree size
    sz_++;
    // fix violated properties
    insert_fixup(mNode);
}

void RedBlackTree::insert_fixup(RedBlackNode * pNode)
{
    RedBlackNode * temp;

    while (pNode->parent_ && pNode->parent_->color_ == Color::RED)
    {
        if (pNode->parent_ == pNode->parent_->parent_->left_)
        {
            temp = pNode->parent_->parent_->right_;
            if (temp && temp->color_ == Color::RED)
            {
                pNode->parent_->color_ = Color::BLACK;
                temp->color_ = Color::BLACK;
                pNode->parent_->parent_->color_ = Color::RED;
                pNode = pNode->parent_->parent_;
            }
            else
            {
                if (pNode == pNode->parent_->right_)
                {
                    pNode = pNode->parent_;
                    left_rotate(pNode);
                }
                pNode->parent_->color_ = Color::BLACK;
                pNode->parent_->parent_->color_ = Color::RED;
                right_rotate(pNode->parent_->parent_);
            }
        }
        else
        {
            temp = pNode->parent_->parent_->left_;
            if (temp && temp->color_ == Color::RED)
            {
                pNode->parent_->color_ = Color::BLACK;
                temp->color_ = Color::BLACK;
                pNode->parent_->parent_->color_ = Color::RED;
                pNode = pNode->parent_->parent_;
            }
            else
            {
                if (pNode == pNode->parent_->left_)
                {
                    pNode = pNode->parent_;
                    right_rotate(pNode);
                }
                pNode->parent_->color_ = Color::BLACK;
                pNode->parent_->parent_->color_ = Color::RED;
                left_rotate(pNode->parent_->parent_);
            }
        }
    }
    root_->color_ = Color::BLACK;
}

void RedBlackTree::in_order(RedBlackNode * pNode)
{
    if (pNode)
    {
        in_order(pNode->left_);
        std::cout << pNode->key_ << " ";
        in_order(pNode->right_);
    }
}

void RedBlackTree::pre_order(RedBlackNode * pNode)
{
    if (pNode)
    {
        std::cout << pNode->key_ << " ";
        pre_order(pNode->left_);
        pre_order(pNode->right_);
    }
}

RedBlackNode * RedBlackTree::search(int key, RedBlackNode * root)
{
    //if (key < root_->key_ ) {
     //   search(root_->left_->key_);
    //}
    return root_;
}

int RedBlackTree::check_property(RedBlackNode * pNode)
{
    if (!pNode)
        return 1;

    int left_height = check_property(pNode->left_);
    if (left_height == 0)
        return left_height;

    int right_height = check_property(pNode->right_);
    if (right_height == 0)
        return right_height;

    if (right_height != left_height)
        return 0;
    else
        return right_height + ((pNode->color_ == Color::BLACK) ? 1 : 0);
}

// replace node u with v
void RedBlackTree::transplant(RedBlackNode * u, RedBlackNode * v)
{
    if (!u->parent_)
        root_ = v;
    else if (u == u->parent_->left_)
        u->parent_->left_ = v;
    else
        u->parent_->right_ = v;
    if (v != nullptr)
        v->parent_ = u->parent_;
}

// delete node z
void RedBlackTree::delete_node(RedBlackNode * z)
{
    RedBlackNode * y = z;
    // node x moves to y place in tree
    RedBlackNode * x;
    RedBlackNode * x_temp_parent;

    Color color = y->color_;

    // case 1: no left child also handles case with no children at all
    if (!z->left_)
    {
        x = z->right_;
        x_temp_parent = z;
        // transplant z->right_ to z's place
        transplant(z,z->right_);
    }
    // case 2: only right child
    else if (!z->right_)
    {
        x = z->left_;
        x_temp_parent = z;
        transplant(z,z->left_);
    }
    // case 3: two children. y replace z
    else
    {
        // y - z's successor
        y = min(z->right_);
        color = y->color_;
        x = y->right_;
        x_temp_parent = y;
        // y - last in left subtree
        if (y->parent_ == z)
            (x) ? x->parent_ = y : x_temp_parent = y;
        else
        {
            // "remove" y and replace with "x"
            x_temp_parent = y->parent_;
            transplant(y,y->right_);
            y->right_ = z->right_;
            y->right_->parent_ = y;
        }
        // delete z and replace with y
        transplant(z,y);
        y->left_ = z->left_;
        y->left_->parent_ = y;
        y->color_ = z->color_;
    }
    // fixup violited properties
    if (color == Color::BLACK)
    {
        //std::cout << "need fixup\n";
        delete_fixup(x, x_temp_parent);
    }
    sz_--;
}

void RedBlackTree::delete_fixup(RedBlackNode * x, RedBlackNode * p)
{
    while (!x || ((x != root_) && (x->color_ == Color::BLACK)))
    {
        if (x == p->left_)
        {
            RedBlackNode * w = p->right_;
            if (w->color_ == Color::RED)
            {
                w->color_ = Color::BLACK;
                p->color_ = Color::RED;
                left_rotate(p);
                w = p->right_;
            }
            if ((!w->left_ && !w->right_) || ((w->left_->color_ == Color::BLACK) && (w->right_->color_ == Color::BLACK)))
            {
                w->color_ = Color::RED;
                x = p;
                p = p->parent_;
            }
            else
            {
                if ((!w->right_) || (w->right_->color_ == Color::BLACK))
                {
                    w->left_->color_ = Color::BLACK;
                    w->color_ = Color::RED;
                    right_rotate(w);
                    w = p->right_;
                }
                w->color_ = p->color_;
                p->color_ = Color::BLACK;
                w->right_->color_ = Color::BLACK;
                left_rotate(p);
                x = root_;
            }
        }
        else
        {
            RedBlackNode * w = p->left_;
            if (w->color_ == Color::RED)
            {
                w->color_ = Color::BLACK;
                p->color_ = Color::RED;
                left_rotate(p);
                w = p->left_;
            }
            if ((!w->left_ && !w->right_) || ((w->left_->color_ == Color::BLACK) && (w->right_->color_ == Color::BLACK)))
            {
                w->color_ = Color::RED;
                x = p;
                p = p->parent_;
            }
            else
            {
                if ((!w->left_) || (w->left_->color_ == Color::BLACK))
                {
                    w->right_->color_ = Color::BLACK;
                    w->color_ = Color::RED;
                    left_rotate(w);
                    w = p->left_;
                }
                w->color_ = p->color_;
                p->color_ = Color::BLACK;
                w->left_->color_ = Color::BLACK;
                right_rotate(p);
                x = root_;
            }
        }
    }
    x->color_ = Color::BLACK;
}

RedBlackTree::~RedBlackTree() { delete root_; }
