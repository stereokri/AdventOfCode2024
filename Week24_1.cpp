#include <iostream>
#include <unordered_map>
#include <fstream>
#include <list>

using namespace std;

bool logicalOperator(char op, bool a, bool b){
    if(op == 'A'){
        return a && b;
    }
    else if(op == 'O'){
        return a || b;
    }
    else if(op == 'X'){
        return a ^ b;
    }
    else{
        cout<<"Invalid operator\n"<<endl;
        exit(1);
        return false;
    }
}

bool evaluateZi(string z, unordered_map<string, tuple<int8_t, string, char, string> >& M){
    if(get<0>(M[z]) != -1){
        return get<0>(M[z]);
    }
    else{
        get<0>(M[z]) = logicalOperator(get<2>(M[z]), evaluateZi(get<1>(M[z]), M), evaluateZi(get<3>(M[z]), M));
        return get<0>(M[z]);
    }
}

unordered_map<string, tuple<int8_t, string, char, string> > readFile(string filename){
    ifstream file(filename);
    string allocation;
    string expression;

    unordered_map<string, tuple<int8_t, string, char, string> > M;

    
    while(1){
        getline(file, allocation);
        if(allocation.size() <= 0) break;
        M[allocation.substr(0, 3)] = {stoi(allocation.substr(5)), "", ' ', ""};
    }
    
    while(getline(file, expression)){
        M[expression.substr(expression.size() - 3)] = {-1, expression.substr(0, 3), expression[4], expression.substr(expression.size() - 10, 3) }; 
    }

    return M;
}

uint64_t evaluateNumber(unordered_map<string, tuple<int8_t, string, char, string> >& M){
    string zi = "z00";
    uint8_t count = 0;
    uint64_t result = 0;
    list<bool> binaryNr;

    while(M.find(zi) != M.end()){
        binaryNr.push_front(evaluateZi(zi, M));
        count++;
        if(count < 10){
            zi = "z0" + to_string(count);
        }
        else{
            zi = "z" + to_string(count);
        }
    }


    for(auto digit : binaryNr){
        result += pow(2, --count)*digit;
    }
    return result;
}

int main(){
    unordered_map<string, tuple<int8_t, string, char, string> > M = readFile("input24.txt");
    cout<<evaluateNumber(M);
    return 0;
}
