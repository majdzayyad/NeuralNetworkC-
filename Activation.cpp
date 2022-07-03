#include "Activation.h"

Activation::Activation(ActivationType type){
  this->type = type;
}

ActivationType Activation::get_activation_type() const{
  return this->type;
}
// performs activation on vector
Matrix Activation::operator()(const Matrix& mat) const{
  if (this->type == RELU){
    Matrix res(mat);
    int rows = res.get_rows();
 // relu activation condition
    for (int i=0; i<rows; i++){
      if (res(i,0) <= 0) res(i,0) = 0;
    }
    return res;
  }

  else {
    Matrix res(mat);
    int rows = res.get_rows();
    float divider = 0;
  //sum the contents of each row raised to an exponent into divider
    for (int i=0; i<rows; i++){
      divider += std::exp(res(i,0));
      res(i,0) = exp(res(i,0));
    }
    // devide the matrix by the scalar devider
    res = res * (1/divider);
    return res;
  }
}