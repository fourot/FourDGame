
#ifndef TRACKBALL_DOT_H
#define TRACKBALL_DOT_H

/*
 * (c) Copyright 1993, 1994, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(TM) is a trademark of Silicon Graphics, Inc.
 */
/*
 * trackball.h
 * A virtual trackball implementation
 * Written by Gavin Bell for Silicon Graphics, November 1988.
 */



////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
//////////////////////////// fourot stuff


#define OGLWINDOWHEIGHT 600
#define OGLWINDOWWIDTH 1200
#define OUTERWINDOWTOPMARGIN 150
#define OUTERWINDOWHEIGHT (OGLWINDOWHEIGHT + OUTERWINDOWTOPMARGIN)
#define OUTERWINDOWWIDTH (OGLWINDOWWIDTH)

#define NUMBEROFFIGS 11 // The number of figures: six 3D and five 4D figures
#define INTERSECTION2DLINERADIUS 1.1
#define NUMBEROFLINESINQUADRANT 15
#define NUMBEROFLINESINCIRCLE (NUMBEROFLINESINQUADRANT*4)
#define FOVEALANGLE 45
#define TRANSLATIONOF2DFIGURES 3.5

#define DEFAULTSLIDERPROJ3D2D 1.25
#define DEFAULTSLIDERPROJ4D3D 1.25

#define DEFAULTUSERSPACEDISTANCE 0.0 
#define DEFAULTEYE3D2D 0.15

#define COUNTDOWNDURATION 5.0 //Seconds
#define TIMERREPEATTIME 0.05 // seconds

#define THIRD 0.33333333333
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define MAX_2D_SIDES 8
#define MIN_2D_SIDES 3
#define POLYGONLINEWIDTH 10.0
#define GLPOINTSIZE 20.0

#define MAX_3D_VERTS 20 // Max number of vertices for 3D figures.
#define MIN_3D_VERTS 4  // Min number of vertices for 3D figures.
#define MAX_3D_EDGES 30 // Max number of edges for 3D figures.
#define MIN_3D_EDGES 6  // Min number of edges for 3D figures.
#define MAX_3D_FACES 20 // Max number of faces for 3D figures.
#define MIN_3D_FACES 4  // Min number of faces for 3D figures.

#define MAX_4D_VERTS 600  // Max number of vertices for 4D figures.
#define MIN_4D_VERTS 5    // Min number of vertices for 4D figures.
#define MAX_4D_EDGES 1200  // Max number of edges for 4D figures.
#define MIN_4D_EDGES 10   // Min number of edges for 4D figures.
#define MAX_4D_FACES 1200 // Max number of faces for 4D figures.
#define MIN_4D_FACES 10   // Min number of faces for 4D figures.
#define MAX_4D_CELLS 600  // Max number of cells in 4D figures.
#define MIN_4D_CELLS 5    // Min number of cells in 4D figures.



#define LAMBDA_FOR_PARALLEL 1E7
#define LAMBDA_FOR_COINCIDENCE 1E10

#define TENDEGREESINRADIANS 0.1745329
#define TWODSUCCESSANGLE TENDEGREESINRADIANS

#define FIGNAMESYVALUE 0.85
#define COUNTDOWNDISPLAYYVALUE 0.85
#define ANGULARDISTANCEYVALUE 0.83
#define ACCURACYBARTOP (INTERSECTION2DLINERADIUS*1.28)
#define ACCURACYBARMIDDLE (INTERSECTION2DLINERADIUS*1.25)
#define ACCURACYBARBOTTOM (INTERSECTION2DLINERADIUS*1.22)
#define MAXACCURACYXVALUE 1.44
#define ACCURACYGREENANGLE (7*M_DEGREES_TO_RADIANS) // SEVEN DEGREES
#define ACCURACYWINANGLE (5*M_DEGREES_TO_RADIANS) // FIVE DEGREES
#define ACCURACYWINANGLE3D (5*M_DEGREES_TO_RADIANS) // five DEGREES
#define ACCURACYGREENPROPORTION (ACCURACYGREENANGLE*M_1_PI)

#define COSINE45 (0.70710678)

#define OSCILLATION_PERIOD_SECONDS 8.0
#define BASE_DEGREES_PER_OSCILLATION 321.723
#define CONSTANT_DEGREES_PER_OSCILLATION 11.9 //Adds to base_degrees_... on each cycle 

