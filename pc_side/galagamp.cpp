#include "serialport.h"
#include <iostream>
#include <string>
#define WIDTH 320
#define HEIGHT 480
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

string coordinate_to_serial(int x, int y, int is_fire) {
    string output = "";
    output.append("C ");
    output.append(to_string(is_fire));
    output.append(" ");
    output.append(to_string(x));
    output.append(" ");
    output.append(to_string(y));
    output.append("\n");
    return output;
    
}

int constrain(int x, int start, int end) {
    if(x <= start) {
        return start;
    }
    else if(x >= end) {
        return end;
    }
    return x;
}
int main(int argc, char *argv[]) {
    SerialPort Serial(argv[1]);
    int x,y, is_fire;
    while(1) {
        string input = Serial.readline();
        cout << input << endl;
        //int c = getchar();
        if(input[0] == 'R') {
            Serial.writeline("A\n");
            x = WIDTH/2;
            y = 80;
            is_fire = 0;
        }
        if(input[0] == 'A') {
                cout << "jump to next phase" << endl;
                string output = coordinate_to_serial(x, y, is_fire);
                cout << output << endl;
                Serial.writeline(output);
                // switch(c){
                // case KEY_LEFT:
                //     x -= 2;
                // break;
                // case KEY_RIGHT:
                //     x += 2;
                // }
        }
        
    }
    return 0;
}
    
