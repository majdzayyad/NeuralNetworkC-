//
// Created by yuval on 01-Oct-21.
//

#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

// Insert Dense class here...
class Dense{
 private:
  Matrix weights;
  Matrix bias;
  ActivationType act;
 public:
  Dense(Matrix weights, Matrix bias, ActivationType act);
  Matrix get_weights() const;
  Matrix get_bias() const;
  Activation get_activation() const;
  Matrix operator()(Matrix& Input);
};


#endif //DENSE_H
