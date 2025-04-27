#include <iostream>
#include <stack>
#include <string>

const int memSize = 100;

std::string interpret_bf(const std::string &code, const std::string input) {
  int memory[memSize] = {0};
  int pointer = 0;
  int inputPointer = 0;
  bool dontExecute = false;
  std::stack<int> loopStack;

  std::string output;

  for (int i = 0; i < code.length(); ++i) {
    if (dontExecute == true && code[i] != ']') {
      continue;
    }
    if (!loopStack.empty() && i == code.length() - 1) {
      std::cout << "unmatched brackets - '[' at position " << loopStack.top();
      return 0;
    }
    switch (code[i]) {
    case '[':
      if (memory[pointer] == 0) {
        dontExecute = true;
      }
      loopStack.push(i);
      break;
    case ']':
      if (loopStack.empty()) {
        std::cout << "unmatched brackets - ']' at position " << i;
        return 0;
      }
      if (memory[pointer] != 0) {
        i = loopStack.top();
      } else {
        loopStack.pop();
      }
      dontExecute = false;
      break;

    case '>':
      if (pointer < memSize - 1) {
        pointer++;
      } else {
        std::cout << "memory exceeded";
        return 0;
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
    default:
      break;
    }
  }

  /*for (auto i : memory) {
      std::cout << i << ' ';
  }*/
  return output;
}
