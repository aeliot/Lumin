#ifndef __stripper__
#define __stripper__

#include "../arduPi/arduPi.h"

class Strip {
 public:
  
 private:

}

class Color {
 public:
  Color Color();
  Color Color(unsigned char, unsigned char, unsigned char);
  unsigned char red;
  unsigned char green;
  unsigned char blue;
}

class Signal {
 public:

  typedef enum {
    CLEAR = 0x00,
    PUSH = 0x01,
    CUE = 0x02,
    BRIGHT = 0x03,
    SOLID = 0x04,
    CYCLE = 0x10,
    FADE = 0x11,
    PULSE = 0x12
  }OpCode;

  void setOp(OpCode);
  void clear();
  void push(Color);
  void cue(Color);
  void bright(unsigned char);
  void solid(Color);
  void startCycle(int);
  void startFade(int);
  void startPulse(int);
  void stopCycle();
  void stopFade();
  void stopPulse();
 privat:
  unsigned char sig[4];
}

#endif
