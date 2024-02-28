#include "../lib/s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(0, 0) {}
S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 0 || cols < 0 || (rows == 0 && cols != rows)) {
    throw std::invalid_argument(
        "The dimensionality of the matrix cannot be negative!");
  } else {
    rows_ = rows;
    cols_ = cols;
    matrix_ = {new double* [rows] {}};
    if (!matrix_) {
      throw std::invalid_argument("Memory allocation error");
    } else {
      for (int i = 0; i < rows; i++) {
        matrix_[i] = {new double[cols]{}};
      }
    }
  }
}
S21Matrix::S21Matrix(const S21Matrix& other) {
  if (other.rows_ < 0 && other.cols_ < 0) {
    throw std::invalid_argument(
        "The dimensionality of the matrix cannot be negative!");
  } else {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = {new double* [rows_] {}};
    if (!matrix_) {
      throw std::invalid_argument("Memory allocation error");
    } else {
      for (int i = 0; i < rows_; i++) {
        matrix_[i] = {new double[cols_]{}};
      }
    }
    for (int ifl = 0; ifl < cols_; ifl++) {
      for (int i = 0; i < rows_; i++) {
        matrix_[ifl][i] = other.matrix_[ifl][i];
      }
    }
  }
}
S21Matrix::S21Matrix(S21Matrix&& other) {
  if (other.rows_ < 0 && other.cols_ < 0) {
    throw std::invalid_argument(
        "The dimensionality of the matrix cannot be negative!");
  } else {
    matrix_ = other.matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    other.matrix_ = nullptr;
    other.cols_ = 0;
    other.rows_ = 0;
  }
}
S21Matrix::~S21Matrix() {
  if (matrix_) {
    matrix_ = nullptr;
    cols_ = 0;
    rows_ = 0;
  }
}
