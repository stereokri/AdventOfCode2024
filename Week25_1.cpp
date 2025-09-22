#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>

using namespace std;


struct TreeNode{
    uint8_t branches;
    vector<TreeNode*> children;

    TreeNode() {
        branches = 0;
        children = vector<TreeNode*>(6, nullptr);
    }
};


class MapTree{
private:
    TreeNode* root;
public:
    MapTree(){
        root = new TreeNode();
    }

    void insert(const vector<uint8_t>& lock){
        TreeNode* current = root;

        for(uint8_t pin : lock){
            if(current->children[pin] == nullptr){
                current->children[pin] = new TreeNode();
                current->branches++;
            }
            current = current->children[pin];
        }
    }

    ~MapTree(){
        clear(root);
    }

    void clear(TreeNode* node){
        if(node == nullptr) return;

        for(auto& nextPin : node->children){
            clear(nextPin);
            delete nextPin;
        }
    }


    uint64_t countLocks(vector<uint8_t>& key, TreeNode* current, uint8_t index){
        if(current == root && current->branches == 0){
            return 0;
        }

        if(current->branches == 0){
            return 1;
        }

        uint64_t locks = 0;
        for(uint8_t i = 0; i <= 5 - key[index]; i++){
            if(current->children[i] != nullptr){
                locks += countLocks(key, current->children[i], index + 1);
            }
        }

        return locks;
    }


    uint64_t readFileAndExecute(string filename){
        ifstream file(filename);
        string lock_key_line;
        string line;
        vector<vector<uint8_t>> keys;
    
    
        while(getline(file, lock_key_line)){
    
            if(lock_key_line.empty()){
                continue;
            }
            
            vector<uint8_t> lock_key(5, 0);
            for(int i = 0; i < 5; i++){
                getline(file, line);
    
                for(uint8_t i = 0; i < 5; i++){
                    if(line[i] == '#'){
                        lock_key[i]++;
                    }
                }
            }
            getline(file, line);
    
            if(lock_key_line == "#####"){
                insert(lock_key);
            }
            else{
                keys.push_back(lock_key);
            }
        }
    
        uint64_t matches = 0;
    
        for(auto& key : keys){
            matches += countLocks(key, root, 0);
        }
    
        return matches;
    }
};


int main(){
    MapTree T;
    cout<<T.readFileAndExecute("input25.txt")<<endl;

    return 0;
}