#define OSCILLATION_3D_PERIOD (OSCILLATION_PERIOD_SECONDS) // Define the 3D period to be the same as the 2D period.
#define OSCILLATION_ANGLE3D_1 (BASE_DEGREES_PER_OSCILLATION*M_DEGREES_TO_RADIANS) // same as base 2D angle
#define OSCILLATION_ANGLE3D_2 (-(BASE_DEGREES_PER_OSCILLATION-12)*M_DEGREES_TO_RADIANS) // nearly the same as base 2D angle!

#define OSCILLATION_4D_PERIOD (OSCILLATION_PERIOD_SECONDS) // Define the 4D period to be the same as the 2D period.
#define OSCILLATION_ANGLE4D_1 (BASE_DEGREES_PER_OSCILLATION*M_DEGREES_TO_RADIANS) // same as base 2D angle
#define OSCILLATION_ANGLE4D_1_DUAL (OSCILLATION_ANGLE4D_1*0.26) // angle to be used in the dual plane
#define OSCILLATION_ANGLE4D_2 (-(BASE_DEGREES_PER_OSCILLATION-12)*M_DEGREES_TO_RADIANS) // nearly the same as base 2D angle!
#define OSCILLATION_ANGLE4D_2_DUAL (OSCILLATION_ANGLE4D_2*0.26) // angle to be used in the dual plane

#define ACCURACYWINANGLE4DSQ ( 11 * 11 * M_DEGREES_TO_RADIANS * M_DEGREES_TO_RADIANS*2.0)
#define ACCURACYANGLE4D ( 20 * M_DEGREES_TO_RADIANS)

#define AXISSHIFTIN3DDEMO (80*M_DEGREES_TO_RADIANS)
#define INACTIVEANGLE (-1000.0)

#define NUMBERSDISPLAY_DISTANCEFACTOR 1.09
#define NUMBERSDISPLAY_EXTRA_X -0.05
#define NUMBERSDISPLAY_EXTRA_Y -0.03
#define NUMBERSDISPLAY_EXTRA_Z 0.01


enum IntersectionObjectType {
	noObject,
	intersectingEdge,
	coincidentEdge,
	coincidentVertex,
	intersectingFace
};

enum StateMouseState {
	mouseHasJustGoneDown,
	mouseIsDown,
	mouseHasJustGoneUp,
	mouseIsUp
};


// from:  figdata.c Generated on Sun May 14 18:28:27 2017
typedef struct figInfo {
 int numDims;                 // Number of dimensions (will be 3 or 4)
 int numVerts;                // Number of vertices in the whole figure
 int numEdges;                // Number of edges in the whole figure
 int numFaces;                // Number of faces in the whole figure
 int numCells;                // Always 1 for 3D figures
 int numVertsPerEdge;         // Always 2, can't be anything else
 int numVertsPerFace;         // Same as the number of edges per face
 int numVertsPerCell;         // Number of vertices in each cell (in 3d it is the same as numVerts)
 int numEdgesPerFace;         // Number of edges in a face, which is a regular polygon. Same as numVertsPerFace
 int numEdgesPerCell;         // Number of edges in a cell
 int numFacesPerCell;         // Number of faces in each cell
 int numFacesPerVert;         // Number of faces meeting at a vertex
 int numFacesPerEdge;         // Number of faces meeting at an edge
 int numCellsPerVert;         // Number of cells meeting at a vertex (always 1 for 3D figures)
 int numCellsPerEdge;         // Number of cells meeting at an edge (either 2 or 3, for 3d and 4d respectively)
 int numCellsPerFace;         // Number of cells meeting at a Face (1 for 3d, 2 for 4d)
 double dihedralCosine;        // Cosine of the angle between faces in a cell
 double cellRadius;            // Radius of an individual cell in a 4d figure
 double cellCentreRadius;      // Distance from the centre of figure to the centre of an individual cell
 double faceCentreRadius;      // Distance from the centre of figure to the centre of an individual face (3D)
 double *vertex;               // Pointer to the array of vertices (number of vertices X number of dimensions)
 int *edge;                   // Pointer to the array of edges (an edge is a pair of vertex numbers)
 int *vertToEdge;             // Pointer to the array of edges per vertex (number of vertices X number of edges meeting at a vertex)
 int *face;                   // Pointer to the array of faces (number of faces X edges per face)
 int *edgeToFace;             // Pointer to the array of faces per edge (number of edges X faces per edge)
 int *faceToVert;             // Pointer to the array of vertices per face (number of faces X vertices per face)
 int *vertToFace;             // Pointer to the array of faces per vertex (number of vertices X faces meeting at a vertex)
 int *faceToCell;             // Pointer to the array of cells per face (number of faces X cells per face (two in 4D))
 double *faceNormal;           // Pointer to the face normals (number of faces X number of dimensions)
 int *cell;                   // Pointer to the array of cells (a cell is a set of face numbers)
 double *cellNormal;           // Pointer to the cell normals (number of cells X number of dimensions)
 int *cellToEdge;             // Pointer to the edges per cell (number of cells X edges per cell)
 int *cellToOpposite;         // Pointer to the opposite cell per cell (number of cells X 1, but not for K005)
} FigInfo;


