#include "Matrix.h"

#include <cstdio>
#include <cstdlib>

using namespace foscar;

Matrix::Matrix() {

    m_nCols    = 0;
    m_nRows    = 0;
    m_pfMat    = 0;
}

Matrix::~Matrix() {

    if(m_pfMat) {
        delete(m_pfMat);
        m_pfMat    = 0;
    }
}
Matrix::Matrix(int nRows, int nCols) {
	m_nCols    = nCols;
	m_nRows	   = nRows;

	m_pfMat	   = new double[m_nRows*m_nCols];
	for(int i=0; i<m_nRows*m_nCols; i++)
	    m_pfMat[i]    = 0.f;
}
Matrix::Matrix(const Matrix &mxInput) {

    m_nCols    = mxInput.m_nCols;
    m_nRows    = mxInput.m_nRows;

    m_pfMat    = new double[m_nRows*m_nCols];
    for(int i=0; i<m_nRows*m_nCols; i++)
        m_pfMat[i]    = mxInput.m_pfMat[i];
}

void Matrix::show() {

    for(int i=0; i<m_nRows; i++) {
        printf("| ");

        for(int j=0; j<m_nCols; j++) {
            printf("%5.2f ", m_pfMat[i*m_nCols+j]);
        }

        printf(" |\n");
    }
    printf("\n");
}

void Matrix::setValue(int *pnValue, int nRows, int nCols) {

    m_nRows    = nRows;
    m_nCols    = nCols;

    if(m_pfMat)
        delete(m_pfMat);

    m_pfMat    = new double[nRows*nCols];

    for(int i=0; i<nRows*nCols; i++)
        m_pfMat[i]    = (double)pnValue[i];
}

void Matrix::setValue(double *pfValue, int nRows, int nCols) {

    m_nRows    = nRows;
    m_nCols    = nCols;

    if(m_pfMat)
        delete(m_pfMat);

    m_pfMat    = new double[nRows*nCols];

    for(int i=0; i<nRows*nCols; i++)
        m_pfMat[i]    = pfValue[i];
}

double Matrix::getValue(int nRows, int nCols) {

    return    m_pfMat[(nRows-1)*m_nCols+(nCols-1)];
}

Matrix & Matrix::operator =(const Matrix &mxInput) {

    if(m_pfMat)
        delete(m_pfMat);

    m_nCols    = mxInput.m_nCols;
    m_nRows    = mxInput.m_nRows;

    m_pfMat    = new double[m_nRows*m_nCols];
    for(int i=0; i<m_nRows*m_nCols; i++)
        m_pfMat[i]    = mxInput.m_pfMat[i];

    return *this;
}

Matrix Matrix::operator +(const Matrix &mxInput) const {

    if(m_nRows != mxInput.m_nRows || m_nCols != mxInput.m_nCols) {
        printf("Matrix dimension error, (+ operation) \n");
        exit(0);
    }

    Matrix    mxSum;
    double*    pfTmp    = new double[m_nRows*m_nCols];

    for(int i=0; i<m_nRows*m_nCols; i++)
        pfTmp[i]    = mxInput.m_pfMat[i] + m_pfMat[i];

    mxSum.m_nCols = m_nCols;
    mxSum.m_nRows = m_nRows;
    mxSum.setValue(pfTmp, m_nRows, m_nCols);

    delete(pfTmp);
    return    mxSum;
}

Matrix Matrix::operator -(const Matrix &mxInput) const {

    if(m_nRows != mxInput.m_nRows || m_nCols != mxInput.m_nCols) {
        printf("Matrix dimension error, (- operation) \n");
        exit(0);
    }

    Matrix    mxSum;
    double*    pfTmp    = new double[m_nRows*m_nCols];

    for(int i=0; i<m_nRows*m_nCols; i++)
        pfTmp[i]    = m_pfMat[i] - mxInput.m_pfMat[i];

    mxSum.m_nCols = m_nCols;
    mxSum.m_nRows = m_nRows;
    mxSum.setValue(pfTmp, m_nRows, m_nCols);

    delete(pfTmp);
    return    mxSum;
}

