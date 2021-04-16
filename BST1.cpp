#include <iostream>
using namespace std;

class TreeNode {
public:
    int rating;
    /*string title;
    string genre;
    string developer;
    float price;
    string platform;*/
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : rating(x), left(nullptr), right(nullptr) {}
};

class Tree {
private:
    TreeNode* root;
public:
    TreeNode* insert(TreeNode* root, int key);
    void inorder(TreeNode* root);
};

int main()
{
    //read input from a file and put input into node variables

}

//Source: Powerpoint Trees-2 Slide 12
TreeNode* insert(TreeNode* root, int key) {
    if (root == nullptr)
        return new TreeNode(key);
    if (key < root->rating)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);
    return root;
}

//Source: Powerpoint Trees-2 Slide 17
void inorder(TreeNode* root) {
    if (root == nullptr)
        cout << "";
    else {
        inorder(root->left);
        cout << root->rating << "";
        inorder(root->right);
    }
}
