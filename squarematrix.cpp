/* squarematrix.cpp */


//#include "dxstdafx.h"

//#include "stdafx.h"
//#include "typesanddefns.h"
#include "squarematrix.h"
//#include "basicgeometry.h"
#include <math.h>

SquareMatrix::SquareMatrix(int nDims, MatrixInitialiser mi){
//	int i,j;
	numberOfDims = nDims;
	switch (mi) {
		case MIZERO:
			v.assign(nDims * nDims, 0);
			break;
		case MIUNIT:
			createUnitMatrix(v);
			break;
		case MIRANDOMROT:
			v.assign(numberOfDims * numberOfDims,0);
			initRandomRot();
			break;
	}
	solve_epsilon = 0.000001;
}

SquareMatrix::SquareMatrix(){
	numberOfDims = 4; //defaults to unit matrix of size 4 by 4
//	numberOfDims = 3; //defaults to unit matrix of size 3 by 3
	createUnitMatrix(v);
	solve_epsilon = 0.000001;
}


void SquareMatrix::rotMat(int axisA, int axisB, std::vector<double> &result){
	int i,j;
	double cs, sn, angle;

	// rotate by a random angle between 0 and two PI.
	angle = 2 * 3.141592654 * rand()/RAND_MAX;
	cs = cos(angle);
	sn = sin(angle);

	// for row I and col J the element is i + j*numberOfDims
	for (i = 0; i < numberOfDims; ++i) {
		for (j = 0; j < numberOfDims; ++j) {
			// Deal with diagonal elements first)
			if (i == j) {
				if (i == axisA || i == axisB) {
					result[i+j*numberOfDims] = cs;
				} else {
					result[i+j*numberOfDims] = 1;
				}
			} else {
				// Deal with off-diagonal elements
				if (i == axisA && j == axisB) {
					result[i+j*numberOfDims] = -sn;
				} else if (i == axisB && j == axisA) {
					result[i+j*numberOfDims] = sn;
				} else {
					result[i+j*numberOfDims] = 0;
				}
			}
		}
	}
}

void SquareMatrix::initIdentity(){
	int i,j;
	for (i = 0; i < numberOfDims; ++i) {
		for (j = 0; j < numberOfDims; ++j) {
			if (i == j) {
				v[i + j*numberOfDims] = 1;
			} else {
				v[i + j*numberOfDims] = 0;
			}
		}
	}
}
void SquareMatrix::initRandomRot(){
	std::vector<double> temp1;
	std::vector<double> temp2;
	std::vector<double> temp3;
	int i,j;

   	createUnitMatrix(temp1);
	temp2.assign(numberOfDims * numberOfDims, 0);
	temp3.assign(numberOfDims * numberOfDims, 0);

//	printf("Unit Matrix\n");
//	printContents(temp1);

	// for row I and col J the element is i + j*nDims
	for (i = 0; i < numberOfDims-1; ++i) {
		for (j = i + 1; j < numberOfDims; ++j) {
			// Create a rotation matrix in temp2 that is a rotation between 0 and 2 Pi
			// in the i,j plane
			rotMat(i,j,temp2);
//			printf("Rot Matrix for Axes = %d %d\n",i,j);
//			printContents(temp2);
			// Multiply the existing rotation matrix in temp1 with the new
			// rotation matrix in temp2
			vMultiply(temp1,temp2,temp3);

			temp1 = temp3;
//			printf("Base matrix after multiply\n");
//			printContents(temp1);
		}
	}
	v = temp1;
}

double SquareMatrix::calcColumnLength(int col){
	double store;
	int i;
	if (col >= numberOfDims) {
		return -1;
	} else {
		store = 0;
		for (i = 0; i < numberOfDims; ++i) {
			store += v[i + col*numberOfDims]*v[i + col*numberOfDims];
		}
		return sqrt(store);
	}
}


void SquareMatrix::createUnitMatrix(std::vector<double> &temp) {
	int i,j;
	for (i = 0; i < numberOfDims; ++i) {
		for (j = 0; j < numberOfDims; ++j) {
			if (i == j) {
				temp.push_back(1);
			} else {
				temp.push_back(0);
			}
		}
	}
}

void SquareMatrix::multThisByParam(SquareMatrix &param, SquareMatrix &result){
	switch (numberOfDims) {
		case 3:
			matrixMult3(v, param.v, result.v);
			break;
		case 4:
			matrixMult4(v, param.v, result.v);
			break;
		default:
			//printf("MultThisByParam - ONly for dims 3 and 4\n");
			{1.0/0.0;};
	}
}
void SquareMatrix::multThisByParam(SquareMatrix &param, MATRIXDESTINATION dest){
	std::vector<double> temp;

	temp.assign(numberOfDims*numberOfDims, 0);
	switch (numberOfDims) {
		case 3:
			matrixMult3(v, param.v, temp);
			break;
		case 4:
			matrixMult4(v, param.v, temp);
			break;
		default:
			//printf("RightmultInPlace ONly for dims 3 and 4\n");
			{1.0/0.0;};
	}
	if (dest == RESULTINTHIS) {
		v = temp;
	} else {
		param.v = temp;
	}
}
void SquareMatrix::multThisByParamTranspose(SquareMatrix &param, SquareMatrix &result, MATRIXTRANSPOSE trans){
	switch (numberOfDims) {
		case 3:
			if (trans == TRANSPOSETHIS) {
				matrixMult3ByTranspose1(v, param.v, result.v);
			} else {
				matrixMult3ByTranspose2(v, param.v, result.v);
			}
			break;
		case 4:
			if (trans == TRANSPOSETHIS) {
				matrixMult4ByTranspose1(v, param.v, result.v);
			} else {
				matrixMult4ByTranspose2(v, param.v, result.v);
			}
			break;
		default:
			//printf("MultThisByParamTranspose - ONly for dims 3 and 4\n");
			{1.0/0.0;};
	}
}
void SquareMatrix::multThisByParamTranspose(SquareMatrix &param, MATRIXDESTINATION dest, MATRIXTRANSPOSE trans) {
	std::vector<double> temp;
	temp.assign(numberOfDims*numberOfDims, 0);
	switch (numberOfDims) {
		case 3:
			if (trans == TRANSPOSETHIS) {
				matrixMult3ByTranspose1(v, param.v, temp);
			} else {
				matrixMult3ByTranspose2(v, param.v, temp);
			}
			break;
		case 4:
			if (trans == TRANSPOSETHIS) {
				matrixMult4ByTranspose1(v, param.v, temp);
			} else {
				matrixMult4ByTranspose2(v, param.v, temp);
			}
			break;
		default:
			//printf("MultThisByParamTranspose - ONly for dims 3 and 4\n");
			{1.0/0.0;};
	}
	if (dest == RESULTINTHIS) {
		v = temp;
	} else {
		param.v = temp;
	}
}


void SquareMatrix::transpose(std::vector<double> &vv) {
	//Transposes external array matrix in place
	double x;
	switch (numberOfDims) {
		case 3:
			x = vv[3]; vv[3] = vv[1]; vv[1] = x;
			x = vv[6]; vv[6] = vv[2]; vv[2] = x;
			x = vv[7]; vv[7] = vv[5]; vv[5] = x;
			break;
		case 4:
			x = vv[4]; vv[4] = vv[1]; vv[1] = x;
			x = vv[8]; vv[8] = vv[2]; vv[2] = x;
			x = vv[12]; vv[12] = vv[3]; vv[3] = x;
			x = vv[13]; vv[13] = vv[7]; vv[7] = x;
			x = vv[14]; vv[14] = vv[11]; vv[11] = x;
			x = vv[9]; vv[9] = vv[6]; vv[6] = x;
			break;
		default:
			//printf("Transpose ONly for dims 3 and 4\n");
			{1.0/0.0;};
	}

}

void SquareMatrix::transposeThis() {
	//Transposes this matrix in place
	double x;
	switch (numberOfDims) {
		case 3:
			x = v[3]; v[3] = v[1]; v[1] = x;
			x = v[6]; v[6] = v[2]; v[2] = x;
			x = v[7]; v[7] = v[5]; v[5] = x;
			break;
		case 4:
			x = v[4]; v[4] = v[1]; v[1] = x;
			x = v[8]; v[8] = v[2]; v[2] = x;
			x = v[12]; v[12] = v[3]; v[3] = x;
			x = v[13]; v[13] = v[7]; v[7] = x;
			x = v[14]; v[14] = v[11]; v[11] = x;
			x = v[9]; v[9] = v[6]; v[6] = x;
			break;
		default:
			//printf("Transpose ONly for dims 3 and 4\n");
			{1.0/0.0;};
	}

}


void SquareMatrix::vMultiply(std::vector<double> &st, std::vector<double> &ns, std::vector<double> &result) {
	// This needs to be optimised!!!!!!!!!!!!!!!!!
	int i,j,k; // i is row, j is col
	for (i = 0; i < numberOfDims; ++i) {
		for (j = 0; j < numberOfDims; ++j) {
			result[i + j*numberOfDims] = 0;
			for (k = 0; k < numberOfDims; ++k) {
				result[i + j*numberOfDims] += 
					st[i + k*numberOfDims] * ns[k + j*numberOfDims];
			}
		}
	}
}
void SquareMatrix::printContents(){
	int i,j; // i is row, j is col
	for (i = 0; i < numberOfDims; ++i) {
		for (j = 0; j < numberOfDims; ++j) {
			//printf("%8.4f",v[i+j*numberOfDims]);
		}
		//printf("\n");
	}
}

