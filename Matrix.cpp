#include "Matrix.h"

#define PRINT_PARAM 0.1

// constructor
Matrix::Matrix(int rows, int cols){
  if (rows<=0 || cols<=0){
      std::cerr << "ERROR: Illegal values!\n";
      exit(EXIT_FAILURE);
  }
  else {
      dims.rows = rows;
      dims.cols = cols;
      mat = new float[rows*cols]{0};
  }
}
// default constructor
Matrix::Matrix(): Matrix (1,1){}

// copy constructor
Matrix::Matrix(const Matrix& m){
  dims.rows = m.dims.rows;
  dims.cols = m.dims.cols;
  mat = new float[dims.rows*dims.cols]{0};
  for (int i=0; i< dims.rows; i++){
      for (int j=0; j<dims.cols; j++){
          mat[i*dims.cols + j] = m(i,j);
      }
  }
}
//destructor
Matrix::~Matrix() {
  delete[] mat;
}

int Matrix::get_rows() const{
  return dims.rows;
}
int Matrix::get_cols() const{
  return dims.cols;
}

// transposes a matrix by changing the rows into columns
Matrix& Matrix::transpose(){
  // new transposed matrix
  float* new_mat = new float[dims.rows*dims.cols];
  for (int i=0; i<dims.rows; i++){
      for (int j=0; j<dims.cols; j++){
        // fill the new matrix row i with the elements in column i
        new_mat[j*dims.rows +i] = mat[i*dims.cols + j];
      }
  }
  delete[] mat;
  mat = new_mat;
  int temp = dims.rows;
  dims.rows = dims.cols;
  dims.cols = temp;
  return *this;
}
Matrix& Matrix::vectorize(){
  // turn matrix into vector (important for multiplication)
  dims.rows = dims.rows*dims.cols;
  dims.cols = 1;
  return *this;
}

void Matrix::plain_print () const {
  // print matrix contents
  for (int i=0; i<dims.rows; i++){
      for (int j=0; j<dims.cols; j++){
          std::cout << mat[i*dims.cols + j] << " ";
      }
      std::cout << "\n";
  }
}

float Matrix::norm() const{
  float res = 0;
  for (int i=0; i<dims.rows; i++){
      for (int j=0; j<dims.cols; j++){
        // sum of each row element raised to the power of two
          res += mat[i*dims.cols + j]*mat[i*dims.cols + j];
        }
    }
    // under square root
  res = std::sqrt(res);
  return res;
}

