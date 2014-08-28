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
        insert(i);
}

RedBlackNode* RedBlackTree::root() {
    return root_;
}


RedBlackNode* RedBlackTree::min(RedBlackNode *p_node) {
    while (p_node->left_)
        p_node = p_node->left_;
    return p_node;
}

void RedBlackTree::left_rotate(RedBlackNode *p_node) {
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

void RedBlackTree::right_rotate(RedBlackNode *p_node) {
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

void RedBlackTree::insert(int key) {
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
        if (temp->key_ > m_node->key_)
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
    insert_fixup(m_node);
}

void RedBlackTree::insert_fixup(RedBlackNode *p_node) {
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
                    left_rotate(p_node);
                }
                p_node->parent_->color_ = Color::BLACK;
                p_node->parent_->parent_->color_ = Color::RED;
                right_rotate(p_node->parent_->parent_);
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
                    right_rotate(p_node);
                }
                p_node->parent_->color_ = Color::BLACK;
                p_node->parent_->parent_->color_ = Color::RED;
                left_rotate(p_node->parent_->parent_);
            }
        }
    }
    root_->color_ = Color::BLACK;
}

void RedBlackTree::in_order(RedBlackNode *p_node) {
    if (p_node) {
        in_order(p_node->left_);
        std::cout << p_node->key_ << " ";
        in_order(p_node->right_);
    }
}

void RedBlackTree::pre_order(RedBlackNode *p_node) {
    if (p_node) {
        std::cout << p_node->key_ << " ";
        pre_order(p_node->left_);
        pre_order(p_node->right_);
    }
}

RedBlackNode * RedBlackTree::search(int key, RedBlackNode *root) {
    //if (key < root_->key_ ) {
     //   search(root_->left_->key_);
    //}
    return root_;
}

int RedBlackTree::check_property(RedBlackNode *p_node) {
    if (!p_node)
        return 1;

    int left_height = check_property(p_node->left_);
    if (left_height == 0)
        return left_height;

    int right_height = check_property(p_node->right_);
    if (right_height == 0)
        return right_height;

    if (right_height != left_height)
        return 0;
    else
        return right_height + ((p_node->color_ == Color::BLACK) ? 1 : 0);
}

// replace node u with v
void RedBlackTree::transplant(RedBlackNode *u, RedBlackNode *v) {
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
void RedBlackTree::delete_node(RedBlackNode *z) {
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
        transplant(z,z->right_);
    } else if (!z->right_) {
        // case 2: only right child
        x = z->left_;
        x_temp_parent = z;
        transplant(z,z->left_);
    } else {
        // case 3: two children
        // y - z's successor
        y = min(z->right_);
        color = y->color_;
        x = y->right_;
        x_temp_parent = y;
        // y - last in left subtree
        if (y->parent_ == z) {
            (x) ? x->parent_ = y : x_temp_parent = y;
        } else {
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
    if (color == Color::BLACK) {
        //std::cout << "need fixup\n";
        delete_fixup(x, x_temp_parent);
    }
    sz_--;
}

// p == x->parent
// w == x->parent->left(right)
void RedBlackTree::delete_fixup(RedBlackNode *x, RedBlackNode *p) {
    while (!x || ((x != root_) && (x->color_ == Color::BLACK))) {
        if (x == p->left_) {
            RedBlackNode * w = p->right_;
            if (w->color_ == Color::RED) {
                w->color_ = Color::BLACK;
                p->color_ = Color::RED;
                left_rotate(p);
                w = p->right_;
            }
            if ((!w->left_ && !w->right_) || ((w->left_->color_ == Color::BLACK) && (w->right_->color_ == Color::BLACK))) {
                w->color_ = Color::RED;
                x = p;
                p = p->parent_;
            } else {
                if ((!w->right_) || (w->right_->color_ == Color::BLACK)) {
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
        } else {
            RedBlackNode * w = p->left_;
            if (w->color_ == Color::RED) {
                w->color_ = Color::BLACK;
                p->color_ = Color::RED;
                left_rotate(p);
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

RedBlackTree::~RedBlackTree() {
    delete root_;
}