void SquareMatrix::applyToVector(std::vector<double> &vect, std::vector<double> &result){
	// matrix by vector  results in vector.
	if (vect.size() != numberOfDims) {
		//printf("The size of the vector %d is different from the dim of the matrix %d\n",
		//	vect.size(), numberOfDims);
		{1.0/0.0;};
	}
	int i,j;
	double sum;
	result.clear();
	for (i = 0; i < numberOfDims; ++i) {
		sum = 0;
		for (j = 0; j < numberOfDims; ++j) {
			sum += v[i+j*numberOfDims] * vect[j];
		}
		result.push_back(sum);
	}
}


void SquareMatrix::grammSchmidt(){
// performs an in-situ gramm-schmidt orthonormalisation
	double lngth, innera, innerb, innerc;
	if (numberOfDims == 3) {
		// Normalise the first vector
		lngth = v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
		if (lngth > 0.0 && lngth != 1.0) {
			lngth = sqrt(lngth);
			v[0] /= lngth;
			v[1] /= lngth;
			v[2] /= lngth;
		}
		// derive the second vector
		innera = v[0]*v[3] + v[1]*v[4] + v[2]*v[5];
		v[3] -= innera * v[0];
		v[4] -= innera * v[1];
		v[5] -= innera * v[2];
		lngth = v[3]*v[3] + v[4]*v[4] + v[5]*v[5];
		if (lngth > 0.0 && lngth != 1.0) {
			lngth = sqrt(lngth);	
			v[3] /= lngth;
			v[4] /= lngth;
			v[5] /= lngth;
		}
		
		// derive the third vector
		innera = v[0]*v[6] + v[1]*v[7] + v[2]*v[8];
		innerb = v[3]*v[6] + v[4]*v[7] + v[5]*v[8];

		v[6] -= (innera * v[0] + innerb * v[3]);
		v[7] -= (innera * v[1] + innerb * v[4]);
		v[8] -= (innera * v[2] + innerb * v[5]);
		lngth = v[6]*v[6] + v[7]*v[7] + v[8]*v[8];
		if (lngth > 0.0 && lngth != 1.0) {
			lngth = sqrt(lngth);	
			v[6] /= lngth;
			v[7] /= lngth;
			v[8] /= lngth;
		}
	} else if (numberOfDims == 4) {
		// Normalise the first vector
		lngth = v[0]*v[0] + v[1]*v[1] + v[2]*v[2] + v[3]*v[3];
		if (lngth > 0.0 && lngth != 1.0) {
			lngth = sqrt(lngth);
			v[0] /= lngth;
			v[1] /= lngth;
			v[2] /= lngth;
			v[3] /= lngth;
		}
		// derive the second vector
		innera = v[0]*v[4] + v[1]*v[5] + v[2]*v[6] + v[3]*v[7];
		v[4] -= innera * v[0];
		v[5] -= innera * v[1];
		v[6] -= innera * v[2];
		v[7] -= innera * v[3];
		lngth = v[4]*v[4] + v[5]*v[5] + v[6]*v[6] + v[7]*v[7];
		if (lngth > 0.0 && lngth != 1.0) {
			lngth = sqrt(lngth);	
			v[4] /= lngth;
			v[5] /= lngth;
			v[6] /= lngth;
			v[7] /= lngth;
		}
		
		// derive the third vector
		innera = v[0]*v[8] + v[1]*v[9] + v[2]*v[10] + v[3]*v[11];
		innerb = v[4]*v[8] + v[5]*v[9] + v[6]*v[10] + v[7]*v[11];

		v[8] -= (innera * v[0] + innerb * v[4]);
		v[9] -= (innera * v[1] + innerb * v[5]);
		v[10] -= (innera * v[2] + innerb * v[6]);
		v[11] -= (innera * v[3] + innerb * v[7]);
		lngth = v[8]*v[8] + v[9]*v[9] + v[10]*v[10] + v[11]*v[11];
		if (lngth > 0.0 && lngth != 1.0) {
			lngth = sqrt(lngth);
			v[8] /= lngth;
			v[9] /= lngth;
			v[10] /= lngth;
			v[11] /= lngth;
		}
		
		// derive the fourth vector
		innera = v[0]*v[12] + v[1]*v[13] + v[2]*v[14] + v[3]*v[15];
		innerb = v[4]*v[12] + v[5]*v[13] + v[6]*v[14] + v[7]*v[15];
		innerc = v[8]*v[12] + v[9]*v[13] + v[10]*v[14] + v[11]*v[15];
		v[12] -= (innera * v[0] + innerb * v[4] + innerc * v[8]);
		v[13] -= (innera * v[1] + innerb * v[5] + innerc * v[9]);
		v[14] -= (innera * v[2] + innerb * v[6] + innerc * v[10]);
		v[15] -= (innera * v[3] + innerb * v[7] + innerc * v[11]);
		lngth = v[12]*v[12] + v[13]*v[13] + v[14]*v[14] + v[15]*v[15];
		if (lngth > 0.0 && lngth != 1.0) {
			lngth = sqrt(lngth);
			v[12] /= lngth;
			v[13] /= lngth;
			v[14] /= lngth;
			v[15] /= lngth;
		}
	}
}

