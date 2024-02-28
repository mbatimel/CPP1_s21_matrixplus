#include "../lib/s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  int result = true;
  if (!this->check_matrix(other)) {
    result = false;
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        if (fabs(this->matrix_[i][j] - other.matrix_[i][j]) > 1e-07) {
          result = false;
          break;
        }
      }
    }
  }
  return result;
}
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (!this->check_matrix(other)) {
    throw std::invalid_argument(
        "The dimensionality of the matrix cannot be negative!");
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
}
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (!this->check_matrix(other)) {
    throw std::invalid_argument(
        "The dimensionality of the matrix cannot be negative!");
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}
void S21Matrix::MulNumber(const double num) {
  if (!this->matrix_ || this->cols_ < 1 || this->rows_ < 1) {
    throw std::invalid_argument("Error when working with the matrix");
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] *= num;
      }
    }
  }
}
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->matrix_ == nullptr && other.matrix_ == nullptr &&
      this->cols_ <= 0 && other.rows_ <= 0 && this->rows_ <= 0) {
    throw std::invalid_argument(
        "One or both matrices are not initialized properly.");
  } else if (this->cols_ != other.rows_) {
    throw std::invalid_argument(
        "Matrix dimensions do not allow multiplication.");
  } else {
    S21Matrix new_matrix(this->rows_, other.cols_);
    this->createmulmatrix(&new_matrix, other);
    for (int i = 0; i < this->rows_; i++) delete[] this->matrix_[i];
    delete[] this->matrix_;
    this->matrix_ = new_matrix.matrix_;
    this->cols_ = other.cols_;
  }
}
S21Matrix S21Matrix::Transpose() {
  S21Matrix transpose_matrix(this->cols_, this->rows_);
  if (this->matrix_ == nullptr || this->cols_ < 1 || this->rows_ < 1) {
    throw std::invalid_argument("Error when working with the matrix");
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        transpose_matrix.matrix_[j][i] = this->matrix_[i][j];
      }
    }
  }
  return transpose_matrix;
}
S21Matrix S21Matrix::CalcComplements() {
  S21Matrix result(this->rows_, this->cols_);
  if (this->matrix_ == nullptr || this->rows_ != this->cols_ ||
      this->rows_ < 1) {
    throw std::invalid_argument("Invalid matrix for calculating complements.");
  } else {
    if (this->rows_ == 1) {
      result.matrix_[0][0] = 1;

    } else {
      S21Matrix minor(this->rows_ - 1, this->cols_ - 1);
      for (int i = 0; i < this->rows_; i++) {
        for (int ii = 0; ii < this->cols_; ii++) {
          fill_minor(this->rows_ - 1, this, i, ii, &minor);

          double det;
          int mult = ((i + ii) % 2) ? -1 : 1;
          det = minor.Determinant();

          result.matrix_[i][ii] = det * mult;
        }
      }
    }
  }
  return result;
}
double S21Matrix::Determinant() {
  double result = 0.0;
  if (this->matrix_ == nullptr || this->rows_ <= 0 || this->cols_ <= 0 ||
      this->cols_ != this->rows_) {
    throw std::invalid_argument(
        "It is impossible to find the determinant of this matrix.");
  } else {
    if (this->rows_ == 1) {
      return this->matrix_[0][0];
    } else if (this->rows_ == 2) {
      return this->matrix_[0][0] * this->matrix_[1][1] -
             this->matrix_[0][1] * this->matrix_[1][0];
    } else {
      for (int j = 0; j < this->cols_; j++) {
        S21Matrix minor(this->rows_ - 1, this->cols_ - 1);
        for (int row = 1; row < this->rows_; row++) {
          for (int col = 0, minorCol = 0; col < this->cols_; col++) {
            if (col != j) {
              minor.matrix_[row - 1][minorCol++] = this->matrix_[row][col];
            }
          }
        }
        result +=
            (j % 2 == 0 ? 1 : -1) * this->matrix_[0][j] * minor.Determinant();
      }
    }
  }

  return result;
}
S21Matrix S21Matrix::InverseMatrix() {
  double det = this->Determinant();
  if (det == 0) {
    throw std::invalid_argument("Matrix is singular and cannot be inverted.");
  }
  S21Matrix cofactors = this->CalcComplements();
  S21Matrix adjugate = cofactors.Transpose();
  for (int i = 0; i < adjugate.rows_; i++) {
    for (int j = 0; j < adjugate.cols_; j++) {
      adjugate.matrix_[i][j] /= det;
    }
  }
  return adjugate;
}