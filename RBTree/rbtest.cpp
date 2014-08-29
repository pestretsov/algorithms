#include <iostream>
#include "rbtree.hpp"

using std::cout;

int main()
{
    std::initializer_list<int> ls = {815, 710,
        659, 377, 558, 883, 578, 222, 710, 572,
        831, 970, 610, 630, 720};
    RedBlackTree tree(ls);

    // RedBlackNode * x = tree.root()->right_->right_->right_;
    // RedBlackNode * y = tree.root()->left_->right_->right_;
    // RedBlackNode * z = tree.root()->right_->left_->right_;
    // cout << x->key_ << std::endl;
    // tree.delete_node(x);
    // tree.delete_node(y);
    // tree.delete_node(z);

    tree.DeleteNode(tree.root());
    tree.DeleteNode(tree.root());
    tree.DeleteNode(tree.root());
    //cout << tree.size() << "\n";
    tree.DeleteNode(tree.root());
    tree.PreOrder(tree.root());
    cout << std::endl;
    //cout << tree.root()->right_->left_->right_->key_;
    //cout << tree.root()->right_->left_->key_;

    //cout << tree.CheckProperty(tree.root()) << "\n";
    cout << tree.Search(610, tree.root())->key_ << "\n";
    //cout << tree.size() << "\n";
    return 0;
}