void SquareMatrix::rotateByTheta4(double theta1, ROTPLANES bivec1, double theta2, ROTPLANES bivec2){
	// Rotates this matrix (left multiplies it by a rot matrix) by theta1 in plane1 and theta2 in plane2

	double cs1, sn1, cs2, sn2;
	double c1_0,c1_1,c1_2,c1_3,c1_4,c1_5,c1_6,c1_7,c1_8,c1_9,c1_10,c1_11,c1_12,c1_13,c1_14,c1_15;
	double c2_0,c2_1,c2_2,c2_3,c2_4,c2_5,c2_6,c2_7,c2_8,c2_9,c2_10,c2_11,c2_12,c2_13,c2_14,c2_15;
	double s1_0,s1_1,s1_2,s1_3,s1_4,s1_5,s1_6,s1_7,s1_8,s1_9,s1_10,s1_11,s1_12,s1_13,s1_14,s1_15;
	double s2_0,s2_1,s2_2,s2_3,s2_4,s2_5,s2_6,s2_7,s2_8,s2_9,s2_10,s2_11,s2_12,s2_13,s2_14,s2_15;

	DIRECTIONS rot1Vec1, rot1Vec2, rot2Vec1, rot2Vec2;

	if (bivec1 == EMPTYPLANE) {
		if (bivec2 == EMPTYPLANE) return;
		rot1Vec1 = EMPTYDIR;
		rot1Vec2 = EMPTYDIR;
	} else {
		cs1 = cos(theta1);
		sn1 = sin(theta1);
	}
	if (bivec2 == EMPTYPLANE) {
		rot2Vec1 = EMPTYDIR;
		rot2Vec2 = EMPTYDIR;
	} else {
		cs2 = cos(theta2);
		sn2 = sin(theta2);
	}

	switch (bivec1) {
		case EMPTYPLANE:
			break;
		case YZPLANE:
			rot1Vec1 = YDIR;
			rot1Vec2 = ZDIR;
			break;
		case ZXPLANE:
			rot1Vec1 = ZDIR;
			rot1Vec2 = XDIR;
			break;
		case XYPLANE:
			rot1Vec1 = XDIR;
			rot1Vec2 = YDIR;
			break;
		case WXPLANE:
			rot1Vec1 = WDIR;
			rot1Vec2 = XDIR;
			break;
		case YWPLANE:
			rot1Vec1 = YDIR;
			rot1Vec2 = WDIR;
			break;
		case ZWPLANE:
			rot1Vec1 = ZDIR;
			rot1Vec2 = WDIR;
			break;
		default:
			{1.0/0.0;};
	}

	switch (bivec2) {
		case EMPTYPLANE:
			break;
		case YZPLANE:
			rot2Vec1 = YDIR;
			rot2Vec2 = ZDIR;
			break;
		case ZXPLANE:
			rot2Vec1 = ZDIR;
			rot2Vec2 = XDIR;
			break;
		case XYPLANE:
			rot2Vec1 = XDIR;
			rot2Vec2 = YDIR;
			break;
		case WXPLANE:
			rot2Vec1 = WDIR;
			rot2Vec2 = XDIR;
			break;
		case YWPLANE:
			rot2Vec1 = YDIR;
			rot2Vec2 = WDIR;
			break;
		case ZWPLANE:
			rot2Vec1 = ZDIR;
			rot2Vec2 = WDIR;
			break;
		default:
			{1.0/0.0;};
	}

	if (rot1Vec1 == XDIR || rot1Vec2 == XDIR) {
		c1_0 = cs1 * v[0];
		s1_0 = sn1 * v[0];
		c1_4 = cs1 * v[4];
		s1_4 = sn1 * v[4];
		c1_8 = cs1 * v[8];
		s1_8 = sn1 * v[8];
		c1_12 = cs1 * v[12];
		s1_12 = sn1 * v[12];
	}
	if (rot1Vec1 == YDIR || rot1Vec2 == YDIR) {
		c1_1 = cs1 * v[1];
		s1_1 = sn1 * v[1];
		c1_5 = cs1 * v[5];
		s1_5 = sn1 * v[5];
		c1_9 = cs1 * v[9];
		s1_9 = sn1 * v[9];
		c1_13 = cs1 * v[13];
		s1_13 = sn1 * v[13];
	}
	if (rot1Vec1 == ZDIR || rot1Vec2 == ZDIR) {
		c1_2 = cs1 * v[2];
		s1_2 = sn1 * v[2];
		c1_6 = cs1 * v[6];
		s1_6 = sn1 * v[6];
		c1_10 = cs1 * v[10];
		s1_10 = sn1 * v[10];
		c1_14 = cs1 * v[14];
		s1_14 = sn1 * v[14];
	}
	if (rot1Vec1 == WDIR || rot1Vec2 == WDIR) {
		c1_3 = cs1 * v[3];
		s1_3 = sn1 * v[3];
		c1_7 = cs1 * v[7];
		s1_7 = sn1 * v[7];
		c1_11 = cs1 * v[11];
		s1_11 = sn1 * v[11];
		c1_15 = cs1 * v[15];
		s1_15 = sn1 * v[15];
	}



	if (rot2Vec1 == XDIR || rot2Vec2 == XDIR) {
		c2_0 = cs2 * v[0];
		s2_0 = sn2 * v[0];
		c2_4 = cs2 * v[4];
		s2_4 = sn2 * v[4];
		c2_8 = cs2 * v[8];
		s2_8 = sn2 * v[8];
		c2_12 = cs2 * v[12];
		s2_12 = sn2 * v[12];
	}
	if (rot2Vec1 == YDIR || rot2Vec2 == YDIR) {
		c2_1 = cs2 * v[1];
		s2_1 = sn2 * v[1];
		c2_5 = cs2 * v[5];
		s2_5 = sn2 * v[5];
		c2_9 = cs2 * v[9];
		s2_9 = sn2 * v[9];
		c2_13 = cs2 * v[13];
		s2_13 = sn2 * v[13];
	}
	if (rot2Vec1 == ZDIR || rot2Vec2 == ZDIR) {
		c2_2 = cs2 * v[2];
		s2_2 = sn2 * v[2];
		c2_6 = cs2 * v[6];
		s2_6 = sn2 * v[6];
		c2_10 = cs2 * v[10];
		s2_10 = sn2 * v[10];
		c2_14 = cs2 * v[14];
		s2_14 = sn2 * v[14];
	}
	if (rot2Vec1 == WDIR || rot2Vec2 == WDIR) {
		c2_3 = cs2 * v[3];
		s2_3 = sn2 * v[3];
		c2_7 = cs2 * v[7];
		s2_7 = sn2 * v[7];
		c2_11 = cs2 * v[11];
		s2_11 = sn2 * v[11];
		c2_15 = cs2 * v[15];
		s2_15 = sn2 * v[15];
	}


	switch (bivec1) {
		case YZPLANE:
			v[1] = c1_1 - s1_2;
			v[2] = s1_1 + c1_2;
			// 2 3 same
			v[5] = c1_5 - s1_6;
			v[6] = s1_5 + c1_6;
			// 6 7 same
			v[9] = c1_9 - s1_10;
			v[10] = s1_9 + c1_10;
			// 10 11 same
			v[13] = c1_13 - s1_14;
			v[14] = s1_13 + c1_14;
			// 15 16 same
			break;
		case ZXPLANE:
			v[0] = c1_0 + s1_2;
			v[2] = -s1_0 + c1_2;
			// 1 3 same
			v[4] = c1_4 + s1_6;
			v[6] = -s1_4 + c1_6;
			// 5 7 same
			v[8] = c1_8 + s1_10;
			v[10] = -s1_8 + c1_10;
			// 9 11 same
			v[12] = c1_12 + s1_14;
			v[14] = -s1_12 + c1_14;
			// 13 15 same
			break;
		case XYPLANE:
			v[0] = c1_0 - s1_1;
			v[1] = s1_0 + c1_1;
			// 2 3 same
			v[4] = c1_4 - s1_5;
			v[5] = s1_4 + c1_5;
			// 6 7 same
			v[8] = c1_8 - s1_9;
			v[9] = s1_8 + c1_9;
			// 10 11 same
			v[12] = c1_12 - s1_13;
			v[13] = s1_12 + c1_13;
			break;
		case WXPLANE:
			v[0] = c1_0 + s1_3;
			v[3] = -s1_0 + c1_3;
			// 1 2 same
			v[4] = c1_4 + s1_7;
			v[7] = -s1_4 + c1_7;
			// 5 6 same
			v[8] = c1_8 + s1_11;
			v[11] = -s1_8 + c1_11;
			// 9 10 same
			v[12] = c1_12 + s1_15;
			v[15] = -s1_12 + c1_15;
			// 13 14 same
			break;
		case YWPLANE:
			v[1] = c1_1 - s1_3;
			v[3] = s1_1 + c1_3;
			// 0 2 same
			v[5] = c1_5 - s1_7;
			v[7] = s1_5 + c1_7;
			// 4 6 same
			v[9] = c1_9 - s1_11;
			v[11] = s1_9 + c1_11;
			// 8 10 same
			v[13] = c1_13 - s1_15;
			v[15] = s1_13 + c1_15;
			// 12 14 same
			break;
		case ZWPLANE:
			v[2] = c1_2 - s1_3;
			v[3] = s1_2 + c1_3;
			// 0 1 same
			v[6] = c1_6 - s1_7;
			v[7] = s1_6 + c1_7;
			// 4 5 same
			v[10] = c1_10 - s1_11;
			v[11] = s1_10 + c1_11;
			// 8 9 same
			v[14] = c1_14 - s1_15;
			v[15] = s1_14 + c1_15;
			// 12 13 same
			break;
	}

	switch (bivec2) {
		case YZPLANE:
			v[1] = c2_1 - s2_2;
			v[2] = s2_1 + c2_2;
			// 2 3 same
			v[5] = c2_5 - s2_6;
			v[6] = s2_5 + c2_6;
			// 6 7 same
			v[9] = c2_9 - s2_10;
			v[10] = s2_9 + c2_10;
			// 10 11 same
			v[13] = c2_13 - s2_14;
			v[14] = s2_13 + c2_14;
			// 15 16 same
			break;
		case ZXPLANE:
			v[0] = c2_0 + s2_2;
			v[2] = -s2_0 + c2_2;
			// 1 3 same
			v[4] = c2_4 + s2_6;
			v[6] = -s2_4 + c2_6;
			// 5 7 same
			v[8] = c2_8 + s2_10;
			v[10] = -s2_8 + c2_10;
			// 9 11 same
			v[12] = c2_12 + s2_14;
			v[14] = -s2_12 + c2_14;
			// 13 15 same
			break;
		case XYPLANE:
			v[0] = c2_0 - s2_1;
			v[1] = s2_0 + c2_1;
			// 2 3 same
			v[4] = c2_4 - s2_5;
			v[5] = s2_4 + c2_5;
			// 6 7 same
			v[8] = c2_8 - s2_9;
			v[9] = s2_8 + c2_9;
			// 10 11 same
			v[12] = c2_12 - s2_13;
			v[13] = s2_12 + c2_13;
			break;
		case WXPLANE:
			v[0] = c2_0 + s2_3;
			v[3] = -s2_0 + c2_3;
			// 1 2 same
			v[4] = c2_4 + s2_7;
			v[7] = -s2_4 + c2_7;
			// 5 6 same
			v[8] = c2_8 + s2_11;
			v[11] = -s2_8 + c2_11;
			// 9 10 same
			v[12] = c2_12 + s2_15;
			v[15] = -s2_12 + c2_15;
			// 13 14 same
			break;
		case YWPLANE:
			v[1] = c2_1 - s2_3;
			v[3] = s2_1 + c2_3;
			// 0 2 same
			v[5] = c2_5 - s2_7;
			v[7] = s2_5 + c2_7;
			// 4 6 same
			v[9] = c2_9 - s2_11;
			v[11] = s2_9 + c2_11;
			// 8 10 same
			v[13] = c2_13 - s2_15;
			v[15] = s2_13 + c2_15;
			// 12 14 same
			break;
		case ZWPLANE:
			v[2] = c2_2 - s2_3;
			v[3] = s2_2 + c2_3;
			// 0 1 same
			v[6] = c2_6 - s2_7;
			v[7] = s2_6 + c2_7;
			// 4 5 same
			v[10] = c2_10 - s2_11;
			v[11] = s2_10 + c2_11;
			// 8 9 same
			v[14] = c2_14 - s2_15;
			v[15] = s2_14 + c2_15;
			// 12 13 same
			break;
	}
}

void SquareMatrix::matrixMult4 (std::vector<double> &m1, std::vector<double> &m2, std::vector<double> &m3)
{
	m3[0] =	m1[0]*m2[0] +
			m1[4]*m2[1] +
			m1[8]*m2[2] +
			m1[12]*m2[3];
	m3[1] =	m1[1]*m2[0] +
			m1[5]*m2[1] +
			m1[9]*m2[2] +
			m1[13]*m2[3];
	m3[2] =	m1[2]*m2[0] +
			m1[6]*m2[1] +
			m1[10]*m2[2] +
			m1[14]*m2[3];
	m3[3] =	m1[3]*m2[0] +
			m1[7]*m2[1] +
			m1[11]*m2[2] +
			m1[15]*m2[3];
	
	m3[4] =	m1[0]*m2[4] + 
			m1[4]*m2[5] +
			m1[8]*m2[6] +
			m1[12]*m2[7];
	m3[5] =	m1[1]*m2[4] +
			m1[5]*m2[5] +
			m1[9]*m2[6] +
			m1[13]*m2[7];
	m3[6] =	m1[2]*m2[4] +
			m1[6]*m2[5] +
			m1[10]*m2[6] +
			m1[14]*m2[7];
	m3[7] =	m1[3]*m2[4] +
			m1[7]*m2[5] +
			m1[11]*m2[6] +
			m1[15]*m2[7];

	m3[8] =	m1[0]*m2[8] + 		
			m1[4]*m2[9] +
			m1[8]*m2[10] +
			m1[12]*m2[11];
	m3[9] =	m1[1]*m2[8] +
			m1[5]*m2[9] +
			m1[9]*m2[10] +
			m1[13]*m2[11];
	m3[10]=	m1[2]*m2[8] +
			m1[6]*m2[9] +
			m1[10]*m2[10] +
			m1[14]*m2[11];
	m3[11]=	m1[3]*m2[8] +
			m1[7]*m2[9] +
			m1[11]*m2[10] +
			m1[15]*m2[11];

	m3[12]=	m1[0]*m2[12] +
       		m1[4]*m2[13] +
       		m1[8]*m2[14] +
       		m1[12]*m2[15];
    m3[13]=	m1[1]*m2[12] +
       		m1[5]*m2[13] +
       		m1[9]*m2[14] +
       		m1[13]*m2[15];
    m3[14]=	m1[2]*m2[12] +
       		m1[6]*m2[13] +
       		m1[10]*m2[14] +
       		m1[14]*m2[15];
    m3[15]=	m1[3]*m2[12] +
       		m1[7]*m2[13] +
       		m1[11]*m2[14] +
       		m1[15]*m2[15];
}

