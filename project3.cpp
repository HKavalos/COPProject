#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

struct Games {
    int id;
    string game_names;
    double rating;
    string genres;
    string platforms;
    string pubs_devs;
};

class TreeNode {
public:
    int key;  //rating
    Games gamedata = {};
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

};

struct PriorityQueue
{
private:
    //stores values
    vector<Games> MaxHeap;
    int Parent(int i)
    {
        return (i - 1) / 2;
    }

    //returns left child
    int LC(int i)
    {
        return (2 * i + 1);
    }

    //returns right child
    int RC(int i)
    {
        return (2 * i + 2);
    }


    //Heapify's up
    void heapifyU(int x)
    {
        // Checks if swap is neccessary
        if (MaxHeap[Parent(x)].rating < MaxHeap[x].rating)
        {
            swap(MaxHeap[x], MaxHeap[Parent(x)]);
            //calls Heapifyu again
            heapifyU(Parent(x));
        }
    }
    //Heapifies down from pos x
    void heapifyD(int x)
    {
        unsigned int left = LC(x);
        unsigned int right = RC(x);

        int lpos = x;

        //determines if and which child to switch with
        if (left < MaxHeap.size() && MaxHeap[left].rating > MaxHeap[x].rating)
        {
            lpos = left;
        }

        if (right < MaxHeap.size() && MaxHeap[right].rating > MaxHeap[lpos].rating)
        {
            lpos = right;
        }

        //swaps and calls HeapifyD again
        if (lpos != x)
        {
            swap(MaxHeap[x], MaxHeap[lpos]);
            heapifyD(lpos);
        }
    }

public:

    //checks if maxheap is empty
    bool empty()
    {
        if (MaxHeap.size() == 0)
            return true;
        else
            return false;
    }

    //inserts values then calls heapifyU
    void push(Games x)
    {
        MaxHeap.push_back(x);
        int index = MaxHeap.size() - 1;
        heapifyU(index);
    }

    //Pops the next element
    Games pop()
    {
        Games temp = MaxHeap[0];
        MaxHeap[0] = MaxHeap.back();
        MaxHeap.pop_back();
        heapifyD(0);
        return temp;
    }

    void topPicks(string test)
    {
        int count = 50;
        while (count > 0)
        {
            Games value = pop();
            if (value.genres == test)
            {
                cout << value.game_names << endl;
                count--;
            }
        }
    }
};

class IGDB {
public:
    TreeNode* root;
    vector<TreeNode*> games;
    string strOutput = ""; //use for cout ouput

    IGDB()
    {
        root = nullptr;
    }

    TreeNode* insertNode(TreeNode* root, TreeNode* node) {
        if (root == nullptr) {
            root = node;
            return root;
        }

        if (node->key < root->key) {
            root->left = insertNode(root->left, node);
        }
        else if (node->key > root->key) {
            root->right = insertNode(root->right, node);
        }
        else {
            return root;
        }
        return root;
    }

    /*
    void inorder(TreeNode* root) {
        //vector<TreeNode*> games;
        if (root == nullptr)
            cout << "";
        else {
            inorder(root->left);
            cout << root->gamedata.game_names << " ";
            inorder(root->right);
        }
    }*/

    //using inorder traversal, searches for the genre inputted by the user and if node contains the genre, pushes node into a vector of nodes
    vector <TreeNode*> inorderSearchGenre(string genre, TreeNode* root, vector<TreeNode*> &games) {
        if (root == nullptr){
            return {};
        }
        //if input is in gamedata contains input string, game is added to vector
        if (root->gamedata.genres.find(genre) != string::npos ) {
            games.push_back(root);
        }
        if (root->gamedata.genres == genre) {
            games.push_back(root);
        }
        inorderSearchGenre(genre, root->left, games);
        inorderSearchGenre(genre, root->right, games);

        return games;
    }
    


};
string capitalize_first_letter(string input) {

    for (int i = 0; i < input.length(); i++) {

        if (i == 0) {
            input[i] = toupper(input[i]);
        }
    }
    return input;
}


int main() {

    Games gameObj;

    string filePath = "games.csv";
    IGDB igdb;
    fstream inFile;
    string output;
 
    char del = ',';
    inFile.open(filePath, ios::in);
    int cnt = 0;
    int id = 0; 
    //int BST_time = 0;

    PriorityQueue games_PQ = PriorityQueue();
    if (inFile.is_open()) {
        string tp;  
        
        std::cout << "Initializing data in BST..." << endl;
        auto start = high_resolution_clock::now();

        while (!inFile.eof()) {
            TreeNode* newnode = new TreeNode();
            if (cnt == 0) {
                getline(inFile, output);
                cnt++;
                continue;
            }
            getline(inFile, output, ',');

            if (output == "")
                continue;
            else
                gameObj.id = stoi(output);

            getline(inFile, output, '\"');

            getline(inFile, output, '\"');
            gameObj.game_names = "\"" + output + "\"";

            getline(inFile, output, ',');
            getline(inFile, output, ',');
            //double d = stod(output);
            if (output == "")
                gameObj.rating = 0;
            else
                gameObj.rating = stod(output);

            getline(inFile, output, ',');
            gameObj.genres = output;

            getline(inFile, output, ',');
            gameObj.platforms = output;

            getline(inFile, output);
            gameObj.pubs_devs = output;

            newnode->key = gameObj.id;
            newnode->gamedata = gameObj;

            games_PQ.push(gameObj);
            
            igdb.root = igdb.insertNode(igdb.root, newnode);
            
            
            cnt++;

        }
       // auto stop = high_resolution_clock::now();
        //auto duration = duration_cast<microseconds>(stop - start);
        //BST_time = duration.count();
       // cout << "BST Insertion: " << BST_time << " microseconds" << endl;
       

        inFile.close();
    }

    string user_input;

    cout << "Please enter your favorite genre: ";
    cin >> user_input;
    user_input = capitalize_first_letter(user_input);
    cout << "Getting top 50 games..." << endl;

    topPicks(user_input);

    //user_input = "\"" + user_input + "\"";
    auto start = high_resolution_clock::now();
    igdb.inorderSearchGenre(user_input, igdb.root, igdb.games);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);


   


    
    for (int i = 0; i < 50; i++) {
        cout << igdb.games[i]->gamedata.game_names << endl << endl;

    } 
    
    cout << "BST Inorder Search by Genre: " << duration.count() << " microseconds" << endl;
  
    //TODO: create menu for user to choose preferred genre
    //TODO: put games in PQ

    

    delete igdb.root;

}