struct Intersection2DInfo {
	double *verts; // point to current vertices
	int sides; // same as currFig2D

	double rotated2DMov [MAX_2D_SIDES][2]; // The rotated vertices of the 2D figure on the Mov
	double rotated2DTarg [MAX_2D_SIDES][2]; // The rotated vertices of the 2D figure on the Targ
	double intersection2DMov [4][2]; // The Intersections of the 2D figure
	double intersection2DTarg [4][2]; // The Intersections of the 2D figure on the Targ
	int intersectionColorIndexMov [4];
	int intersectionColorIndexTarg [4];
	double muMov[2]; // Distance of the two intersection points from the centre of the intersection line.
	double muTarg[2]; // Distance of the two intersection points from the centre of the intersection line.
	double lineEndPointsMov[2][2];
	double lineHalfLength;
	int countIntersectsions2DMov;
	int countIntersectsions2DTarg;
	double displacementLine2D; // Distance of the intersection plane from the origin.
	double normalLine2D; // Angle of the normal to the intersection line (initialise to 0 = vertical normal = horizontal line)
	double normalVector2D[2]; // The vector corresponding to normalLine2D (vertical line)

	double angle2DMov; // Rotation angle for Mov figure (as displayed)
	double angle2DTarg; // Rotation angle for Targ figure (as displayed)

	// Following are used to convert from mouse 2D screen position coords to x y coords in the 3d scene
	double convertFromMouseTo3D;
	double mouse3DxInitialPosition;
	double mouse3DyInitialPosition;
	double mouse3DRadius;

	// Following are to display the countdown graphics
	double falseStartMov;
	double trueStartMov;
	double falseStartTarg;
	double trueStartTarg;
	double countdownDispNum;
	int displayNumber;
	int prevdisplayNumber;

	// The following are used in gameplay.
	double mouseAngleStart;
	double mouseAngleNow;
	double angleMovOriginal;
	double angularDistance;
	double prevAngularDistance;
	double cumulativeMotionAngularError;
	double cumulativeAngularMotion;
	int angularErrorCount;
	double successTime; // The time to completion
	double finalScore;
};


void project4Dto3D(double *v4D, double *v3D, int count, double dPersp);
void randomVec3D (double * vec);

void calcNormalBivector4DFromVectors (double *v1, double *v2, struct Bivector4D *biv);

void copyRotor( struct Rotor4D *r1,  struct Rotor4D *r2);
void copyBivector( struct Bivector4D *r1,  struct Bivector4D *r2);
void sortFloats(int Kount, double *values, int* vind);

struct Bivector4D {
	double e12;
	double e13;
	double e14;
	double e23;
	double e24;
	double e34;
};

struct trackballInfo {
	double trackballsize;
	double littleballsize;
	double rsquared; // trackballsize ^2
	double t; //The horizontal distance from the centre of the trackball to the centre of the little ball 
	double p; // The horizontal distance from the centre of the trackball to the point where the trackball meets the little ball.
	double axis[3]; // The computed axis
	double currentxyz[3]; // Current mouse posn
	double prevxyz[3]; // Prev mouse posn
	double rotangle; // the computed angle of rotation.
	double myquat[4]; //quaternion resulting from calculation
	int zone; // Where the mouse is located relative to the centre of the trackball
	double mousex2D;
	double mousey2D;

	// 4D
	int horrible4DFlag;
	double prevMouse4D[3];
	double currMouse4D[3];
	double normalisedCurr[4];
	double normalisedPrev[4];
	int insideTrackballArea;
};


struct IntersectPoint {
	enum IntersectionObjectType iType;
	int objectIndex;
	int faceIndexForColour; // This for a given point applies to the new edge between this point and the previous point
	double p[3]; // The actual intersection point
};

