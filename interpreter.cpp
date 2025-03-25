#include <iostream>
#include <string>

const int memSize = 100;

int main(){    
    int memory[memSize] = {0};
    int pointer = 0;

    std::string input;
    std::cin >> input;
    
    for (char i : input){
        if (i == '>' && pointer < memSize){
            pointer++;
        }
        else if (i == '<' && pointer > 0){
            pointer--;
        }
        else if (i == '+'){
            memory[pointer]++;
        }
        else if (i == '-'){
            memory[pointer]--;
        }
        else if (i == '.'){
            std::cout << (char) memory[pointer]; // TODO: convert to text value using ascii
        }
    }
    return 0;
}