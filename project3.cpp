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

struct PriorityQueue
{
    //calculates the index of the index's parent.
   int Parent(int i)
    {
        return (i - 1) / 2;
    }

    //calculates the index of the index's left child.
    int LC(int i)
    {
        return (2 * i + 1);
    }

    //calculates the index of the index's left child.
    int RC(int i)
    {
        return (2 * i + 2);
    }

    //Heapify's up from pos x
    // Average and worst case is O(log(N))
    void heapifyU(vector<Games>& MaxHeap, int x)
    {
        // Checks if swap is neccessary
        if (MaxHeap[Parent(x)].rating < MaxHeap[x].rating)
        {
            swap(MaxHeap[x], MaxHeap[Parent(x)]);
            //calls Heapifyu again
            heapifyU(MaxHeap,Parent(x));
        }
    }

    //Heapifies down from pos x
    // Average and worst case is O(log(N))
    void heapifyD(vector<Games>& MaxHeap, int x)
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
            heapifyD(MaxHeap,lpos);
        }
    }

    //checks if maxheap is empty
    bool empty(vector<Games>& MaxHeap)
    {
        if (MaxHeap.size() == 0)
            return true;
        else
            return false;
    }
    // Average and worst case is O(log(N))
    //inserts values then calls heapifyU
    void push(vector<Games>& MaxHeap, Games x)
    {
        MaxHeap.push_back(x);
        int index = MaxHeap.size() - 1;
        heapifyU(MaxHeap,index);
    }
    //Pops the head value and then calls heapifyD
    // Average and worst case is O(log(N))
    Games pop(vector<Games>& MaxHeap)
    {
        Games temp = MaxHeap[0];
        MaxHeap[0] = MaxHeap.back();
        MaxHeap.pop_back();
        heapifyD(MaxHeap,0);
        return temp;
    }
    
    //Pops values and prints out the first 25 values that match the user inputed criteria
    void printPQ(vector<Games>& MaxHeap, string user_input)
    {

        int count = 0;
        user_input = "\"" + user_input + "\"";

        while (count != 25)
        {
            Games printer = pop(MaxHeap);
            if (printer.genres == user_input || printer.genres.find(user_input) != string::npos) {
                std::cout << count + 1 << "." << printer.game_names << " | " << printer.rating << "% | " << printer.genres << " | " << printer.platforms << " | " << printer.pubs_devs << endl;
                count++;
            }
        }
    } 
};


class TreeNode {
public:
    double key;  //rating
    Games gamedata = {};
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

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
    //Average case is O(log(N))
    //Worst case is 0(N)
    //recursivly inserts nodes
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

    //using reverse inorder traversal, searches for the genre inputted by the user and if node contains the genre, pushes node into a vector of nodes
    // Average case is O(log(N))
    //Worst case is 0(N)
    vector <TreeNode*> inorderSearchGenre(string genre, TreeNode* root, vector<TreeNode*> &games) {
        if (root == nullptr){
            return {};
        }
        inorderSearchGenre(genre, root->right, games);
        if(root->gamedata.genres.find(genre) != string::npos && root->gamedata.rating)
            games.push_back(root);
        inorderSearchGenre(genre, root->left, games);
        

        return games;
    }

    void printBST(vector <TreeNode*> &games, string user_input) {

        for (int i = 0; i < 25; i++) {
            cout << i + 1 << "." << games[i]->gamedata.game_names << " | " << games[i]->gamedata.rating << "% | " << games[i]->gamedata.genres << " | " << games[i]->gamedata.platforms << " | " << games[i]->gamedata.pubs_devs << endl;
       
        } 

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

    PriorityQueue PQ = PriorityQueue();
    vector<Games> gamesVec;

    string filePath = "games.csv";
    IGDB igdb;
    fstream inFile;
    string output;
 
    char del = ',';
    inFile.open(filePath, ios::in);
    int cnt = 0;
    int id = 0; 
   
    if (inFile.is_open()) {
        string tp;  
        
        std::cout << "\nInitializing data to BST and Priority Queue..." << endl << endl;
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
            
            PQ.push(gamesVec,gameObj);

            newnode->key = gameObj.rating;
            newnode->gamedata = gameObj;

            igdb.root = igdb.insertNode(igdb.root, newnode);
     
            cnt++;

        }
        inFile.close();
    }
    
    cout << "Welcome to our Game Parser!" << endl << endl;

    cout << "Genre Options: " << endl << endl;
    cout << "Fighting" << endl;
    cout << "Shooter" << endl;
    cout << "Music" << endl;
    cout << "Platform" << endl;
    cout << "Puzzle" << endl;
    cout << "Racing" << endl;
    cout << "Simulator" << endl;
    cout << "Sport"<< endl;
    cout << "Strategy" << endl;
    cout << "Tactical" << endl;
    cout << "Adventure" << endl;
    cout << "Arcade" << endl;
    cout << "Indie" << endl << endl;

    string user_input;
    cout << "Please enter your favorite genre from the list above: ";
    cin >> user_input;
    user_input = capitalize_first_letter(user_input);

    cout << "Getting top 25 games..." << endl << endl;

    //user_input = "\"" + user_input + "\"";
    auto start = high_resolution_clock::now();
    igdb.inorderSearchGenre(user_input, igdb.root, igdb.games);
    
    

    cout << "Top 25 Games from Priority Queue:" << endl;
    auto start2 = high_resolution_clock::now();
    
    PQ.printPQ(gamesVec, user_input);
    auto stop2 = high_resolution_clock::now();
    auto PQtime = duration_cast<microseconds>(stop2 - start2);
    cout << "\nPriority Queue Search by Genre: " << PQtime.count() <<" microseconds" << endl << endl << endl;

    cout << "Top 25 Games from BST: " << endl;
    igdb.printBST(igdb.games, user_input);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nBST Inorder Search by Genre: " << duration.count() << " microseconds" << endl;

    cout << "\nThanks for Using Game Parser! :)\n";

    delete igdb.root;
    delete &gamesVec;

}