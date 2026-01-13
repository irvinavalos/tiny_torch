#ifndef NN_H
#define NN_H

#include "matrix.h"

void Sigmoid();
void ReLu();

class NeuralNetwork {
  public:
    NeuralNetwork() : x_(Matrix()) {};

  private:
    Matrix x_;
};

#endif // NN_H
