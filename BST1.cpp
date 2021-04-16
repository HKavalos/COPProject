#include <iostream>
using namespace std;

class TreeNode {
public:
    int rating;
    string title;
    string genre;
    string developer;
    float price;
    string platform;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x, string t, string g, string d, float p, string plat) : rating(x), title(t), genre(g), developer(d), price(p), platform(plat), left(nullptr), right(nullptr) {}
};

class Tree {
private:
    TreeNode* root;
public:
    TreeNode* insert(TreeNode* root, int key, string tle, string gnr, string dev, float prc, string pltf);
    //level order ? traverse
};

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

/*
    
    
*/