Matrix Matrix::operator *(const int nInput) const {

    Matrix    mxMult;
    double*    pfTmp    = new double[m_nRows*m_nCols];

    for(int i=0; i<m_nRows*m_nCols; i++)
        pfTmp[i]    = nInput * m_pfMat[i];

    mxMult.m_nCols = m_nCols;
    mxMult.m_nRows = m_nRows;
    mxMult.setValue(pfTmp, m_nRows, m_nCols);

    delete(pfTmp);
    return    mxMult;
}

Matrix Matrix::operator *(const float fInput) const {

    Matrix    mxMult;
    double*    pfTmp    = new double[m_nRows*m_nCols];

    for(int i=0; i<m_nRows*m_nCols; i++)
        pfTmp[i]    = fInput * m_pfMat[i];

    mxMult.m_nCols = m_nCols;
    mxMult.m_nRows = m_nRows;
    mxMult.setValue(pfTmp, m_nRows, m_nCols);

    delete(pfTmp);
    return    mxMult;
}

Matrix Matrix::operator *(const double dInput) const {

    Matrix    mxMult;
    double*    pfTmp    = new double[m_nRows*m_nCols];

    for(int i=0; i<m_nRows*m_nCols; i++)
        pfTmp[i]    = (double)dInput * m_pfMat[i];

    mxMult.m_nCols = m_nCols;
    mxMult.m_nRows = m_nRows;
    mxMult.setValue(pfTmp, m_nRows, m_nCols);

    delete(pfTmp);
    return    mxMult;
}

Matrix Matrix::operator *(const Matrix &mxInput) const {

    if(m_nCols != mxInput.m_nRows) {
        printf("Matrix dimension error, (* operation) \n");
        exit(0);
    }

    Matrix    mxMult;
    double*    pfTmp    = new double[m_nRows*mxInput.m_nCols];

    for(int i=0; i<m_nRows*mxInput.m_nCols; i++)
        pfTmp[i]    = 0.0;

    int    nIndex    = 0;
    for(int i=0; i<m_nRows; i++) {
        for(int j=0; j<mxInput.m_nCols; j++) {
            for(int k=0; k<m_nCols; k++) {
                pfTmp[i*mxInput.m_nCols+j]    += m_pfMat[i*m_nCols+k] * mxInput.m_pfMat[j+k*mxInput.m_nCols];
            }
        }
    }

    mxMult.setValue(pfTmp, m_nRows, mxInput.m_nCols);

    delete(pfTmp);
    return    mxMult;
}

Matrix operator *(int nInput, Matrix &mxInput) {

    return    mxInput * nInput;
}

Matrix operator *(float fInput, Matrix &mxInput) {

    return    mxInput * fInput;
}

Matrix operator *(double dInput, Matrix &mxInput) {

    return    mxInput * dInput;
}

Matrix Matrix::transpose() {

    Matrix    mxTrans;
    double*    pfTmp    = new double[m_nRows*m_nCols];

    for(int i=0; i<m_nRows; i++) {
        for(int j=0; j<m_nCols; j++) {
            pfTmp[i+m_nRows*j] = m_pfMat[i*m_nCols+j];
        }
    }

    mxTrans.setValue(pfTmp, m_nCols, m_nRows);

    delete(pfTmp);
    return    mxTrans;
}

Matrix Matrix::invert() {

    if(m_nRows != m_nCols) {
        printf("Matrix dimension error (Matrix must be square)\n");
        exit(0);
    }

    double    ftmp;
    double*    pfTmp;
    Matrix    mxInv;

    pfTmp        = new double[m_nRows*m_nCols];

    if(m_nCols == 2 && m_nRows == 2) {

        ftmp    = m_pfMat[0]*m_pfMat[3] - m_pfMat[1]*m_pfMat[2];

        if(ftmp == 0) {
            printf("Matrix inverse, divide zero error\n");
            exit(0);
        } else {
            pfTmp[0]    = m_pfMat[3] / ftmp;
            pfTmp[1]    = m_pfMat[1] / -ftmp;
            pfTmp[2]    = m_pfMat[2] / -ftmp;
            pfTmp[3]    = m_pfMat[0] / ftmp;
        }
    }

    mxInv.setValue(pfTmp, m_nCols, m_nRows);

    delete(pfTmp);
    return    mxInv;
}

