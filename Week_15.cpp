#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <tuple>



using namespace std;

void printBoard(vector<vector<char> >& board){
    for(unsigned i = 0; i < board.size(); i++){
        for(unsigned j = 0; j < board[i].size(); j++){
            cout<<char(board[i][j]);
        }
        cout<<endl;
    }
    cout<<endl;
}


void MoveLeft(vector<vector<char> >& board, pair<unsigned, unsigned>& position){
    unsigned index = position.second;
    
    if(board[position.first][position.second - 1] == '.'){
        position.second -= 1;
    }
    else{
        while(board[position.first][--index] == 'O') {}

        if(board[position.first][index] == '.'){
            board[position.first][index] = 'O';
            board[position.first][position.second - 1] = '.';
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
        while(board[position.first][++index] == 'O') {}

        if(board[position.first][index] == '.'){
            board[position.first][index] = 'O';
            board[position.first][position.second + 1] = '.';
            position.second++;
        }
    }
}


void MoveUp(vector<vector<char> >& board, pair<unsigned, unsigned>& position){
    unsigned index = position.first;
    
    if(board[position.first - 1][position.second] == '.'){
        position.first -= 1;
    }
    else{
        while(board[--index][position.second] == 'O') {}

        if(board[index][position.second] == '.'){
            board[index][position.second] = 'O';
            board[position.first - 1][position.second] = '.';
            position.first--;
        }
    }
}


void MoveDown(vector<vector<char> >& board, pair<unsigned, unsigned>& position){
    unsigned index = position.first;
    
    if(board[position.first + 1][position.second] == '.'){
        position.first += 1;
    }
    else{
        while(board[++index][position.second] == 'O') {}

        if(board[index][position.second] == '.'){
            board[index][position.second] = 'O';
            board[position.first + 1][position.second] = '.';
            position.first++;
        }
    }
}



uint64_t play(vector<vector<char>>& board, string commandline, pair<unsigned, unsigned> position){
    for(char command : commandline){
        // printBoard(board);
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
                exit(1);
                break;
        }
    }

    // printBoard(board);


    uint64_t sum = 0;

    for(uint64_t i = 1; i < board.size() - 1; i++){
        for(uint64_t j = 1; j < board[i].size() - 1; j++){
            if(board[i][j] == 'O'){
                sum += i * 100 + j;
            }
        }
    }

    return sum;
}


tuple<vector<vector<char> >, string, pair<unsigned, unsigned> > readFile(string filename){
    ifstream file(filename);
    uint64_t counter = 0;
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
                    c = '.';
                }
                row.push_back(c);
            }
            board.push_back(row);
        }
        
        while(getline(file, line)){
            counter++;
            command += line;
        }
        cout<<counter<<endl;
    }
    else{
        cout<<"Unable to open file: "<<filename<<endl;
    }

    return {board, command , position};
}





int main(){
    auto input = readFile("input15.txt");

    cout<<play(get<0>(input), get<1>(input), get<2>(input))<<endl;

    return 0;


}

