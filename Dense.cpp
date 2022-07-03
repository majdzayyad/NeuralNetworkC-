#include "Dense.h"

Dense::Dense(Matrix weights, Matrix bias, ActivationType act){
  this->weights = weights;
  this->bias = bias;
  this->act = act;
}
Matrix Dense::get_weights() const{
  return this->weights;
}
Matrix Dense::get_bias() const{
  return this->bias;
}
// returns an activation class based on the current activation type
Activation Dense::get_activation() const{
  Activation activ(this->act);
  return activ;
}
// performs activtion on input matrix
Matrix Dense::operator()(Matrix& Input){
  Matrix res;
  Input.vectorize(); // turn input into vector for the activation function
  Activation activ(this->act);
  res = weights*Input;
  res += bias;
  res = activ(res); // perform activation
  return res;
}