void SquareMatrix::matrixMult4ByTranspose2 (std::vector<double> &m1, std::vector<double> &m2, std::vector<double> &m3)
{
	// The matrix in m2 is transposed before the multiplication

	m3[0] =	m1[0]*m2[0] +
			m1[4]*m2[4] +
			m1[8]*m2[8] +
			m1[12]*m2[12];
	m3[1] =	m1[1]*m2[0] +
			m1[5]*m2[4] +
			m1[9]*m2[8] +
			m1[13]*m2[12];
	m3[2] =	m1[2]*m2[0] +
			m1[6]*m2[4] +
			m1[10]*m2[8] +
			m1[14]*m2[12];
	m3[3] =	m1[3]*m2[0] +
			m1[7]*m2[4] +
			m1[11]*m2[8] +
			m1[15]*m2[12];
	
	m3[4] =	m1[0]*m2[1] + 
			m1[4]*m2[5] +
			m1[8]*m2[9] +
			m1[12]*m2[13];
	m3[5] =	m1[1]*m2[1] +
			m1[5]*m2[5] +
			m1[9]*m2[9] +
			m1[13]*m2[13];
	m3[6] =	m1[2]*m2[1] +
			m1[6]*m2[5] +
			m1[10]*m2[9] +
			m1[14]*m2[13];
	m3[7] =	m1[3]*m2[1] +
			m1[7]*m2[5] +
			m1[11]*m2[9] +
			m1[15]*m2[13];

	m3[8] =	m1[0]*m2[2] + 		
			m1[4]*m2[6] +
			m1[8]*m2[10] +
			m1[12]*m2[14];
	m3[9] =	m1[1]*m2[2] +
			m1[5]*m2[6] +
			m1[9]*m2[10] +
			m1[13]*m2[14];
	m3[10]=	m1[2]*m2[2] +
			m1[6]*m2[6] +
			m1[10]*m2[10] +
			m1[14]*m2[14];
	m3[11]=	m1[3]*m2[2] +
			m1[7]*m2[6] +
			m1[11]*m2[10] +
			m1[15]*m2[14];

	m3[12]=	m1[0]*m2[3] +
       		m1[4]*m2[7] +
       		m1[8]*m2[11] +
       		m1[12]*m2[15];
    m3[13]=	m1[1]*m2[3] +
       		m1[5]*m2[7] +
       		m1[9]*m2[11] +
       		m1[13]*m2[15];
    m3[14]=	m1[2]*m2[3] +
       		m1[6]*m2[7] +
       		m1[10]*m2[11] +
       		m1[14]*m2[15];
    m3[15]=	m1[3]*m2[3] +
       		m1[7]*m2[7] +
       		m1[11]*m2[11] +
       		m1[15]*m2[15];
}

void SquareMatrix::matrixMult4ByTranspose1 (std::vector<double> &m1, std::vector<double> &m2, std::vector<double> &m3)
{
	// The matrix in m1 is transposed before the multiplication

	m3[0] =	m1[0]*m2[0] +
			m1[1]*m2[1] +
			m1[2]*m2[2] +
			m1[3]*m2[3];
	m3[1] =	m1[4]*m2[0] +
			m1[5]*m2[1] +
			m1[6]*m2[2] +
			m1[7]*m2[3];
	m3[2] =	m1[8]*m2[0] +
			m1[9]*m2[1] +
			m1[10]*m2[2] +
			m1[11]*m2[3];
	m3[3] =	m1[12]*m2[0] +
			m1[13]*m2[1] +
			m1[14]*m2[2] +
			m1[15]*m2[3];

	m3[4] =	m1[0]*m2[4] +
			m1[1]*m2[5] +
			m1[2]*m2[6] +
			m1[3]*m2[7];
	m3[5] =	m1[4]*m2[4] +
			m1[5]*m2[5] +
			m1[6]*m2[6] +
			m1[7]*m2[7];
	m3[6] =	m1[8]*m2[4] +
			m1[9]*m2[5] +
			m1[10]*m2[6] +
			m1[11]*m2[7];
	m3[7] =	m1[12]*m2[4] +
			m1[13]*m2[5] +
			m1[14]*m2[6] +
			m1[15]*m2[7];

	m3[8] =	m1[0]*m2[8] +
			m1[1]*m2[9] +
			m1[2]*m2[10] +
			m1[3]*m2[11];
	m3[9] =	m1[4]*m2[8] +
			m1[5]*m2[9] +
			m1[6]*m2[10] +
			m1[7]*m2[11];
	m3[10]=	m1[8]*m2[8] +
			m1[9]*m2[9] +
			m1[10]*m2[10] +
			m1[11]*m2[11];
	m3[11]=	m1[12]*m2[8] +
			m1[13]*m2[9] +
			m1[14]*m2[10] +
			m1[15]*m2[11];

	m3[12]= m1[0]*m2[12] +
			m1[1]*m2[13] +
			m1[2]*m2[14] +
			m1[3]*m2[15];
	m3[13]= m1[4]*m2[12] +
			m1[5]*m2[13] +
			m1[6]*m2[14] +
			m1[7]*m2[15];
	m3[14]=	m1[8]*m2[12] +
			m1[9]*m2[13] +
			m1[10]*m2[14] +
			m1[11]*m2[15];
	m3[15]=	m1[12]*m2[12] +
			m1[13]*m2[13] +
			m1[14]*m2[14] +
			m1[15]*m2[15];

}
void SquareMatrix::matrixMult3 (std::vector<double> &m1, std::vector<double> &m2, std::vector<double> &m3)
{
	m3[0] =	m1[0]*m2[0] +
			m1[3]*m2[1] +
			m1[6]*m2[2];
	m3[1] =	m1[1]*m2[0] +
			m1[4]*m2[1] +
			m1[7]*m2[2];
	m3[2] =	m1[2]*m2[0] +
			m1[5]*m2[1] +
			m1[8]*m2[2];
	
	m3[3] =	m1[0]*m2[3] + 
			m1[3]*m2[4] +
			m1[6]*m2[5];
	m3[4] =	m1[1]*m2[3] +
			m1[4]*m2[4] +
			m1[7]*m2[5];
	m3[5] =	m1[2]*m2[3] +
			m1[5]*m2[4] +
			m1[8]*m2[5];

	m3[6] =	m1[0]*m2[6] + 
			m1[3]*m2[7] +
			m1[6]*m2[8];
	m3[7] =	m1[1]*m2[6] +
			m1[4]*m2[7] +
			m1[7]*m2[8];
	m3[8] =	m1[2]*m2[6] +
			m1[5]*m2[7] +
			m1[8]*m2[8];
}
void SquareMatrix::matrixMult3ByTranspose2 (std::vector<double> &m1, std::vector<double> &m2, std::vector<double> &m3)
{
	// Matrix m2 is transposed before the mult takes place. Result is in m3

	m3[0] =	m1[0]*m2[0] +
			m1[3]*m2[3] +
			m1[6]*m2[6];
	m3[1] =	m1[1]*m2[0] +
			m1[4]*m2[3] +
			m1[7]*m2[6];
	m3[2] =	m1[2]*m2[0] +
			m1[5]*m2[3] +
			m1[8]*m2[6];
	
	m3[3] =	m1[0]*m2[1] + 
			m1[3]*m2[4] +
			m1[6]*m2[7];
	m3[4] =	m1[1]*m2[1] +
			m1[4]*m2[4] +
			m1[7]*m2[7];
	m3[5] =	m1[2]*m2[1] +
			m1[5]*m2[4] +
			m1[8]*m2[7];

	m3[6] =	m1[0]*m2[2] + 
			m1[3]*m2[5] +
			m1[6]*m2[8];
	m3[7] =	m1[1]*m2[2] +
			m1[4]*m2[5] +
			m1[7]*m2[8];
	m3[8] =	m1[2]*m2[2] +
			m1[5]*m2[5] +
			m1[8]*m2[8];
}
void SquareMatrix::matrixMult3ByTranspose1 (std::vector<double> &m1, std::vector<double> &m2, std::vector<double> &m3)
{
	// Matrix m1 is transposed before the mult takes place. Result is in m3

	m3[0] =	m1[0]*m2[0] +
			m1[1]*m2[1] +
			m1[2]*m2[2];
	m3[1] =	m1[3]*m2[0] +
			m1[4]*m2[1] +
			m1[5]*m2[2];
	m3[2] =	m1[6]*m2[0] +
			m1[7]*m2[1] +
			m1[8]*m2[2];
	
	m3[3] =	m1[0]*m2[3] + 
			m1[1]*m2[4] +
			m1[2]*m2[5];
	m3[4] =	m1[3]*m2[3] +
			m1[4]*m2[4] +
			m1[5]*m2[5];
	m3[5] =	m1[6]*m2[3] +
			m1[7]*m2[4] +
			m1[8]*m2[5];

	m3[6] =	m1[0]*m2[6] + 
			m1[1]*m2[7] +
			m1[2]*m2[8];
	m3[7] =	m1[3]*m2[6] +
			m1[4]*m2[7] +
			m1[5]*m2[8];
	m3[8] =	m1[6]*m2[6] +
			m1[7]*m2[7] +
			m1[8]*m2[8];

}
double SquareMatrix::getDistance(SquareMatrix &other){
	double x, diff, scaleValue;
	int i,j;

	// We want the root mean square of distance of the axes
	// sqrt (dist of x-axis ^2  + dist of y-axis ^2 + ... + dist of w-axis ^2)
	// since 'dist of x-axis ^2' is min of 0 and max of 2
	// The RMS value has max of sqrt( 4 * num of dims)
	// Scale the above to 1.0)

	scaleValue = 4.0 * numberOfDims;

//	if (false) {
//		printf("This Matrix\n");
//		printContents();
//		printf("Other Matrix\n");
//		other.printContents();
//	}


	// For debug, calculate the dot prod of the cols
//	if (false) {
//		double angle;
//		for (j = 0; j < numberOfDims; ++j) { // cols
//			x = 0.0;
//			for (i = 0; i < numberOfDims; ++i) { // rows
//				x += v[i+j*numberOfDims] * other.v[i+j*numberOfDims];
//			}
//			angle = acos(x);
//			angle = angle * 57.295779513082320876798; //  RADIANSTODEGREES;
//			printf("%8.4f%9.3f",x,angle);
//		}
//		printf("\n");
//	}



	x = 0.0;

	//columnwise diffs
	for (j = 0; j < numberOfDims; ++j) { // cols
		for (i = 0; i < numberOfDims; ++i) { // rows
			diff = v[i+j*numberOfDims] - other.v[i+j*numberOfDims];
			x += diff * diff;
		}
	}
	x /= scaleValue;
	x = sqrt(x);
//	x /= (2*numberOfDims);
	return x;
}