struct Intersection3DInfoGeneral {
	// 3D info that applies to both figure and target.
	double userPlaneDeclension; // varies from zero (the normal is the y axis) to Pi/2 (the normal is the positive z axis)
	double userPlaneNormal[3];
	double userPlaneDistance;
	FigInfo *fig; // The current figure

	double baseAxisOfDemo[3];
	double reducedTime; // Used for the 3D demo
	double previousReducedTime; // Used for the 3D demo
	double basePositionDemoQuat[4];
	int displayNumber;
	int prevDisplayNumber;

	double diffAngle;
	double diffAxis[3];
	double diffQuat[4];
	double cumulativeAngularTravel;
	double initialAngularDifference;
	double successTime;
	double finalScore;
	double escapeAngle;
	double cumulativeEscape;
	int firstEscape;
};

struct Intersection3DInfo {

	double rotatedVerts[MAX_3D_VERTS][3];
	double rotatedFaceNormals[MAX_3D_VERTS][3];

	double dotProdOfRotVertsWithUserNormal[MAX_3D_VERTS];

	double distOfRotVertsFromUserPlane[MAX_3D_VERTS];
	double finalPositionQuaternion[4]; // The quaternion which when applied in a double rotation (with it's conjugate) leads to the rotated final position

	double edgeLambda[MAX_3D_EDGES];
	int numberIntersections;
	int firstCoincidentEdge;
	int numberCoincidentEdges;
	int firstCoincidentVert;
	int firstIntersectingEdge;
	int numberCoincidentVerts;
	struct IntersectPoint iPoint[MAX_3D_FACES]; // These are the intersections to be plotted
	int numberIntersectionsToBePlotted;

	// These deal with the countdown process
	// Once the game is underway, truestartaxis, truestartangle and truestartquat refer to the current position
	double trueStartAxis[3];
	double trueStartAngle;
	double trueStartQuat[4];
	double falseStartAxis[3];
	double falseStartAngle;
	double falseStartQuat[4];
	struct ColValue *randomColors;
};

struct Rotor4D {
	double scalar;
	struct Bivector4D b;
	double e1234;
};

struct RotorComponents {
	struct Bivector4D biv;
	double angle; // This is the full angle
};

struct Intersection4DInfoGeneral {
	// 4D info that applies to both figure and target.
	double userSpaceNormal[4];
	double userSpaceDistance;
	FigInfo *fig; // The current figure

	struct Bivector4D demoRotationPlanes;

	struct RotorComponents basePosn;
	struct Rotor4D basePosnRot; // The rotor for going from the canonical posn to the base posn.	
	struct Rotor4D compositeRot; // The rotor from going from the canonical position to the displayed position (newposnrot * baseposnrot)

	// Structures for the 4D countdown;
	struct Rotor4D trueStartRotTarg;
	struct Bivector4D falseStartBivTarg;
	double falseStartTargAngle1, falseStartTargAngle2;

	struct Rotor4D trueStartRotFig;
	struct Bivector4D falseStartBivFig;
	double falseStartFigAngle1, falseStartFigAngle2;


	double reducedTime; // Used for the 4D demo
	double previousReducedTime; // Used for the 4D demo
	int displayNumber;
	int prevDisplayNumber;

	struct RotorComponents trueStartPosition;
	struct RotorComponents falseStartPosition;
	// Some stuff relevant to the solution;
	double cumulativeAngularTravel;
	double initialAngularDifference1,initialAngularDifference2;
	double successTime;
	double finalScore;
	double requiredAngle, fspeed, faccuracy, fscore;

	double startEscapeTime;
	int firstEscape;
	int currentCellInWireframe;
	int oppositeCellInWireframe;

	double projectDist4D3D; // Used for perspective projection from 4D to 3D.
	double projectDist3D2D;
	double rightEyeX3D2D; // The x position of the right eye in stereo projection in 3d.
	double frustum_ag;
	double frustum_bg;
	double frustum_topf;
	double frustum_botf;
	double frustum_near;
	double frustum_far;

	double surroundCircleRadius;
	double surroundCircleZ;

