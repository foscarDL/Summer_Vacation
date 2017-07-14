#ifndef MATRIX_H
#define MATRIX_H

namespace foscar {
class Matrix {

private:
    int      m_nRows;
    int      m_nCols;
    double    *m_pfMat;

public:
    Matrix();
    ~Matrix();
    Matrix(int nRows, int nCols);
    Matrix(const Matrix &mxInput);

    void    show();
    void    setValue(int* pnValue, int nRows, int nCols);
    void    setValue(double* pfValue, int nRows, int nCols);
    double   getValue(int nRows, int nCols);

    Matrix&   operator =(const Matrix &mxInput);
    Matrix    operator +(const Matrix &mxInput) const;
    Matrix    operator -(const Matrix &mxInput) const;
    Matrix    operator *(const int nInput) const;
    Matrix    operator *(const float fInput) const;
    Matrix    operator *(const double dInput) const;
    Matrix    operator *(const Matrix &mxInput) const;

    friend    Matrix operator *(int nInput, Matrix &mxInput);
    friend    Matrix operator *(float fInput, Matrix &mxInput);
    friend    Matrix operator *(double dInput, Matrix &mxInput);

    Matrix    transpose();
    Matrix    invert();
};
}

#endif