Matrix Matrix::dot(const Matrix& b) const{
  // dot product of two matrices
    if (dims.rows != b.get_rows() || dims.cols != b.get_cols()){
        std::cerr << "ERROR: Illegal matrix dot product\n";
        exit(EXIT_FAILURE);
    }

    Matrix res(dims.rows, dims.cols);

  for (int i=0; i<dims.rows; i++){
      for (int j=0; j<dims.cols; j++){
        // multiply (this) matrix by the inputed matrix and return the result
          res(i,j) = mat[i*dims.cols + j]*b(i,j);
        }
    }
  return res;
}
// adds two matrices and returns by value because it's a const
Matrix Matrix::operator+(const Matrix& b) const{
    if (dims.rows != b.get_rows() || dims.cols != b.get_cols()){
        std::cerr << "ERROR: Illegal matrix addition\n";
        exit(EXIT_FAILURE);
    }
    Matrix res(dims.rows, dims.cols);

  for (int i=0; i< dims.rows; i++){
      for (int j = 0; j < dims.cols; j++){
        // add (this) matrix to the inputed matrix and return the result
          res(i,j) = mat[i*dims.cols + j] + b(i,j);
        }
    }
  return res;
}
// element at this index (return by reference to allow us to change the value)
float& Matrix::operator()(int i, int j){
  if (i>= dims.rows || j>= dims.cols){
      std::cerr<< "ERROR: illegal index\n";
      exit(EXIT_FAILURE);
    }
  if (i<0 || j<0){
      std::cerr<< "ERROR: illegal index\n";
      exit(EXIT_FAILURE);
    }
  return mat[i*dims.cols + j];
}
// element at this index return by value
float Matrix::operator()(int i, int j) const{
  if (i>= dims.rows || j>= dims.cols){
      std::cerr<< "ERROR: illegal index\n";
      exit(EXIT_FAILURE);
    }
  if (i<0 || j<0){
      std::cerr<< "ERROR: illegal index\n";
      exit(EXIT_FAILURE);
    }
  return mat[i*dims.cols + j];
}
// make a matrix equal to this matrix
Matrix& Matrix::operator=(const Matrix& b){
  dims.rows = b.get_rows();
  dims.cols = b.get_cols();

  // create a new matrix a copy the contents of the other matrix to it
  delete[] mat;
  mat = new float[dims.rows*dims.cols];
  for (int i=0; i<dims.rows; i++){
      for (int j = 0; j < dims.cols; j++){
          mat[i*dims.cols + j] = b(i,j);
        }
    }
  return *this;
}
// multiply by scalar to the right
Matrix Matrix::operator*(float c){
  Matrix res(dims.rows, dims.cols);

  for (int i=0; i< dims.rows; i++){
      for (int j = 0; j < dims.cols; j++){
          res(i,j) = c*mat[i*dims.cols + j];
        }
    }
  return res;
}
// multiply a different matrix object by a scalar (to the right)
Matrix operator*(const Matrix& m, float c){
  Matrix res(m.get_rows(), m.get_cols());
  res = res * c;
  return res;
}
// multiply a different matrix object by a scalar (to the left)
Matrix operator*(float c, const Matrix& m){
  Matrix res(m.get_rows(), m.get_cols());
  res = res * c;
  return res;
}
// matrix multiplication
Matrix Matrix::operator*(const Matrix& m){
  // the condition for performing matrix multiplication
    if (dims.cols != m.get_rows()){
        std::cerr << "ERROR: illegal matrix multiplication\n";
        exit(EXIT_FAILURE);
    }
    int rows = dims.rows;
  int cols = m.get_cols();
  Matrix res(rows, cols);
// for each row
  for (int i=0; i<dims.rows; i++){
    // for each col
      for (int j=0; j<cols; j++){
          float element = 0;
          for (int k=0; k<dims.cols; k++){
            // go through the columns of the second matrix and multiply
            // their elements by the elements of the rows in the first matrix
            // and sum the result to the element in the new matrix
              element += mat[i*dims.cols + k]*m(k,j);
            }
          res(i,j) = element;
        }
    }
  return res;
}
// increase this by matrix b
Matrix& Matrix::operator+=(const Matrix& b){
  if (dims.rows != b.get_rows() || dims.cols != b.get_cols()){
      std::cerr << "ERROR: Illegal matrix addition\n";
      exit(EXIT_FAILURE);
    }
  // for each element
  for (int i=0; i< dims.rows; i++){
      for (int j = 0; j < dims.cols; j++){
        // sum the element from this and b into this
          mat[i*dims.cols + j] = mat[i*dims.cols + j] + b(i,j);
        }
    }
  return *this;
}
// element at this index (return by reference to allow us to change the value)
float& Matrix::operator[](int i){
  if (i<0 || i>=dims.rows*dims.cols) {
      std::cerr << "ERROR: illegal value\n";
      exit(EXIT_FAILURE);
    }
  return mat[i];
}
// element at this index (return by value)
float Matrix::operator[](int i) const{
  if (i<0 || i>=dims.rows*dims.cols) {
      std::cerr << "ERROR: illegal value\n";
      exit(EXIT_FAILURE);
    }
  return mat[i];
}
// print representation of the digit
std::ostream& operator<<(std::ostream& out, const Matrix& m){
  for (int i=0; i<m.get_rows(); i++){
      for (int j=0; j<m.get_cols(); j++){
          if (m(i,j) > PRINT_PARAM){
              out << "**";
            }
          else out << "  ";
        }
      out << "\n";
    }
  return out;
}
// input from binary file into a matrix object
std::istream& operator>>(std::istream& in, Matrix& m){
  int rows = m.get_rows();
  int cols = m.get_cols();
  // temp to hold the input
  float* temp = new float[rows*cols];
  // read into temp the amount of floats of rows*cols
  in.read ((char*) temp, rows*cols*sizeof(float ));
  // if reading failed
  if (in.fail()){
      std::cerr << "ERROR: failed to read input\n";
      delete[] temp;
      exit(EXIT_FAILURE);
  }
  // copy temp into the matrix
  for (int i=0; i<rows*cols; i++) {
      m[i] = temp[i];
  }
  // free memory
  delete[] temp;
  return in;
}