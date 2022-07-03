#include "MlpNetwork.h"
#define MAT_NUM 4
#define DIGIT_COUNT 10

MlpNetwork::MlpNetwork (Matrix weights[], Matrix biases[]){
 // construct weights and biases
  Matrix w1(weights[0]);
  Matrix w2(weights[1]);
  Matrix w3(weights[2]);
  Matrix w4(weights[3]);
  Matrix b1(biases[0]);
  Matrix b2(biases[1]);
  Matrix b3(biases[2]);
  Matrix b4(biases[3]);
  // declare them in the private fields
  this->w1 = w1;
  this->w2 = w2;
  this->w3 = w3;
  this->w4 = w4;
  this->b1 = b1;
  this->b2 = b2;
  this->b3 = b3;
  this-> b4 = b4;
}
// neural network implementation on a digit image
digit MlpNetwork::operator()(Matrix& number) const{
  // start with image
  Dense layer1(w1, b1, RELU);
  Matrix r1(number);
  r1 = layer1(number);

  Dense layer2(w2, b2, RELU);
  Matrix r2(r1);
  r2 = layer2(r1);

  Dense layer3(w3, b3, RELU);
  Matrix r3(r2);
  r3 = layer3(r2);
  // now performing the last activation function
  Dense layer4(w4, b4, SOFTMAX);
  Matrix r4(r3);
  r4 = layer4(r3);

  // get the index with the highest probability
  int max_index = 0;
  for (int i=0; i<DIGIT_COUNT; i++){
    max_index = r4[max_index]<r4[i] ? i:max_index;
  }
  // return it
  digit res;
  res.value = max_index;
  res.probability = r4[max_index];
  return res;
}