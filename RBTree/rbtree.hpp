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
    RedBlackNode *Search(int, RedBlackNode *);
    RedBlackNode *Min(RedBlackNode *);
    RedBlackNode *Max(RedBlackNode *);
    RedBlackNode *Successor(RedBlackNode *);
    RedBlackNode *Predecessor(RedBlackNode *);

    void LeftRotate(RedBlackNode *);
    void RightRotate(RedBlackNode *);

    void Insert(int);
    void DeleteNode(RedBlackNode *);

    void InOrder(RedBlackNode *);
    void PreOrder(RedBlackNode *);

    int CheckProperty(RedBlackNode *);

    ~RedBlackTree();
private:
    RedBlackNode *root_;
    std::size_t sz_;

    void InsertFixup(RedBlackNode *);
    void DeleteFixup(RedBlackNode *, RedBlackNode *);
    void Transplant(RedBlackNode *, RedBlackNode *);
};

//#endif