bool SquareMatrix::solvIt(std::vector<double> &b,
		std::vector<double> &result) {
//Solves Ax = b
//
// Note the method of accessing rows and columns
//  if i refers to rows and j refers to colums, the element v[i,j]
//  can be obtained by v[i + j*numberOfDims]
//
//
	int icols,jrows,k,maxrow;
	double tmp;

	for (icols=0;icols<numberOfDims;++icols) {
//		printf("icols=%d\n",icols);
		maxrow = icols;

		// Find the row with the largest first value
		for (jrows = icols+1; jrows<numberOfDims; ++jrows) {
//			printf("  jrows=%d\n",jrows);
			if (abs(v[jrows+icols*numberOfDims]) >
				abs(v[maxrow+icols*numberOfDims])) {
				maxrow = jrows;
			}
		}

		// swap the maxrow and the icols row
		if (icols != maxrow) {
//			printf("  Switching rows %d and %d\n",icols,maxrow);
//			for (k = icols; k < numberOfDims+1; ++k){
			for (k = icols; k < numberOfDims; ++k){
//				printf("    K=%d\n",k);
				tmp = v[icols + k*numberOfDims];
//				printf("    K=%d\n",k);
				v[icols+k*numberOfDims] = v[maxrow+k*numberOfDims];
//				printf("    K=%d\n",k);
				v[maxrow+k*numberOfDims]=tmp;
//				printf("    K=%d\n",k);
			}
			tmp = b[icols];
//				printf("    1\n");
			b[icols] = b[maxrow];
//				printf("    2\n");
			b[maxrow] = tmp;
//				printf("    3\n");
		}

		// Is this a singular matrix
		if (abs(v[icols + icols * numberOfDims]) < solve_epsilon) {
//			printf("    Singular\n");
			return false;
		}

		// Eliminate the icol'th element from the jrow'th row
		for (jrows = icols + 1;  jrows<numberOfDims; ++jrows) {
			b[jrows] -= b[icols]*v[jrows+icols*numberOfDims]/
				v[icols + icols*numberOfDims];
//			printf("    b elim done\n");
			for (k = numberOfDims-1; k>=icols; --k){
//			for (k = numberOfDims; k>=icols; --k){
//				printf("    k=%d elim\n",k);
				v[jrows+k*numberOfDims] -= v[icols+k*numberOfDims]*
				v[jrows+icols*numberOfDims]/v[icols + icols*numberOfDims];
			}
		}
	}

	// Do the back substitution
	//
//	printf("Back subst\n");
	for (jrows = numberOfDims-1; jrows >= 0; --jrows) {
		tmp = 0;
		for (k = jrows+1; k<numberOfDims; ++k) {
			tmp += v[jrows+k*numberOfDims] * result[k];
		}
//		result[jrows] = (v[jrows+numberOfDims*numberOfDims] - tmp)/
//			v[jrows+jrows*numberOfDims];
		result[jrows] = (b[jrows] - tmp)/v[jrows+jrows*numberOfDims];
	}
	return true;
}

bool SquareMatrix::solvItComplex(int nRows,
								 std::vector<std::complex<double> > &smallMat,
								 std::vector<std::complex<double> > &b,
								 std::vector<std::complex<double> > &result) {
//Solves SmallMat.x = b
//
// Note the method of accessing rows and columns
//  if i refers to rows and j refers to colums, the element v[i,j]
//  can be obtained by v[i + j*numberOfDims]
//
//

	int icols,jrows,k,maxrow;
	std::complex<double> tmp;

	for (icols=0;icols<nRows;++icols) {
//		printf("icols=%d\n",icols);
		maxrow = icols;

		// Find the row with the largest first value
		for (jrows = icols+1; jrows<nRows; ++jrows) {
//			printf("  jrows=%d\n",jrows);
			if (abs(smallMat[jrows+icols*nRows]) >
				abs(smallMat[maxrow+icols*nRows])) {
				maxrow = jrows;
			}
		}

		// swap the maxrow and the icols row
		if (icols != maxrow) {
//			printf("  Switching rows %d and %d\n",icols,maxrow);
//			for (k = icols; k < nRows+1; ++k){
			for (k = icols; k < nRows; ++k){
//				printf("    K=%d\n",k);
				tmp = smallMat[icols + k*nRows];
//				printf("    K=%d\n",k);
				smallMat[icols+k*nRows] = smallMat[maxrow+k*nRows];
//				printf("    K=%d\n",k);
				smallMat[maxrow+k*nRows]=tmp;
//				printf("    K=%d\n",k);
			}
			tmp = b[icols];
//				printf("    1\n");
			b[icols] = b[maxrow];
//				printf("    2\n");
			b[maxrow] = tmp;
//				printf("    3\n");
		}

		// Is this a singular matrix
		if (abs(smallMat[icols + icols * nRows]) < solve_epsilon) {
//			printf("    Singular\n");
			return false;
		}

		// Eliminate the icol'th element from the jrow'th row
		for (jrows = icols + 1;  jrows<nRows; ++jrows) {
			b[jrows] -= b[icols]*smallMat[jrows+icols*nRows]/
				smallMat[icols + icols*nRows];
//			printf("    b elim done\n");
			for (k = nRows-1; k>=icols; --k){
//			for (k = nRows; k>=icols; --k){
//				printf("    k=%d elim\n",k);
				smallMat[jrows+k*nRows] -= smallMat[icols+k*nRows]*
				smallMat[jrows+icols*nRows]/smallMat[icols + icols*nRows];
			}
		}
	}

	// Do the back substitution
	//
//	printf("Back subst\n");
	for (jrows = nRows-1; jrows >= 0; --jrows) {
		tmp = 0;
		for (k = jrows+1; k<nRows; ++k) {
			tmp += smallMat[jrows+k*nRows] * result[k];
		}
//		result[jrows] = (smallMat[jrows+nRows*nRows] - tmp)/
//			smallMat[jrows+jrows*nRows];
		result[jrows] = (b[jrows] - tmp)/smallMat[jrows+jrows*nRows];
	}
	return true;
}

