#include <iostream>
#include <vector>
#include <memory>
#include<string>

using namespace std;
int main () {


    string command;

    while (cin >> command) {
    if (command == "game" ) {
        string playerOne, playerTwo;
        cin >> playerOne >> playerTwo;

    }
    else if (command == "resign") {

    }
    else if (command == "move") {
        string oldPos, newPos;
        cin >> oldPos >> newPos;
        //ignore if no pawn promotion is happening
        char pawnProm;
        cin >> pawnProm;

    }
    else if (command == "setup") {
        string setupCommand;
        while(cin >> setupCommand) {
            if(setupCommand == "+"){
                string addPos;
                cin >> addPos;

            }
            else if(setupCommand == "-"){
                string removePos;
                cin >> removePos;

            }
            else if(setupCommand == "="){
                string colour;
                cin >> colour;

            }
            else if(setupCommand == "done"){
                break;
            }
        }
    }
  }
}
