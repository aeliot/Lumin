#ifndef __stripper__
#define __stripper__

#include "../arduPi/arduPi.h"
#include <queue>

using namespace std;

class Color {
 public:
  Color();
  Color(unsigned char, unsigned char, unsigned char);
  unsigned char red;
  unsigned char green;
  unsigned char blue;
};

class Signal {
 public:
  
  typedef enum {
    CLEAR = 0x00,
    PUSH = 0x01,
    CUE = 0x02,
    BRIGHT = 0x10,
    SOLID = 0x03,
    CYCLE = 0x21,
    CYCLE_STOP = 0x31,
    FADE = 0x22,
    FADE_STOP = 0x32,
    PULSE = 0x23,
    PULSE_STOP = 0x33,
    SHOW = 0x40
  }OpCode;

  void setOp(OpCode);
  void setColor(Color);
  void clear();
  void push(Color);
  void cue(Color);
  void bright(unsigned char);
  void solid(Color);
  /*
  void startCycle(int);
  void startFade(int);
  void startPulse(int);
  void stopCycle();
  void stopFade();
  void stopPulse();
  */
  unsigned char sig[4];
};

class Strip {
 public:
  Strip(int);
  void send(Signal);
  void stackUp(Signal);
  void sendStack();
 private:
  int length;
  queue<Signal> stack;
};

#endif
