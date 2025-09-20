#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <tuple>
#include <chrono>
#include <set>
#include <queue>

using namespace std;

struct CompareDescending {
    bool operator()(const std::pair<int,int>& a, const std::pair<int,int>& b) const {
        if(a.first == b.first){
            return a.second > b.second;
        }
        return a.first > b.first;
    }
};


void printBoard(vector<vector<char> >& board, pair<unsigned, unsigned> position){
    for(unsigned i = 0; i < board.size(); i++){
        for(unsigned j = 0; j < board[i].size(); j++){
            if(i == position.first && j == position.second){
                cout<<'@';
            }
            else
                cout<<char(board[i][j]);
        }
        cout<<endl;
    }
    cout<<endl;
}


void MoveUp(vector<vector<char> >& board, pair<unsigned, unsigned>& position){
    set<pair<unsigned, unsigned>> blocks_left_bracket_indices;
    queue<pair<unsigned, unsigned>> Q;

    if(board[position.first - 1][position.second] == '.'){
        position.first -= 1;
        return;
    }
    else if(board[position.first - 1][position.second] == '#' ){
        return;
    }
    else{
        if(board[position.first - 1][position.second] == '['){
            blocks_left_bracket_indices.insert({position.first - 1, position.second});
            board[position.first - 1][position.second] = 'V';
            Q.push({position.first - 1, position.second});
        }
        else{
            blocks_left_bracket_indices.insert({position.first - 1, position.second - 1});
            board[position.first - 1][position.second - 1] = 'V';
            Q.push({position.first - 1, position.second - 1});
        }
    }

    while(!Q.empty()){
        pair<unsigned, unsigned> current = Q.front();
        Q.pop();

        if(board[current.first - 1][current.second] == '#' || board[current.first - 1][current.second + 1] == '#'){
            // Revert all changes to board and return because no movement possible
            for(auto pair : blocks_left_bracket_indices){
                board[pair.first][pair.second] = '[';
            }
            return;
        }

        if(board[current.first - 1][current.second] == '['){
            Q.push({current.first - 1, current.second});
            blocks_left_bracket_indices.insert({current.first - 1, current.second});
            board[current.first - 1][current.second] = 'V';
        }
        if(board[current.first - 1][current.second - 1] == '['){
            Q.push({current.first - 1, current.second - 1});
            blocks_left_bracket_indices.insert({current.first - 1, current.second - 1});
            board[current.first - 1][current.second - 1] = 'V';
        }
        if(board[current.first - 1][current.second + 1] == '['){
            Q.push({current.first - 1, current.second + 1});
            blocks_left_bracket_indices.insert({current.first - 1, current.second + 1});
            board[current.first - 1][current.second + 1] = 'V';
        }
    }

    for(auto pair : blocks_left_bracket_indices){
        board[pair.first][pair.second] = '[';
        swap(board[pair.first][pair.second], board[pair.first - 1][pair.second]);
        swap(board[pair.first][pair.second + 1], board[pair.first - 1][pair.second + 1]);
    }

    position.first -= 1;
}


void MoveLeft(vector<vector<char> >& board, pair<unsigned, unsigned>& position){
    unsigned index = position.second;
    
    if(board[position.first][position.second - 1] == '.'){
        position.second -= 1;
    }
    else{
        do{
            index--;
        }
        while(board[position.first][index] == '[' || board[position.first][index] == ']');

        if(board[position.first][index] == '.'){
            while(index != position.second){
                swap(board[position.first][index], board[position.first][index + 1]);
                index++;
            }
            position.second--;
        }
    }
}


void MoveRight(vector<vector<char> >& board, pair<unsigned, unsigned>& position){
    unsigned index = position.second;
    
    if(board[position.first][position.second + 1] == '.'){
        position.second += 1;
    }
    else{
        do{
            index++;
        }
        while(board[position.first][index] == '[' || board[position.first][index] == ']');

        if(board[position.first][index] == '.'){
            while(index != position.second){
                swap(board[position.first][index], board[position.first][index - 1]);
                index--;
            }
            position.second++;
        }
    }
}


