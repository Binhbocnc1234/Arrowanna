#include <iostream>
#include <bits/stdc++.h>
#include <thread>
#include <vector>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#define RED_TEXT "\x1B[31m"
#define RESET_TEXT "\x1B[0m"
#else
#define RED_TEXT "\033[31m"
#define RESET_TEXT "\033[0m"
#endif

using namespace std;

vector<string> errors = {
    "undefined reference to `SDL_Init'",
    "undefined reference to `SDL_CreateWindow'",
    "undefined reference to `SDL_CreateRenderer'",
    "'SDL_Window' was not declared in this scope",
    "'SDL_Renderer' was not declared in this scope",
    "fatal error: SDL2/SDL.h: No such file or directory",
    "expected ';' before 'return'",
    "stray '\\342' in program",
    "missing terminating '\"' character",
    "invalid conversion from 'int' to 'const char*'",
    "'nullptr' was not declared in this scope",
    "'cout' was not declared in this scope",
    "expected primary-expression before ';' token",
    "expected declaration before '}' token",
    "invalid operands of types 'const char [6]' and 'int' to binary 'operator+'",
    "'SDL_QUIT' was not declared in this scope",
    "too many arguments to function 'int main()'",
    "narrowing conversion from 'double' to 'int' inside { } is ill-formed",
    "control reaches end of non-void function",
    "'main' must return 'int'",
    "cannot convert 'std::string' to 'char*' in assignment",
    "'int SDL_RenderPresent(SDL_Renderer*)' redeclared as different kind of symbol",
    "multiple definition of `main'",
    "'SDL_CreateTextureFromSurface' was not declared in this scope",
    "invalid use of incomplete type 'struct SDL_Texture'",
    "'SDL_FreeSurface' was not declared in this scope",
    "pointer type mismatch in conditional expression",
    "error: expected ')' before ';' token",
    "error: 'for' loop initial declarations are only allowed in C99 mode",
    "error: cannot pass objects of non-trivially-copyable type 'std::string' through '...'"
};

// Simulate compilation errors appearing endlessly
void playGame() {
    system("cls"); // Clear screen (Windows), use "clear" for Linux/macOS
    cout << "g++ -Wall -I src/include -c main.cpp -o main.o\n" << endl;
    this_thread::sleep_for(chrono::seconds(2)); // Fake compilation time

    string filePath = "C:\\My program\\Games\\Nemo Escape\\main.cpp";
    
    srand(time(0));
    int count = 0;

    while (true) { // Infinite loop
        int line = rand() % 500 + 1;  // Random line number (1-500)
        int column = rand() % 80 + 1; // Random column number (1-80)

        cout << filePath << ":" << line << ":" << column << ": "
             << RED_TEXT << "error: " << RESET_TEXT
             << errors[count % errors.size()] << endl;

        count++;
        this_thread::sleep_for(chrono::milliseconds(20)); // Random delay

        // Every 20 errors, print a new line for comedic effect
        if (count % 20 == 0) {
            cout << "\n--- Compilation still going... Please send help. ---\n" << endl;
            this_thread::sleep_for(chrono::milliseconds(50));
            // break;
        }
    }
}

int main() {
    playGame();
    return 1;
}
