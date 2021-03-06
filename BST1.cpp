#include <iostream>
#include <vector>
using namespace std;

class TreeNode {
public:
    int rating;
    string title;
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
    TreeNode* insert(TreeNode* root, int key, string tle, string gnr, string dev, float prc, string pltf);
    void inorder(TreeNode* root);

int main()
{
    //read input from a file and put input into node variables

}

//Source: Powerpoint Trees-2 Slide 12
TreeNode* insert(TreeNode* root, int key, string tle, string gnr, string dev, float prc, string pltf) {
    if (root == nullptr)
        return new TreeNode(key, tle, gnr, dev, prc, pltf);
    if (key < root->rating)
        root->left = insert(root->left, key, tle, gnr, dev, prc, pltf);
    else
        root->right = insert(root->right, key, tle, gnr, dev, prc, pltf);
    return root;
}

//Source: Powerpoint Trees-2 Slide 17
void inorder(TreeNode* root) {
    //vector<TreeNode*> games;
    if (root == nullptr)
        cout << "";
    else {
        inorder(root->left);
        cout << root->rating << " ";
        inorder(root->right);
    }
    //return games;
}