void MoveDown(vector<vector<char> >& board, pair<unsigned, unsigned>& position){
    set<pair<unsigned, unsigned>, CompareDescending> blocks_left_bracket_indices;
    queue<pair<unsigned, unsigned>> Q;

    if(board[position.first + 1][position.second] == '.'){
        position.first += 1;
        return;
    }
    else if(board[position.first + 1][position.second] == '#' ){
        return;
    }
    else{
        if(board[position.first + 1][position.second] == '['){
            blocks_left_bracket_indices.insert({position.first + 1, position.second});
            board[position.first + 1][position.second] = 'V';
            Q.push({position.first + 1, position.second});
        }
        else{
            blocks_left_bracket_indices.insert({position.first + 1, position.second - 1});
            board[position.first + 1][position.second - 1] = 'V';
            Q.push({position.first + 1, position.second - 1});
        }
    }

    while(!Q.empty()){
        pair<unsigned, unsigned> current = Q.front();
        Q.pop();

        if(board[current.first + 1][current.second] == '#' || board[current.first + 1][current.second + 1] == '#'){
            // Revert all changes to board and return because no movement possible
            for(auto pair : blocks_left_bracket_indices){
                board[pair.first][pair.second] = '[';
            }
            return;
        }

        if(board[current.first + 1][current.second] == '['){
            Q.push({current.first + 1, current.second});
            blocks_left_bracket_indices.insert({current.first + 1, current.second});
            board[current.first + 1][current.second] = 'V';
        }
        if(board[current.first + 1][current.second - 1] == '['){
            Q.push({current.first + 1, current.second - 1});
            blocks_left_bracket_indices.insert({current.first + 1, current.second - 1});
            board[current.first + 1][current.second - 1] = 'V';
        }
        if(board[current.first + 1][current.second + 1] == '['){
            Q.push({current.first + 1, current.second + 1});
            blocks_left_bracket_indices.insert({current.first + 1, current.second + 1});
            board[current.first + 1][current.second + 1] = 'V';
        }
    }

    for(auto pair : blocks_left_bracket_indices){
        board[pair.first][pair.second] = '[';
        swap(board[pair.first][pair.second], board[pair.first + 1][pair.second]);
        swap(board[pair.first][pair.second + 1], board[pair.first + 1][pair.second + 1]);
    }

    position.first += 1;
}


uint64_t play(vector<vector<char>>& board, string commandline, pair<unsigned, unsigned> position){
    for(char command : commandline){
        // printBoard(board, position);
        switch(command){
            case '<':
                MoveLeft(board, position);
                break;
            case '>':
                MoveRight(board, position);
                break;
            case '^':
                MoveUp(board, position);
                break;
            case 'v':
                MoveDown(board, position);
                break;
            default:
                cout<<"Invalid command: "<<command<<endl;
                exit(2132);
                break;
        }
    }

    printBoard(board, position);


    uint64_t sum = 0;
    uint64_t rows = board.size();
    uint64_t cols = board[0].size();

    for(uint64_t i = 1; i < rows - 1; i++){
        for(uint64_t j = 2; j < cols - 2; j++){
            if(board[i][j] == '['){
                sum += i * 100 + j;
            }
        }
    }

    return sum;
}


tuple<vector<vector<char> >, string, pair<unsigned, unsigned> > readFile(string filename){
    ifstream file(filename);
    vector<vector<char> > board;
    string line;
    string command = "";
    pair<unsigned, unsigned> position;

    if(file.is_open()){

        while(getline(file, line)){
            if(line.empty()){
                break;
            }
            vector<char> row;
            for(char c : line){
                if(c == '@'){
                    position = {board.size(), row.size()};
                    row.push_back('.');
                    row.push_back('.');
                }
                else if(c == '#'){
                    row.push_back('#');
                    row.push_back('#');
                }
                else if(c == '.'){
                    row.push_back('.');
                    row.push_back('.');
                }
                else if(c == 'O'){
                    row.push_back('[');
                    row.push_back(']');
                }
                else{
                    cout<<"Invalid character in board: "<<c<<endl;
                    exit(2132);
                }
                
            }
            board.push_back(row);
        }
        
        while(getline(file, line)){
            command += line;
        }
    }
    else{
        cout<<"Unable to open file: "<<filename<<endl;
    }

    return {board, command , position};
}


int main(){
    auto input = readFile("input15.txt");
    cout<<play(get<0>(input), get<1>(input), get<2>(input))<<endl;
    printBoard(get<0>(input), get<2>(input));
 
    return 0;
}

