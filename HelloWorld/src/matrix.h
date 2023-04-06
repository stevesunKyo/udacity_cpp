#include <vector>

using std::vector;

class mat{
  // class for a matrix and matrix operation used in computation. 
  //it can be also used as 1D vector if we set _col or _row to 1.
  
  public:
  mat(vector<vector<float>> data);  // constructor
  ~mat(); // destructor
  mat(const mat &source); // copy constructor
  mat(mat &&source); // move constructor
  mat& operator=(mat &&source); // copy assignment operator
  
  mat dot(mat B); // calculate dot product of A*B, when B is a matrix
  vec dot(vec B); // calculate dot product of A*B, when B is a vector
    
    
  mat operator+ (mat m1, mat m2); // element-wise plus
  mat operator- (mat m1, mat m2); // element-wise substract
  mat operator* (mat m1, mat m2); // element-wise multiply
  mat operator/ (mat m1, mat m2); // element-wise divide
    
    
  private:
  int _col; // row number
  int _row; // column number 
  vector<vector<float>> _data; // matrix data
};

  