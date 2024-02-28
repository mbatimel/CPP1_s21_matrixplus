#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

#define SUCCESS 1
#define FAILURE 0
#define EPSILON 10e-7
class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

  bool check_matrix(const S21Matrix& other);
  void replacement(S21Matrix* copy, int dimention, int v, int row);
  int noughts_handling(S21Matrix* copy, double* result, int dimention);
  void fill_minor(int dimention, S21Matrix* A, int i, int ii, S21Matrix* minor);
  void createmulmatrix(S21Matrix* matrix, const S21Matrix& other);

 public:
  int get_rows() const;
  int get_cols() const;
  void set_size(int new_rows, int new_cols);
  /* КОНСТРУКТОР И ДЕКОСТРУКТОР КЛАССА */
  S21Matrix();  // Базовый конструктор, инициализирующий матрицу некоторой
                // заранее заданной размерностью.
  S21Matrix(int rows, int cols);  // Параметризированный конструктор с
                                  // количеством строк и столбцов.
  S21Matrix(const S21Matrix& other);  // Конструктор копирования.
  S21Matrix(S21Matrix&& other);  // конструктор переноса
  ~S21Matrix();                  // деконструктор
  /* ОПЕРАЦИИ НАД МАТРИЦАМИ */

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
  /* ОПЕРАТОРЫ */
  S21Matrix& operator=(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator*(const double num) const;
  S21Matrix& operator*=(const double num);
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix& operator*=(const S21Matrix& other);
  double& operator()(int i, int j);
};