	int keyDownXAxis,keyDownYAxis,keyDownZAxis,keyDownWAxis,keyDownShift,keyDownCtrl;
	int keyDownSpeedUp,keyDownSlowDown;
	struct Bivector4D trackBBiv, solvBiv1, solvBiv2, prevSolvBiv1;
	struct Rotor4D figRotor;
	struct Rotor4D solutionRotor;
	struct Rotor4D escapeRotor;
	struct Bivector4D escapeBiv;
	double cumulativeAngularEscape;
	double solvangle1,solvangle2, prevangle;
	int autosolve4D;
	double kbRotation, escRotation;

	int prevDisplayPositionOfSolvBiv1;
	int displayPositionOfSolvBiv1;
	double angleBiv[12], asigns[12];
	int vinds[12];
	int solveType4D;
};

struct EdgeIntersection { //One of these for each edge that intersects with the user space (in array edgeIntsct)
	int globalEdgeIndex; // ID of the edge that intersects
    double intersectionPoint[4]; // The point at which this intersection
    double intersectionPointProjTo3D[3]; // The point at which this intersection
    double intersectionPointProjTo3DLeftEye[3]; // The point at which this intersection
    double intersectionPointProjTo3DRightEye[3]; // The point at which this intersection
    int faceIntersectionIndex[5]; // The indices of faces (in faceIntsct) that must also intersect. Max number of face intersections per edge.
    int faceIntersectionIndexInd; // The number of entries in faceIntersectionIndex
};

struct FaceIntersection { // One of these for each face that intersects with the user space (in array faceIntsct)
	int globalFaceIndex; // ID of the face that intersects
    int edgeIntersectionIndex[2]; // Indices of the intersecting edges (int edgeIntsct) for this face, can only be 2 at most.
    int edgeIntersectionIndexInd; // The number of entries in edgeIntersectionIndex
    int cellIntersectionIndex[2]; // indices of the cells (int cellIntsct) that must also intersect. 2 at most.
    int cellIntersectionIndexInd; // The number of entries in cellIntersectionIndex
};

struct CellIntersection { // One of these for each cell that intersects with the userspace (in cellIntsct)
	int globalCellIndex; // Id of this cell
    int faceIntersectionIndex[10];// Indices of intersecting faces for this cell (int faceIntsct). 10 at most, for dodecahedral cell in k120.
    int faceIntersectionIndex1[10];// face intersections per cell.
    int faceIntersectionIndexInd; // The number of entries in faceIntersectionIndex
};

struct IntersectionObject {
	struct EdgeIntersection edgeIntsct[MAX_4D_EDGES]; // Intersecting edges, indexed by edgeIntersectionIndex;
	struct FaceIntersection faceIntsct[MAX_4D_FACES]; // Intersecting faces, indexed by faceIntersectionIndex;
	struct CellIntersection cellIntsct[MAX_4D_CELLS];  // Intersecting cells, indexed by cellIntersectionIndex;
	// The indices below are used in constructing the intersection figure.
	// Once all the intersections have been constructed, the indices below show the number of intersections of different type
	int edgeIntersectionIndex;
	int faceIntersectionIndex;
	int cellIntersectionIndex;
};

struct Intersection4DInfo { // This struct is instantiated separately for fig and target.
	struct IntersectionObject iObj;
	double rotatedVerts[MAX_4D_VERTS][4];
	double rotatedCellNormals[MAX_4D_CELLS][4];
	double dotProdOfRotVertsWithUserNormal[MAX_4D_VERTS];
	double distOfRotVertsFromUserPlane[MAX_4D_VERTS];
	double numberCoincidentVerts;
	double edgeLambda[MAX_4D_EDGES];
	double verts4DProjectedTo3D[MAX_4D_VERTS][3];
	double verts4DTo3DLeftEye[MAX_4D_VERTS][3];
	double verts4DTo3DRightEye[MAX_4D_VERTS][3];
	struct ColValue *randomColors;	
};

struct ModelInfo {
	int modelFlag; // Set this true if a file of the 4D figure is needed
	int mIndex;
	int numOfModelFaces;
	int numOfModelEdges;
	int vertsPerFace[MAX_4D_VERTS];
	int edgeNum[2*MAX_4D_VERTS];
	int vertNum[2*MAX_4D_VERTS];
	int faceStartIndex[MAX_4D_VERTS];
	int maxVertFreq;
	int vertFreq[10];
	int edgeToFaceModel[MAX_4D_VERTS][2];
	double edgeLength[MAX_4D_VERTS];
	double modelVert[2*MAX_4D_VERTS][3];
	struct Rotor4D modelPosn;
};

#endif // for include file recursion