bool SquareMatrix::getCharPolyCoeffs(double *third,
			double *second,double *first,double *constant) {
// NB the coefficient of the fourth power of x (where x is an eigenvalue) is always 1
//
// These formulae obtained from maple10
//
// This method returns the coefficients of the powers of x (or, mor usually, lambda)
// in the characteristic polynomial of the (4x4) square matrix.
//
// So the characteristic polynomial is
//
// x^4 + (*third)x^3 + (*second)x^2 + (*first)x + (*constant)

	*third  = -v[15]-v[10]-v[5]-v[0];
	*second = -v[3]*v[12]
		-v[7]*v[13]
		-v[11]*v[14]
		+v[15]*v[10]
		+v[15]*v[5]
		+v[15]*v[0]
		-v[2]*v[8]
		-v[6]*v[9]
		+v[10]*v[5]
		+v[10]*v[0]
		-v[1]*v[4]
		+v[5]*v[0];

	if (true) {
		// This next bit is from empirical observation, not proper theory
		*first = *third;
		*constant = 1.0;
	} else {
		*first = 
		-v[3]*v[8]*v[14]
		-v[10]*v[5]*v[0]
		-v[7]*v[9]*v[14]
		-v[6]*v[1]*v[8]
		+v[2]*v[8]*v[5]
		+v[10]*v[1]*v[4]
		-v[7]*v[1]*v[12]
		+v[6]*v[9]*v[0]
		-v[2]*v[4]*v[9]
		-v[15]*v[5]*v[0]
		+v[15]*v[1]*v[4]
		-v[15]*v[10]*v[0]
		-v[15]*v[10]*v[5]
		+v[15]*v[6]*v[9]
		+v[15]*v[2]*v[8]
		+v[11]*v[14]*v[0]
		+v[11]*v[14]*v[5]
		+v[7]*v[13]*v[0]
		+v[7]*v[13]*v[10]
		+v[3]*v[12]*v[5]
		+v[3]*v[12]*v[10]
		-v[3]*v[4]*v[13]
		-v[11]*v[2]*v[12]
		-v[11]*v[6]*v[13];

		*constant = 
		-v[7]*v[13]*v[10]*v[0]
		+v[11]*v[14]*v[1]*v[4]
		-v[11]*v[14]*v[5]*v[0]
		+v[15]*v[2]*v[4]*v[9]
		+v[15]*v[6]*v[1]*v[8]
		-v[15]*v[2]*v[8]*v[5]
		-v[15]*v[6]*v[9]*v[0]
		-v[15]*v[10]*v[1]*v[4]
		+v[15]*v[10]*v[5]*v[0]
		+v[7]*v[13]*v[2]*v[8]
		-v[3]*v[8]*v[6]*v[13]
		-v[7]*v[1]*v[8]*v[14]
		-v[7]*v[9]*v[2]*v[12]
		-v[11]*v[2]*v[4]*v[13]
		-v[11]*v[6]*v[1]*v[12]
		+v[3]*v[4]*v[13]*v[10]
		+v[3]*v[8]*v[14]*v[5]
		+v[7]*v[1]*v[12]*v[10]
		+v[7]*v[9]*v[14]*v[0]
		+v[11]*v[2]*v[12]*v[5]
		+v[11]*v[6]*v[13]*v[0]
		+v[3]*v[12]*v[6]*v[9]
		-v[3]*v[12]*v[10]*v[5]
		-v[3]*v[4]*v[9]*v[14];
	}

//	if (*constant != 1.0) printf("Constant not 1.0\n");
//	if (*first != *third) printf("First not eq third, diff = %19.15f\n",*first - *third);

	return true;
}
bool SquareMatrix::evSolve(int skipNum, double eValue, std::vector<double> &evecShort){

	// skipnum = number of the row to skip.
	std::vector<double> small;
	SquareMatrix *smallSq;
	int i,j,k,l;
	double subLambda;

	if (skipNum < 0 || skipNum > (numberOfDims - 1)) {
		{1.0/0.0;};
	}
	smallSq = new SquareMatrix(numberOfDims - 1,MIZERO);

	small.assign(numberOfDims-1,0);
	evecShort.assign(numberOfDims-1,0);

//	printf("In EVSOLVE skipnum=%d, eValue=%9.5f\n",skipNum,eValue);

	//Copy this matrix to a 'small' matrix of n-1 X n-1
	k = 0; l = 0;
	for (i = 0; i < numberOfDims; ++i){
		//Skip a row
		if (i != skipNum) {

			for (j = 0; j < numberOfDims; ++j) {
//				printf("i=%d j=%d k=%d l=%d\n",i,j,k,l);
				if (i == j) {
					subLambda = eValue;
				} else {
					subLambda = 0.0;
				}

				if (j == (numberOfDims - 1)) {
					small[k] = -(getElement(i,j) - subLambda);
//					printf("Adding to short %9.4f\n",-v[i + j*numberOfDims]);
					++k;
				} else {
					// for diagonal elements we must subtract the eigenvalue
					smallSq->setElement(k, l, getElement(i,j) - subLambda);
					//if ( false && i == j) {
					//	smallSq->setElement(k, l, getElement(i,j) - eValue);
					//} else {
					//	smallSq->setElement(k, l, getElement(i,j));
					//}
//					small[k + l*(numberOfDims - 1)] = v[i + j * numberOfDims];
//					printf("Adding to small %9.4f\n",v[i + j*numberOfDims]);

					if (++l >= (numberOfDims - 1)) {
						l = 0;
					}
				}
			}
		}
	}


//	if (false) {
//		printf("Original Matr..\n");
//		printContents();
//		printf("Small Matr..\n");
//		smallSq->printContents();
//		//for (i = 0; i < numberOfDims-1; ++i) {
//		//	for (j = 0; j < numberOfDims-1; ++j) {
//		//		printf(" sq %9.5f",smallSq->getElement(i,j));
//		//	}
//		//	printf("\n");
//		//}
//		for (i = 0; i < numberOfDims - 1; ++i) {
//			printf("small %10.5f\n",small[i]);
//		}
//		//printf("\n");
//
//	}

	smallSq->solvIt(small,evecShort);

//Solves Ax = b
	double denom, numer1, numer2, numer3;
	if (true){


		denom = 
		- smallSq->v[2]*smallSq->v[4]*smallSq->v[6] 
		+ smallSq->v[2]*smallSq->v[3]*smallSq->v[7] 
		+ smallSq->v[1]*smallSq->v[5]*smallSq->v[6] 
		- smallSq->v[3]*smallSq->v[1]*smallSq->v[8] 
		+ smallSq->v[4]*smallSq->v[0]*smallSq->v[8] 
		- smallSq->v[0]*smallSq->v[5]*smallSq->v[7];

		numer1 = 
		-smallSq->v[7]*smallSq->v[5]*small[0]
		+small[1]*smallSq->v[5]*smallSq->v[6]
		-smallSq->v[8]*smallSq->v[3]*small[1]
		+smallSq->v[8]*smallSq->v[4]*small[0]
		-small[2]*smallSq->v[4]*smallSq->v[6]
		+small[2]*smallSq->v[3]*smallSq->v[7];

		numer2 = 
		-smallSq->v[1]*smallSq->v[8]*small[0]
		-smallSq->v[1]*small[2]*smallSq->v[6]
		-smallSq->v[2]*smallSq->v[7]*small[0]
		-smallSq->v[8]*smallSq->v[0]*small[1]
		+smallSq->v[2]*small[1]*smallSq->v[6]
		+small[2]*smallSq->v[0]*smallSq->v[7];

		numer3 = 
		-smallSq->v[3]*smallSq->v[1]*small[2]
		+smallSq->v[2]*smallSq->v[3]*small[1]
		-smallSq->v[2]*smallSq->v[4]*small[0]
		+smallSq->v[4]*smallSq->v[0]*small[2]
		+smallSq->v[1]*smallSq->v[5]*small[0]
		-smallSq->v[0]*smallSq->v[5]*small[1];

//		printf("NuSolve %9.5f %9.5f %9.5f\n",numer1/denom,numer2/denom,numer3/denom);
	}

	delete smallSq;
	return true;

}

bool SquareMatrix::evSolve(int skipNum, int skipCol, std::complex<double> eValue, std::vector<std::complex<double> > &evecShort){

	// skipnum = number of the row to skip.
	// skipcol = number of the col to skip
	// evalue = the eigenvalue (for which we are finding the eigenvector
	// evecshort = the eigenvector that we find.
	std::vector<std::complex<double> > smallB;
	std::vector<std::complex<double> > smallMat;
	std::vector<int> nonZeroCol;
	std::vector<int> nonZeroRow;
	int nonZeroB = 0;
	//SquareMatrix *smallSq;
	int i,j,k,l;
	std::complex<double> subLambda;

	if (skipNum < 0 || skipNum > (numberOfDims - 1)) {
		{1.0/0.0;};
	}

	smallB.assign(numberOfDims-1,0);
	evecShort.assign(numberOfDims-1,0);
	smallMat.assign((numberOfDims-1)*(numberOfDims-1),0);
	nonZeroCol.assign(numberOfDims-1,0);
	nonZeroRow.assign(numberOfDims-1,0);

//	printf("In EVSOLVE skipnum=%d, skipcol=%d eValue=%9.5f i%9.5f\n",skipNum,skipCol,eValue.real(),eValue.imag());

	//Copy this matrix to a 'small' matrix of n-1 X n-1
	k = 0; l = 0; // K indexes rows, l indexes cols
	for (i = 0; i < numberOfDims; ++i){
		//Skip a row
		l = 0;
		if (i != skipNum) {

			for (j = 0; j < numberOfDims; ++j) {
//				printf("i=%d j=%d k=%d l=%d\n",i,j,k,l);
				if (i == j) {
					subLambda = eValue;
				} else {
					subLambda = 0.0;
				}

				if (j == skipCol) {
					smallB[k] = -(getElement(i,j) - subLambda);
					if (abs(smallB[k]) != 0) { // Count the number of times B is nonzero
						++nonZeroB;
					}
				} else {
					smallMat[k + l*(numberOfDims - 1)] = getElement(i,j) - subLambda;
//					printf("Adding to small %9.4f\n",v[i + j*numberOfDims]);

					if (abs(getElement(i,j) - subLambda) != 0) {
						++nonZeroRow[k];
						++nonZeroCol[l];
					}
					++l;
				}
			}
			++k;
		}
	}

//	if (false) {
//		printf("Original Matr..\n");
//		printContents();
//		printf("Small Matr..\n");
//		for (i = 0; i < numberOfDims-1; ++i) {
//			for (j = 0; j < numberOfDims-1; ++j) {
//				printf(" %9.5f i%9.5f",smallMat[i + j*(numberOfDims - 1)].real(), smallMat[i+j*(numberOfDims-1)].imag());
//			}
//			printf("\n");
//		}
//		for (i = 0; i < numberOfDims - 1; ++i) {
//			printf("smallB %10.5f i%10.5f\n",smallB[i].real(), smallB[i].imag());
//		}
//	}

	if (nonZeroB == 0) {
//		printf("All Zero B detected\n");
		return false;
	}
	for (k = 0; k < numberOfDims - 1; ++k) {
		if (nonZeroRow[k] == 0) {
//			printf("All Zero row[%d] detected\n",k);
			return false;
		}
		if (nonZeroCol[k] == 0) {
//			printf("All Zero col[%d] detected\n",k);
			return false;
		}
	}

	bool res = solvItComplex(numberOfDims - 1, smallMat, smallB, evecShort);
//	printf("bool result is %d\n",res);
	return res;
}

