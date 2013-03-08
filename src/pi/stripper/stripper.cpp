#include "stripper.h"
#include "../arduPi/arduPi.h"

using namespace std;

Strip::Strip(int size){
  //setup the pi interface
  Serial.begin(9600);

  this.length = size;
}

void Strip::send(Signal signal){
  for(int i = 0; i < 4; i++){
    Serial.print(signal.sig[i]);
  }
}

void Strip::stackUp(Signal signal){
  this.stack.push(signal);
}

void Strip::sendStack(){
  while(!this.stack.empty()){
    send(this.stack.pop());
  }
}

Color::Color(){
  red = 0;
  green = 0;
  blue = 0;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b){
  red = r;
  green = g;
  blue = g;
}

void Signal::setOp(OpCode){
  sig[0] = OpCode;
}

void Signal::setColor(Color color){
  sig[1] = color.red;
  sig[2] = color.green;
  sig[3] = color.blue;
}

void Signal::clear(){
  setOp(CLEAR);
  sig[1] = 0;
  sig[2] = 0;
  sig[3] = 0;
}

void Signal::push(Color color){
  setOp(PUSH);
  setColor(color);
}

void Signal::cue(Color color){
  setOp(CUE);
  setColor(color);
}

void Signal::bright(unsigned char level){
  setOp(BRIGHT);
  sig[1] = 0;
  sig[2] = 0;
  sig[3] = level;
}

void Signal::solid(Color color){
  setOp(SOLID);
  setColor(color);
}

