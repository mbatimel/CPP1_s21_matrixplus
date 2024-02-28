#include "../lib/s21_matrix_oop.h"

bool S21Matrix ::check_matrix(const S21Matrix &other) {
  bool res = true;
  if (this->matrix_ == nullptr || other.matrix_ == nullptr ||
      (this->rows_ != other.rows_) || (this->cols_ != other.cols_) ||
      this->rows_ <= 0 || this->cols_ <= 0) {
    res = false;
  }
  return res;
}

int S21Matrix ::noughts_handling(S21Matrix *copy, double *result,
                                 int dimention) {
  int switch_sign = 1;
  for (int v = 0; v < dimention; v++) {
    if (fabs(copy->matrix_[v][v]) < EPSILON) {
      int row = 0;
      while (row < dimention) {
        if (fabs(copy->matrix_[v][row]) > EPSILON &&
            fabs(copy->matrix_[row][v]) > EPSILON) {
          switch_sign *= -1;
          copy->replacement(copy, dimention, v, row);
          break;
        }

        else
          row++;
      }

      if (row == dimention) *result = 0;
    }
  }
  return switch_sign;
}
void S21Matrix ::replacement(S21Matrix *copy, int dimention, int v, int row) {
  double tmp;

  for (int i = 0; i < dimention; i++) {
    tmp = copy->matrix_[v][i];
    copy->matrix_[v][i] = copy->matrix_[row][i];
    copy->matrix_[row][i] = tmp;
  }
}
void S21Matrix ::fill_minor(int dimention, S21Matrix *A, int i, int ii,
                            S21Matrix *minor) {
  for (int iii = 0; iii < dimention; iii++) {
    for (int iv = 0; iv < dimention; iv++) {
      if (iii < i && iv < ii) minor->matrix_[iii][iv] = A->matrix_[iii][iv];
      if (iii < i && iv >= ii)
        minor->matrix_[iii][iv] = A->matrix_[iii][iv + 1];
      if (iii >= i && iv < ii)
        minor->matrix_[iii][iv] = A->matrix_[iii + 1][iv];
      if (iii >= i && iv >= ii)
        minor->matrix_[iii][iv] = A->matrix_[iii + 1][iv + 1];
    }
  }
}

int S21Matrix ::get_rows() const { return this->rows_; }
int S21Matrix ::get_cols() const { return this->cols_; }
void S21Matrix ::set_size(int new_rows, int new_cols) {
  // дописать
  double **new_matrix = nullptr;
  if (new_cols > 0 && new_rows > 0) {
    new_matrix = new double *[new_rows];
    for (int i = 0; i < new_rows; ++i) {
      new_matrix[i] = new double[new_cols]{0};
    }

    int min_rows = std::min(new_rows, rows_);
    int min_cols = std::min(new_cols, cols_);
    for (int i = 0; i < min_rows; ++i) {
      for (int j = 0; j < min_cols; ++j) {
        new_matrix[i][j] = this->matrix_[i][j];
      }
    }
  }

  for (int i = 0; i < rows_; ++i) {
    delete[] this->matrix_[i];
  }
  delete[] this->matrix_;

  this->matrix_ = new_matrix;
  this->rows_ = new_rows;
  this->cols_ = new_cols;
}

void S21Matrix::createmulmatrix(S21Matrix *matrix, const S21Matrix &other) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      matrix->matrix_[i][j] = 0;
      for (int k = 0; k < this->cols_; k++) {
        matrix->matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
}