bool SquareMatrix::evSolver(std::complex<double> eValue, std::vector<std::complex<double> > &evecShort, int &denom){

	int skiprow,skipcol;
	bool result;

	for (skiprow = 0; skiprow < numberOfDims; ++skiprow) {
		for (skipcol = 0; skipcol < numberOfDims; ++skipcol) {
			result = evSolve(skiprow,skipcol,eValue,evecShort);
			if (result) {
				denom = skipcol;
				break;
			}
		}
		if (result) break;
	}
	return result;
}

int SquareMatrix::signR(double Z) {
 // int ret;
 // if (Z > 0.0) {
	//  ret = 1;
 // } else {
	//  if (Z < 0.0) {
	//	  ret = -1;
	//  } else {
	//	  ret =0;
	//  }
 // }

	//return ret;
  if (Z > 0.0) return 1;
  if (Z < 0.0) return -1;
  return 0;
}

double SquareMatrix::CBRT(double Z) {
  double ret;
	const double THIRD = 1./3.;
	//define cubic root as statement function
	//SIGN has different meanings in both C and Fortran
	// Was unable to use the sign command of C, so wrote my own
	// that why a new variable needs to be introduced that keeps track of the sign of
	// SIGN is supposed to return a 1, -1 or 0 depending on what the sign of the argument is
	ret = fabs(pow(fabs(Z),THIRD)) * signR(Z);
	return ret;
}

int SquareMatrix::cubic(double A[4], double X[3], int* L) {
  /*-------------------- Global Function Description Block ----------------------
  *
  *     ***CUBIC************************************************08.11.1986
  *     Solution of a cubic equation
  *     Equations of lesser degree are solved by the appropriate formulas.
  *     The solutions are arranged in ascending order.
  *     NO WARRANTY, ALWAYS TEST THIS SUBROUTINE AFTER DOWNLOADING
  *     ******************************************************************
  *     A(0:3)      (i)  vector containing the polynomial coefficients
  *     X(1:L)      (o)  results
  *     L           (o)  number of valid solutions (beginning with X(1))
  *     ==================================================================
  *  	17-Oct-2004 / Raoul Rausch
  *		Conversion from Fortran to C
  *
  *
  *-----------------------------------------------------------------------------
  */
	const double PI = 3.1415926535897932;
	const double THIRD = 1./3.;
	double U[3],W, P, Q, DIS, PHI;
	int i;
	
	using namespace std;

	//define cubic root as statement function
	// In C, the function is defined outside of the cubic fct

	// ====determine the degree of the polynomial ====

	if (A[3] != 0.0)
	{
		//cubic problem
		W = A[2]/A[3]*THIRD;
		P = pow((A[1]/A[3]*THIRD - pow(W,2)),3);
		Q = -.5*(2.0*pow(W,3)-(A[1]*W-A[0])/A[3] );
		DIS = pow(Q,2)+P;
		if ( DIS < 0.0 )
		{
			//three real solutions!
			//Confine the argument of ACOS to the interval [-1;1]!
			PHI = acos(min(1.0,max(-1.0,Q/sqrt(-P))));
			P=2.0*pow((-P),(5.e-1*THIRD));
			for (i=0;i<3;i++)	U[i] = P*cos((PHI+2*((double)i)*PI)*THIRD)-W;
			X[0] = min(U[0], min(U[1], U[2]));
			X[1] = max(min(U[0], U[1]),max( min(U[0], U[2]), min(U[1], U[2])));
			X[2] = max(U[0], max(U[1], U[2]));
			*L = 3;
		}
		else
		{
			// only one real solution!
			DIS = sqrt(DIS);
			X[0] = CBRT(Q+DIS)+CBRT(Q-DIS)-W;
			*L=1;
		}
	}
	else if (A[2] != 0.0)
	{
		// quadratic problem
		P = 0.5*A[1]/A[2];
		DIS = pow(P,2)-A[0]/A[2];
		if (DIS > 0.0)
		{
			// 2 real solutions
			X[0] = -P - sqrt(DIS);
			X[1] = -P + sqrt(DIS);
			*L=2;
		}
		else
		{
			// no real solution
			*L=0;
		}
	}
	else if (A[1] != 0.0)
	{
		//linear equation
		X[0] =A[0]/A[1];
		*L=1;
	}
	else
	{
		//no equation
		*L=0;
	}
 /*
  *     ==== perform one step of a newton iteration in order to minimize
  *          round-off errors ====
  */
	for (i=0;i<*L;i++)
	{
		X[i] = X[i] - (A[0]+X[i]*(A[1]+X[i]*(A[2]+X[i]*A[3])))/(A[1]+X[i]*(2.0*A[2]+X[i]*3.0*A[3]));
	//	printf("\n X inside cubic %.15e\n", X[i]);
	}

	return 0;
}

int SquareMatrix::quartic(double dd[5], double sol[4], double soli[4], int* Nsol) {
  /*-------------------- Global Function Description Block ----------------------
 *
 *     ***QUARTIC************************************************25.03.98
 *     Solution of a quartic equation
 *     ref.: J. E. Hacke, Amer. Math. Monthly, Vol. 48, 327-328, (1941)
 *     NO WARRANTY, ALWAYS TEST THIS SUBROUTINE AFTER DOWNLOADING
 *     ******************************************************************
 *     dd(0:4)     (i)  vector containing the polynomial coefficients
 *     sol(1:4)    (o)  results, real part
 *     soli(1:4)   (o)  results, imaginary part
 *     Nsol        (o)  number of real solutions 
 *     ==================================================================
 *  	17-Oct-2004 / Raoul Rausch
 *		Conversion from Fortran to C
 *
 * Coeffs of dd:
 * [0] is const, [1] is power 1, [2] is power 2, [3] is power 3, [4] is power 4
 *-----------------------------------------------------------------------------
 */
 

	double AA[4], z[3];
	double a, b, c, d, f, p, q, r, zsol, xK2, xL, xK, sqp, sqm;
	int ncube, i;
	*Nsol = 0;
		using namespace std;


	if (dd[4] == 0.0)
	{
//		printf("\n ERROR: NOT A QUARTIC EQUATION");
		return 0;
	}

	a = dd[4];
	b = dd[3];
	c = dd[2];
	d = dd[1];
	f = dd[0];

	p = (-3.0*pow(b,2) + 8.0 *a*c)/(8.0*pow(a,2));
	q = (pow(b,3) - 4.0*a*b*c + 8.0 *d*pow(a,2)) / (8.0*pow(a,3));
	r = (-3.0*pow(b,4) + 16.0 *a*pow(b,2)*c - 64.0 *pow(a,2)*b*d + 256.0 *pow(a,3)*f)/(256.0*pow(a,4));
	
	// Solve cubic resolvent
	AA[3] = 8.0;
	AA[2] = -4.0*p;
	AA[1] = -8.0*r;
	AA[0] = 4.0*p*r - pow(q,2);

	//printf("\n bcubic %.4e\t%.4e\t%.4e\t%.4e ", AA[0], AA[1], AA[2], AA[3]);
	cubic(AA, z, &ncube);
	//printf("\n acubic %.4e\t%.4e\t%.4e ", z[0], z[1], z[2]);
	
	zsol = - 1.e99;
	for (i=0;i<ncube;i++)	zsol = max(zsol, z[i]);	//Not sure C has max fct
	z[0] =zsol;
	xK2 = 2.0*z[0] -p;
	xK = sqrt(xK2);
	xL = q/(2.0*xK);
	sqp = xK2 - 4.0 * (z[0] + xL);
	sqm = xK2 - 4.0 * (z[0] - xL);

	for (i=0;i<4;i++)	soli[i] = 0.0;
	if ( (sqp >= 0.0) && (sqm >= 0.0))
	{
//		printf("\n case 1 ");
		sol[0] = 0.5 * (xK + sqrt(sqp));
		sol[1] = 0.5 * (xK - sqrt(sqp));
		sol[2] = 0.5 * (-xK + sqrt(sqm));
		sol[3] = 0.5 * (-xK - sqrt(sqm));
		*Nsol = 4;
	}
	else if ( (sqp >= 0.0) && (sqm < 0.0))
	{
//		printf("\n case 2 ");
		sol[0] = 0.5 * (xK + sqrt(sqp));
		sol[1] = 0.5 * (xK - sqrt(sqp));
		sol[2] = -0.5 * xK;
		sol[3] = -0.5 * xK;
		soli[2] =  sqrt(-.25 * sqm);
		soli[3] = -sqrt(-.25 * sqm);
		*Nsol = 2;
	}
	else if ( (sqp < 0.0) && (sqm >= 0.0))
	{
//		printf("\n case 3 ");
		sol[0] = 0.5 * (-xK + sqrt(sqm));
		sol[1] = 0.5 * (-xK - sqrt(sqm));
		sol[2] = 0.5 * xK;
		sol[3] = 0.5 * xK;
		soli[2] =  sqrt(-0.25 * sqp);
		soli[3] = -sqrt(-0.25 * sqp);
		*Nsol = 2;
	}
	else if ( (sqp < 0.0) && (sqm < 0.0))
	{
//		printf("\n case 4 ");
		sol[0] = -0.5 * xK;
		sol[1] = -0.5 * xK;
		soli[0] =  sqrt(-0.25 * sqm);
		soli[1] = -sqrt(-0.25 * sqm);
		sol[2] = 0.5 * xK;
		sol[3] = 0.5 * xK;
		soli[2] =  sqrt(-0.25 * sqp);
		soli[3] = -sqrt(-0.25 * sqp);
		*Nsol = 0;
	}
	
	for (i=0;i<4;i++)	sol[i] -= b/(4.0*a);
	return 0;
}

