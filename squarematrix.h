/* squarematrix.h */
#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

//////////////////////////////////////////////////////////
//	Matrices are represented columnwise, as in opengl   //
//  for row I and col J the element is i + j*nDims      //
//////////////////////////////////////////////////////////


#include <vector>
#include <complex>
#include <cstdlib>
//#include "typesanddefns.h"
#define CREATEANEXCEPTION {int z=0; _fcloseall(); z=1/z;}

enum MatrixInitialiser {
	MIZERO,
	MIUNIT,
	MIRANDOMROT,
	MIRESERVEONLY
};

enum DIRECTIONS {
	EMPTYDIR = -1,
	XDIR = 0,
	YDIR = 1,
	ZDIR = 2,
	WDIR = 3
};

enum MATRIXDESTINATION {
	RESULTINTHIS = 0,
	RESULTINPARAM = 1
};
enum MATRIXTRANSPOSE {
	TRANSPOSETHIS = 0,
	TRANSPOSEPARAM = 1
};

enum ROTPLANES {
	EMPTYPLANE = 0,
	YZPLANE = 1,
	ZXPLANE = 2,
	XYPLANE = 3,
	WXPLANE = 4,
	YWPLANE = 5,
	ZWPLANE = 6

	//  1 represents the yz plane
	//	2 represents the zx plane
	//	3 represents the xy plane
	//	4 represents the wx plane
	//	5 represents the yw plane
	//	6 represents the zw plane
};

class SquareMatrix
{
public:
	SquareMatrix(int nDims, MatrixInitialiser mi);
	SquareMatrix();
	~SquareMatrix(){}

	std::vector<double> v;

	inline double getElement(int i, int j) {return v[i + numberOfDims*j];}
	inline void setElement(int i, int j, double value) {v[i + numberOfDims*j]=value;}

//	void rightMultiply(SquareMatrix &multiplier, SquareMatrix & result);


	void multThisByParam(SquareMatrix &param, SquareMatrix &result);
	void multThisByParam(SquareMatrix &param, MATRIXDESTINATION dest);
	void multThisByParamTranspose(SquareMatrix &param, SquareMatrix &result, MATRIXTRANSPOSE trans);
	void multThisByParamTranspose(SquareMatrix &param, MATRIXDESTINATION dest, MATRIXTRANSPOSE trans);



	//void rightMult(SquareMatrix &multiplier, SquareMatrix & result);
	//void rightMultInPlace(SquareMatrix &multiplier);
	//void leftMult(SquareMatrix &multiplier, SquareMatrix & result);
	//void leftMultInPlace(SquareMatrix &multiplier);
	//void rightMultByTrans(SquareMatrix &multiplier, SquareMatrix & result);
	//void rightMultByTransInPlace(SquareMatrix &multiplier);
	//void leftMultByTrans(SquareMatrix &multiplier, SquareMatrix & result);
	//void leftMultByTransInPlace(SquareMatrix &multiplier);
	void transpose(std::vector<double> &vv);
	void transposeThis();
	void applyToVector(std::vector<double> &vect, std::vector<double> &result);
	double calcColumnLength(int col);
	void grammSchmidt();
	void rotateByTheta4(double theta1, ROTPLANES bivec1, double theta2, ROTPLANES bivec2);
	void initRandomRot();
	void initIdentity();
	void printContents();
	double getDistance(SquareMatrix &other);
	bool solveRotMat(std::complex<double> &eValue1,
							   std::complex<double> &eValue2,
							   std::vector<std::complex<double> > &evec1,
							   std::vector<std::complex<double> > &evec2,
							   int &denom1,
							   int &denom2);
	bool constructRotMat(std::vector<double> &spanVec1, std::vector<double> &spanVec2, double rotRadians);
	bool constructRotMatCumul(std::vector<double> &spanVec1, std::vector<double> &spanVec2, double rotRadians,
		SquareMatrix &cumul);


private:
	double solve_epsilon;
	void rotMat(int axisA, int axisB, std::vector<double> &result);
	void createUnitMatrix(std::vector<double> &tv);
	void vMultiply(std::vector<double> &start,
		std::vector<double> &multiplier,
		std::vector<double> &result);
	void matrixMult4 (std::vector<double> &m1, std::vector<double> &m2,std::vector<double> &m3);
	void matrixMult3 (std::vector<double> &m1, std::vector<double> &m2,std::vector<double> &m3);
	void matrixMult4ByTranspose2 (std::vector<double> &m1, std::vector<double> &m2,std::vector<double> &m3);
	void matrixMult4ByTranspose1 (std::vector<double> &m1, std::vector<double> &m2,std::vector<double> &m3);
	void matrixMult3ByTranspose2 (std::vector<double> &m1, std::vector<double> &m2,std::vector<double> &m3);
	void matrixMult3ByTranspose1 (std::vector<double> &m1, std::vector<double> &m2,std::vector<double> &m3);
	bool solvIt(std::vector<double> &b, std::vector<double> &result);
	bool solvItComplex(int nRows,std::vector<std::complex<double> > &smallMat,
								 std::vector<std::complex<double> > &b,
								 std::vector<std::complex<double> > &result);
	bool evSolve(int skipNum, double eValue, std::vector<double> &evecShort);
	bool evSolve(int skipNum, int skipCol, std::complex<double> eValue, std::vector<std::complex<double> > &evecShort);
	bool evSolver(std::complex<double> eValue, std::vector<std::complex<double> > &evecShort, int &denom);

	// NB the coefficient of the fourth power is always 1
	bool getCharPolyCoeffs(double *third,
			double *second,double *first,double *constant);


	int signR(double Z);
	double CBRT(double Z);
	int cubic(double A[4], double X[3], int* L);
	int quartic(double dd[5], double sol[4], double soli[4], int* Nsol);

	int numberOfDims;

};

#endif
