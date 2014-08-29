#include "rbtree.hpp"

RedBlackNode::~RedBlackNode() {
    delete left_;
    delete right_;
}

RedBlackTree::RedBlackTree() : sz_(0) {
    root_ = nullptr;
}

RedBlackTree::RedBlackTree(std::initializer_list<int> ls) : sz_(0) {
    root_ = nullptr;
    for (auto i : ls)
        Insert(i);
}

RedBlackNode* RedBlackTree::root() {
    return root_;
}

RedBlackNode* RedBlackTree::Min(RedBlackNode *p_node) {
    while (p_node->left_)
        p_node = p_node->left_;
    return p_node;
}

RedBlackNode *RedBlackTree::Max(RedBlackNode *p_node) {
    while (p_node->right_)
        p_node = p_node->right_;
    return p_node;
}

RedBlackNode *RedBlackTree::Successor(RedBlackNode *p_node) {
    return Min(p_node->right_);
}

RedBlackNode *RedBlackTree::Predecessor(RedBlackNode *p_node) {
    return Max(p_node->left_);
}

void RedBlackTree::LeftRotate(RedBlackNode *p_node) {
    // init m_node
    RedBlackNode *m_node = p_node->right_;
    p_node->right_ = m_node->left_;
    if (m_node->left_)
        m_node->left_->parent_ = p_node;
    m_node->parent_ = p_node->parent_;
    // set m_node parent
    if (!p_node->parent_)
        root_ = m_node;
    else if (p_node->parent_->left_ == p_node)
        p_node->parent_->left_ = m_node;
    else
        p_node->parent_->right_ = m_node;
    m_node->left_ = p_node;
    // set p_node parent
    p_node->parent_ = m_node;
}

void RedBlackTree::RightRotate(RedBlackNode *p_node) {
    // init m_node
    RedBlackNode *m_node = p_node->left_;
    p_node->left_ = m_node->right_;
    if (m_node->right_)
        m_node->right_->parent_ = p_node;
    m_node->parent_ = p_node->parent_;
    // set p_node parent
    if (!p_node->parent_)
        root_ = m_node;
    else if (p_node->parent_->left_ == p_node)
        p_node->parent_->left_ = m_node;
    else
        p_node->parent_->right_ = m_node;
    m_node->right_ = p_node;
    // set p_node parent
    p_node->parent_ = m_node;
}

void RedBlackTree::Insert(int key) {
    //init new node
    RedBlackNode *m_node = new RedBlackNode;
    m_node->key_ = key;
    m_node->left_ = nullptr;
    m_node->right_ = nullptr;
    m_node->color_ = Color::RED;
    // travels through the tree
    RedBlackNode *temp = root_;
    // parent of m_node
    RedBlackNode *parent = nullptr;

    // find where to add
    while (temp) {
        parent = temp;
        if (m_node->key_ < temp->key_)
            temp = temp->left_;
        else
            temp = temp->right_;
    }
    // connect to parent
    m_node->parent_ = parent;
    // if no root make current node root
    if (!parent)
        root_ = m_node;
    else if (parent->key_ > m_node->key_)
        parent->left_ = m_node;
    else
        parent->right_ = m_node;
    // increment tree size
    sz_++;
    // fix violated properties
    InsertFixup(m_node);
}

void RedBlackTree::InsertFixup(RedBlackNode *p_node) {
    RedBlackNode *temp;

    while (p_node->parent_ && p_node->parent_->color_ == Color::RED) {
        if (p_node->parent_ == p_node->parent_->parent_->left_) {
            temp = p_node->parent_->parent_->right_;
            if (temp && temp->color_ == Color::RED) {
                p_node->parent_->color_ = Color::BLACK;
                temp->color_ = Color::BLACK;
                p_node->parent_->parent_->color_ = Color::RED;
                p_node = p_node->parent_->parent_;
            } else {
                if (p_node == p_node->parent_->right_) {
                    p_node = p_node->parent_;
                    LeftRotate(p_node);
                }
                p_node->parent_->color_ = Color::BLACK;
                p_node->parent_->parent_->color_ = Color::RED;
                RightRotate(p_node->parent_->parent_);
            }
        } else {
            temp = p_node->parent_->parent_->left_;
            if (temp && temp->color_ == Color::RED) {
                p_node->parent_->color_ = Color::BLACK;
                temp->color_ = Color::BLACK;
                p_node->parent_->parent_->color_ = Color::RED;
                p_node = p_node->parent_->parent_;
            } else {
                if (p_node == p_node->parent_->left_) {
                    p_node = p_node->parent_;
                    RightRotate(p_node);
                }
                p_node->parent_->color_ = Color::BLACK;
                p_node->parent_->parent_->color_ = Color::RED;
                LeftRotate(p_node->parent_->parent_);
            }
        }
    }
    root_->color_ = Color::BLACK;
}

void RedBlackTree::InOrder(RedBlackNode *p_node) {
    if (p_node) {
        InOrder(p_node->left_);
        std::cout << p_node->key_ << " ";
        InOrder(p_node->right_);
    }
}