bool SquareMatrix::solveRotMat(std::complex<double> &eValue1,
							   std::complex<double> &eValue2,
							   std::vector<std::complex<double> > &evec1,
							   std::vector<std::complex<double> > &evec2,
							   int &denom1,
							   int &denom2){

// Outputs are, the two eigenvalues
// The two eigenvectors associated with the two eigenvalues
// Denom1 is the index of the unit vector in eigenvector 1
// Denom2 is the index of the unit vector in eigenvector 2
	std::vector<double> storeV;
	std::complex<double> unitComp (1.0,0.0);
	int i,j,result;
	double dd[5], sol[4], soli[4];
	int Nsol;
	bool done;
	std::vector<std::complex<double> > vresult;
	std::vector<std::complex<double> >::iterator compIter;
	std::vector<double> evec1Real, evec1Im, evec2Real, evec2Im;
	std::complex<double> *eValue;
	int iPair[4] = {-1,-1,-1,-1};
	int pairInd, pr;

	if (numberOfDims != 4) {
//		printf("Yikes!\n");
		return false;
	}

	//store = new SquareMatrix();
	storeV = v;
	denom1 = -1;
	denom2 = -1;

	dd[4] = 1.0; // The quartic coefficient
	done = getCharPolyCoeffs(&dd[3], &dd[2], &dd[1], &dd[0]);
//	printf("\n The quartic coeffs are %19.15f\n %19.15f\n %19.15f\n %19.15f\n %19.15f\n",
//		dd[4],dd[3],dd[2],dd[1],dd[0]);	
	result = quartic(dd, sol, soli, &Nsol); // This find eigenvalues, not eigenvectors

	//printf("\n");
	//for (int kk = 0; kk < 4; ++kk) {
	//	printf("Result of Matrix quartic Soln=%d sol=%11.5f soli=%11.5f\n",
	//				kk,sol[kk],soli[kk]);
	//}
	//printf("NSol is %d\n",Nsol); // number of real solutions


	// find the conjugate pairs
	// Look for a solution with nonzero imaginary part.
	// The first pair is iPair[0] and iPair[1], the second pair is iPair[2] and iPair[3]
	// iPair contains the index of the arrays sol and soli
	for (i = 0; i < 4; ++i) {
		if (soli[i] != 0.0) {
			iPair[0] = i;
			// Look for the conjugate of pair1
			for (j = iPair[0] + 1; j < 4; ++j) {
				if (soli[j] == -soli[iPair[0]] && sol[j] == sol[iPair[0]]) {
					iPair[1] = j;
					break;
				}
			}
			break;
		}
	}

	if (Nsol == 0) { // Only look for the other pair if the number of real solutions is zero
		switch (iPair[0]) {
			case 0:
				switch(iPair[1]) {
					case 1: iPair[2] = 2; iPair[3] = 3; break;
					case 2: iPair[2] = 1; iPair[3] = 3; break;
					case 3: iPair[2] = 1; iPair[3] = 2; break;
					default: /* printf("Failure1\n"); */ return false; break;
				}
				break;
			case 1:
				switch(iPair[1]) {
					case 0: iPair[2] = 2; iPair[3] = 3; break;
					case 2: iPair[2] = 0; iPair[3] = 3; break;
					case 3: iPair[2] = 0; iPair[3] = 2; break;
					default: /* printf("Failure2\n"); */ return false; break;
				}
				break;
			case 2:
				switch(iPair[1]) {
					case 0: iPair[2] = 1; iPair[3] = 3; break;
					case 1: iPair[2] = 0; iPair[3] = 2; break;
					case 3: iPair[2] = 0; iPair[3] = 1; break;
					default: /* printf("Failure3\n"); */ return false; break;
				}
				break;
			default: /* printf("Failure4\n"); */ return false; break;
		}
	}

	//printf(" Nsol=%d Pair 1 is %d and %d, Pair 2 is %d and %d\n",Nsol,iPair[0],iPair[1],iPair[2],iPair[3]);

	vresult.assign(3,0);
	bool retVal;
//	bool solnFound;
	int denom;
	int answerInd;

	answerInd = 0;
	for (pairInd = 0; pairInd < 2; ++pairInd) {
		pr = iPair[2*pairInd];
		if (pr < 0) {
//			printf("Found a real eigenvalue.. ignoring it\n");
			continue; // Don't look at axes (indicated by zero imaginary value
		}
		if (soli[pr] < 0.000001) {
//			printf("Found complex eigenvalue %13.9f   i %13.9f almost real, hence ignoring it\n",sol[pr],soli[pr]);
			continue;
		}
		//solnFound = false;
		eValue = new std::complex<double>(sol[pr], soli[pr]);
		retVal = evSolver(*eValue,vresult,denom);
		if (!retVal) {/*printf("Catastrophe at solver\n");*/ delete eValue; return false;}
//		if (false) {
//			printf("Evalue is %11.5f i %11.5f\n",eValue->real(), eValue->imag());
//			switch (denom) {
//				case 0:
//					printf("Result: y/x %12.7g   i%12.7g\n",vresult[0].real(),vresult[0].imag());
//					printf("Result: z/x %12.7g   i%12.7g\n",vresult[1].real(),vresult[1].imag());
//					printf("Result: w/x %12.7g   i%12.7g\n",vresult[2].real(),vresult[2].imag());
//					break;
//				case 1:
//					printf("Result: x/y %12.7g   i%12.7g\n",vresult[0].real(),vresult[0].imag());
//					printf("Result: z/y %12.7g   i%12.7g\n",vresult[1].real(),vresult[1].imag());
//					printf("Result: w/y %12.7g   i%12.7g\n",vresult[2].real(),vresult[2].imag());
//					break;
//				case 2:
//					printf("Result: x/z %12.7g   i%12.7g\n",vresult[0].real(),vresult[0].imag());
//					printf("Result: y/z %12.7g   i%12.7g\n",vresult[1].real(),vresult[1].imag());
//					printf("Result: w/z %12.7g   i%12.7g\n",vresult[2].real(),vresult[2].imag());
//					break;
//				case 3:
//					printf("Result: x/w %12.7g   i%12.7g\n",vresult[0].real(),vresult[0].imag());
//					printf("Result: y/w %12.7g   i%12.7g\n",vresult[1].real(),vresult[1].imag());
//					printf("Result: z/w %12.7g   i%12.7g\n",vresult[2].real(),vresult[2].imag());
//					break;
//				default:
//					break;
//			}
//		}
		if (answerInd == 0) {
			// populate eigenvector 1
			denom1 = denom;
			eValue1 = *eValue;
			evec1.clear();
			for (j = 0; j < 4; ++j) {
				if (j < denom) {
					evec1.push_back( vresult[j]);
				} else if (j == denom) {
					evec1.push_back( unitComp);
				} else {
					evec1.push_back( vresult[j - 1]);
				}
			}
		}else {
			// populate eigenvector 2
			denom2 = denom;
			eValue2 = *eValue;
			evec2.clear();
			for (j = 0; j < 4; ++j) {
				if (j < denom) {
					evec2.push_back( vresult[j]);
				} else if (j == denom) {
					evec2.push_back( unitComp);
				} else {
					evec2.push_back( vresult[j - 1]);
				}
			}
		}
		//printf("PairInd=%d, AnswerInd=%d, pr=%d\n",pairInd,answerInd,pr);
		++answerInd;
		delete eValue;
	}
	return true;
}

bool SquareMatrix::constructRotMat(std::vector<double> &spanVec1, std::vector<double> &spanVec2, double rotRadians){

	// This function assumes that spanvec1 and spanvec2 are mutually orthogonal and are of unit length.
	// It constructs a rotation matrix for rotating from spanVec1 to spanVec2 by an angle rotRadians.

	double costhetaM1, sintheta, mult1, mult2, unitVecValue, rvalue;
	int colIndex, rowIndex;

	if ((spanVec1.size() != numberOfDims) || (spanVec2.size() != numberOfDims)) {
//		printf("The dim of this matrix (%d) spanvec1(%d) and spanvec2(%d) should all be the same\n",
//			numberOfDims, spanVec1.size(), spanVec2.size());
		{1.0/0.0;};
	}

	// If the rotation is Tiny, return the identity matrix
	if (abs(rotRadians) < 0.000001) {
		initIdentity();
		return true;
	}

	costhetaM1 = cos(rotRadians) - 1.0;
	sintheta = sin(rotRadians);

	// Construct the rotation matrix column by column
	for (colIndex = 0; colIndex < numberOfDims; ++colIndex) {
		mult1 = spanVec1[colIndex] * costhetaM1 - spanVec2[colIndex] * sintheta;
		mult2 = spanVec1[colIndex] * sintheta + spanVec2[colIndex] * costhetaM1;
		for (rowIndex = 0; rowIndex < numberOfDims; ++rowIndex) {
			unitVecValue = (rowIndex == colIndex) ? 1.0 : 0.0; //This is the canonical axis vector. The component is 1 or 0
			rvalue = spanVec1[rowIndex]*mult1 + spanVec2[rowIndex]*mult2 + unitVecValue;
			setElement(rowIndex,colIndex,rvalue);
		}
	}

	return true;
}

bool SquareMatrix::constructRotMatCumul(std::vector<double> &spanVec1, std::vector<double> &spanVec2, double rotRadians,
										SquareMatrix &cumul){
	// Constructs a rotation matrix, then multiplies it by matrix in 'cumul'
	// The result is stored in cumul.

	std::vector<double> tempV;

	tempV.assign(numberOfDims * numberOfDims, 0);

	constructRotMat(spanVec1,spanVec2,rotRadians);

	if (numberOfDims == 3) {
		matrixMult3(v, cumul.v, tempV);
	} else if (numberOfDims == 4) {
		matrixMult4(v, cumul.v, tempV);
	}

	cumul.v = tempV;
	return true;
}
