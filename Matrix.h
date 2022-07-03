// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>

/**
 * @struct MatrixDims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and in main.cpp.
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

// Insert Matrix class here...
class Matrix{
 private:
  matrix_dims dims;
  float* mat;
 public:

  Matrix(int rows, int cols); // v

  Matrix(const Matrix& m); // v

  Matrix();

  ~Matrix(); // v

  int get_rows() const; // v

  int get_cols() const; // v

  Matrix& transpose(); // v

  Matrix& vectorize(); // v

  void plain_print() const; // v

  float norm() const; // v

  Matrix dot(const Matrix& b) const;

  Matrix operator+(const Matrix& b) const; // v

  float& operator()(int i, int j); // v

  float operator()(int i, int j) const; // v

  Matrix& operator=(const Matrix& b); // v

  Matrix operator*(float c); // v

  Matrix operator*(const Matrix& m); //v

  friend Matrix operator*(const Matrix& m, float c); // v

  friend Matrix operator*(float c, const Matrix& m);

  Matrix& operator+=(const Matrix& b); // v

  float operator[](int i) const; // v

  float& operator[](int i); // v

  friend std::ostream& operator<< (std::ostream& out, const Matrix& m);

  friend std::istream& operator>> (std::istream& in, Matrix& m);
};

#endif //MATRIX_H
