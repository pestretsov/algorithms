//#ifndef _rbtree_h_
//#define _rbtree_h_

#include <iostream>
#include <initializer_list>

enum class Color {RED, BLACK};

struct RedBlackNode {
    Color color_;
    int key_;
    RedBlackNode *left_;
    RedBlackNode *right_;
    RedBlackNode *parent_;

    ~RedBlackNode();
};

class RedBlackTree {
public:
    RedBlackTree();
    RedBlackTree(std::initializer_list<int>);

    std::size_t size() {return sz_;};
    RedBlackNode *root();
    RedBlackNode *search(int, RedBlackNode *);
    RedBlackNode *min(RedBlackNode *);

    void left_rotate(RedBlackNode *);
    void right_rotate(RedBlackNode *);

    void insert(int);
    void delete_node(RedBlackNode *);

    void in_order(RedBlackNode *);
    void pre_order(RedBlackNode *);

    int check_property(RedBlackNode *);

    ~RedBlackTree();
private:
    RedBlackNode *root_;
    std::size_t sz_;

    void insert_fixup(RedBlackNode *);
    void delete_fixup(RedBlackNode *, RedBlackNode *);
    void transplant(RedBlackNode *, RedBlackNode *);
};

//#endif
