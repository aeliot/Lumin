#include "stripper.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
  string input;
  Strip lights(32);
  while(!cin.eof() && !cin.fail()){
    cin >> input;
    if(input == "quit" || input == "exit" || input == "close"){
      break;
    } else if(input == "solid"){
      cin >> input;
      Color color;
      Signal sig;
      if(input == "red"){
	color.red = 0xff;
      } else if(input == "green"){
	color.green = 0xff;
      } else if(input == "blue"){
	color.blue = 0xff;
      } else {
	cerr << endl << "WHAT THE FUCK WAS THAT, I WANTED A COLOR" << endl;
      }
      sig.solid(color);
      lights.send(sig);
    } else if(input == "show"){
      Signal sig;
      sig.setOp(Signal::SHOW);
      lights.send(sig);
    }
  }
  return 0;
}
