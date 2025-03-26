#include <iostream>
#include <string>

const int memSize = 100;


int main(){    
    int memory[memSize] = {0};
    int pointer = 0;
    int inputPointer = 0;
    int loopstart= 0;

    std::string code;
    std::string input;
    std::string output;
    std::cin >> code;
    std::cin >> input;
    
    for (int i = 0; i < code.length(); ++i){
        switch (code[i]) {
            case '>':
                if (pointer < memSize - 1) {
                    pointer++;
                }
                break;
            case '<':
                if (pointer > 0) {
                    pointer--;
                }
                break;
            case '+':
                memory[pointer]++;
                break;
            case '-':
                memory[pointer]--;
                break;
            case '.':
                output += static_cast<char>(memory[pointer]);
                break;
            case ',':
                if (inputPointer < input.length()) {
                    memory[pointer] = static_cast<int>(input[inputPointer]);
                    inputPointer++;
                }
                break;
            // prevent ] before [ and check if current cell is 0 before exeucting
            case '[':
                loopstart = i;
                break;
            case ']':
                if (memory[pointer] != 0){
                    i = loopstart;
                }
                break;
            default:
                // Ignore any other characters
                break;
        }
    }
    
    for (auto i : memory) {
        std::cout << i << ' ';
    }
    std::cout << "\n" << "output: " << output;
    return 0;
}