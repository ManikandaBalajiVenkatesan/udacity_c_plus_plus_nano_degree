#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "bat.h"

class Controller {
 public:
  void HandleInput(bool &running, Bat &bat) const;

 private:

};

#endif