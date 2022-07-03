//Activation.h


#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    RELU,
    SOFTMAX
};

// Insert Activation class here...
class Activation{
 private:
  ActivationType type;
 public:
  Activation(ActivationType type);
  ActivationType get_activation_type() const;
  Matrix operator()(const Matrix& mat) const;
};

#endif //ACTIVATION_H
