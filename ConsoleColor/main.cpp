#include <iostream>
#include <Windows.h>
#include <cstdlib>
#define DEFAULT_COLOR FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

int ColorSwitch(int num) { // Simple switcher for colors

    switch (num) {
    case 0:
        return FOREGROUND_RED; // Set text color to bright red
    case 1:
        return FOREGROUND_BLUE;
    case 2:
        return FOREGROUND_GREEN;
    case 3:
        return DEFAULT_COLOR;
    }

    return DEFAULT_COLOR;
}

void SetConsoleTextColor(int color) { // Change color of symbols

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main() {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    COORD startPos = consoleInfo.dwCursorPosition;
    SetConsoleCursorPosition(hConsole, startPos); // Move cursor to the start pos
    SetConsoleTextColor(DEFAULT_COLOR);

    int width, height;
    std::cout << "Input height: "; std::cin >> height;
    std::cout << "Input width: "; std::cin >> width;
    std::cout << std::endl;

    int** numArray = new int* [height];
    std::srand(static_cast<unsigned int>(std::time(0)));
    for (int i = 0; i < height; ++i) {
        numArray[i] = new int[width];
        for (int j = 0; j < width; ++j) {

            numArray[i][j] = std::rand() % 2;
            //SetConsoleTextColor(ColorSwitch(rand() % 4) | FOREGROUND_INTENSITY); // Only default colors with intensity
            //SetConsoleTextColor(ColorSwitch(rand() % 4)); // without indensity

            SetConsoleTextColor(ColorSwitch(rand() % 4) | FOREGROUND_INTENSITY); // Combinations of default colors
            std::cout << numArray[i][j] << " ";
        }
        SetConsoleTextColor(DEFAULT_COLOR); // Set default color and output it
        std::cout << std::endl;
    }

    // Memory will be cleared automatically because of the end of the program :)
    // but if you wanna do smth else in this code you should clear it using delete
    return 0;
}