#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;




void fileReader(string &path, vector<string> &id, vector<string> &game_names, vector<string> &rating, vector<string> &genres, vector<string> &platforms,vector<string> &pubs_devs ) {
    int count = 1;

    fstream inFile;
    string output = "";
    

    inFile.open(path);
    while(!inFile.eof()) {
        if (count == 1) {
            while(getline(inFile,output,','));
            count--;
        }
    
        getline(inFile,output,',');     
            id.push_back(output);
        getline(inFile,output,',');     
            game_names.push_back(output);   
        getline(inFile,output,',');     
            rating.push_back(output);
        getline(inFile,output, ',');
            genres.push_back(output);
        getline(inFile,output,',');     
            platforms.push_back(output);
        getline(inFile,output,',');     
            pubs_devs.push_back(output);
    }
    inFile.close();
    

}    


int main() {

   
    string path = "games.csv";

    vector<string> id;
    vector<string> game_names;
    vector<string> rating;
    vector<string> genres;
    vector<string> platforms;
    vector<string> pubs_devs;

    fileReader(path, id, game_names, rating, genres, platforms, pubs_devs);

    for(int i = 0; i < id.size(); i++) {
        cout << "Game: " << game_names[i] << endl;
        cout << "Rating: " << rating[i] << endl;
        cout << "Platform(s): " << platforms[i] << endl;
        cout << "Publishers/Developers: " << pubs_devs[i] << endl;

    }
    
    

    

    

}