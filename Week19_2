#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Node{
    unordered_map<char, Node*> children;
    bool isEndOfWord;

    Node() : isEndOfWord(false) {}
};

class Trie{
private:
    Node* root;
public:
    Trie() {
        root = new Node();
    }

    Trie(string filename){
        root = new Node();

        std::ifstream file(filename);
        std::string line;

        if (file && getline(file, line)) {
            std::stringstream ss(line);
            std::string word;

            while (getline(ss, word, ',')) {
                // remove a single leading space if it exists
                if (!word.empty() && word.front() == ' ')
                    word.erase(word.begin());
                insert(word);
            }
        }
    }

    Node* getRoot() {
        return root;
    }

    void insert(const string& word) {
        Node* current = root;
        for(char c : word) {
            if(current->children.find(c) == current->children.end()) {
                current->children[c] = new Node();
            }
            current = current->children[c];
        }
        current->isEndOfWord = true;
    }

    bool search(const string& word) {
        Node* current = root;
        for(char c : word) {
            if(current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        return current->isEndOfWord;
    }

    void deleteSubtree(Node* node) {
        for(auto& pair : node->children) {
            deleteSubtree(pair.second);
        }
        delete node;
    }

    void printSubtree(Node* node, string prefix) {
        if(node->isEndOfWord) {
            cout << prefix << endl;
        }
        for(auto& pair : node->children) {
            printSubtree(pair.second, prefix + pair.first);
        }
    }
    void print(){
        printSubtree(root, "");
    }

    ~Trie() {
        // Destructor to free memory (not implemented here for brevity)
        deleteSubtree(root);
    }
};

list<unsigned> indices(string text, Trie& T, unsigned start){
    
    list<unsigned> indices;
    unsigned index = start;

    Node* current = T.getRoot();
    
    while(current->children.find(text[index]) != current->children.end()){
        current = current->children[text[index]];
        if(current->isEndOfWord){
            indices.push_back(index + 1);
        }
        index++;
        if(index >= text.size()){
            break;
        }
    }

    return indices;
}

int64_t StringCoveringWays(string text, Trie& T, unsigned start, vector<int64_t>& memo){
    
    if(memo[start] != -1){
        return memo[start];
    }
    
    if(start >= text.size()){
        memo[start] = 1;
        return 1;
    }

    list<unsigned> inds = indices(text, T, start);

    if(inds.size() == 0){
        memo[start] = 0;
        return 0;
    }
    else{
        for(unsigned i : inds){
            memo[start] += StringCoveringWays(text, T, i, memo);
        }
    }


    memo[start] += 1;
    return memo[start];
}

int64_t execute(string textfile){
    Trie T("input19.txt");
    int64_t count = 0;
    std::ifstream file(textfile);
    std::string line;
    unsigned lineNumber = 0;
    vector<int64_t> memo(100, -1);

    while (getline(file, line)) {
        lineNumber++;
        if (lineNumber < 3) {
            continue;
        }

        count += StringCoveringWays(line, T, 0, memo);

        fill(memo.begin(), memo.end(), -1);
    }
    
    return count;
}

int main(){
    cout<< execute("input19.txt");
    
    return 0;
}