void RedBlackTree::PreOrder(RedBlackNode *p_node) {
    if (p_node) {
        std::cout << p_node->key_ << " ";
        PreOrder(p_node->left_);
        PreOrder(p_node->right_);
    }
}

RedBlackNode * RedBlackTree::Search(int key, RedBlackNode *p_node) {
    if (!p_node) {
        return nullptr;
    } else if (key == p_node->key_) {
        return p_node;
    } else if (key < p_node->key_ ) {
        return Search(key, p_node->left_);
    } else if (key >= p_node->key_) {
        return Search(key, p_node->right_);
    } else {
        return nullptr;
    }
}

int RedBlackTree::CheckProperty(RedBlackNode *p_node) {
    if (!p_node)
        return 1;

    int left_height = CheckProperty(p_node->left_);
    if (left_height == 0)
        return left_height;

    int right_height = CheckProperty(p_node->right_);
    if (right_height == 0)
        return right_height;

    if (right_height != left_height)
        return 0;
    else
        return right_height + ((p_node->color_ == Color::BLACK) ? 1 : 0);
}

// replace node u with v
void RedBlackTree::Transplant(RedBlackNode *u, RedBlackNode *v) {
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
void RedBlackTree::DeleteNode(RedBlackNode *z) {
    RedBlackNode *y = z;
    // node x moves to y place in tree
    RedBlackNode *x;
    RedBlackNode *x_temp_parent;

    Color color = y->color_;

    // case 1: no left child also handles case with no children at all
    if (!z->left_) {
        x = z->right_;
        x_temp_parent = z;
        // transplant z->right_ to z's place
        Transplant(z,z->right_);
    } else if (!z->right_) {
        // case 2: only right child
        x = z->left_;
        x_temp_parent = z;
        Transplant(z,z->left_);
    } else {
        // case 3: two children
        // y - z's successor
        y = Successor(z);
        color = y->color_;
        x = y->right_;
        x_temp_parent = y;
        // y - last in left subtree
        if (y->parent_ == z) {
            (x) ? x->parent_ = y : x_temp_parent = y;
        } else {
            // "remove" y and replace with "x"
            x_temp_parent = y->parent_;
            Transplant(y,y->right_);
            y->right_ = z->right_;
            y->right_->parent_ = y;
        }
        // delete z and replace with y
        Transplant(z,y);
        y->left_ = z->left_;
        y->left_->parent_ = y;
        y->color_ = z->color_;
    }
    // fixup violited properties
    if (color == Color::BLACK) {
        //std::cout << "need fixup\n";
        DeleteFixup(x, x_temp_parent);
    }
    // decrease size
    sz_--;
}

// p == x->parent
// w == x->parent->left(right)
<<<<<<< HEAD
void RedBlackTree::DeleteFixup(RedBlackNode *x, RedBlackNode *p) {
=======
void RedBlackTree::delete_fixup(RedBlackNode *x, RedBlackNode *p) {
>>>>>>> FETCH_HEAD
    while (!x || ((x != root_) && (x->color_ == Color::BLACK))) {
        if (x == p->left_) {

            RedBlackNode * w = p->right_;
            // case 1: can go to 2nd case
            if (w->color_ == Color::RED) {
                w->color_ = Color::BLACK;
                p->color_ = Color::RED;
                LeftRotate(p);
                w = p->right_;
            }
            if ((!w->left_ && !w->right_) || ((w->left_->color_ == Color::BLACK) && (w->right_->color_ == Color::BLACK))) {
                w->color_ = Color::RED;
                x = p;
                p = p->parent_;
            } else {
                // case 3: transforms to case 4
                if ((!w->right_) || (w->right_->color_ == Color::BLACK)) {
                    w->left_->color_ = Color::BLACK;
                    w->color_ = Color::RED;
                    RightRotate(w);
                    w = p->right_;
                }
                w->color_ = p->color_;
                p->color_ = Color::BLACK;
                w->right_->color_ = Color::BLACK;
                LeftRotate(p);
                x = root_;
            }
        } else {
            RedBlackNode * w = p->left_;

            if (w->color_ == Color::RED) {
                w->color_ = Color::BLACK;
                p->color_ = Color::RED;
                LeftRotate(p);
                w = p->left_;
            }
            if ((!w->left_ && !w->right_) || ((w->left_->color_ == Color::BLACK) && (w->right_->color_ == Color::BLACK))) {
                w->color_ = Color::RED;
                x = p;
                p = p->parent_;
            } else {
                if ((!w->left_) || (w->left_->color_ == Color::BLACK)) {
                    w->right_->color_ = Color::BLACK;
                    w->color_ = Color::RED;
                    LeftRotate(w);
                    w = p->left_;
                }
                w->color_ = p->color_;
                p->color_ = Color::BLACK;
                w->left_->color_ = Color::BLACK;
                RightRotate(p);
                x = root_;
            }
        }
    }
    x->color_ = Color::BLACK;
}

RedBlackTree::~RedBlackTree() {
    delete root_;
}
