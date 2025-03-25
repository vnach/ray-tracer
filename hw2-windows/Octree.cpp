#include "Octree.h"

#include <iostream>
#include <vector>
using namespace std;
#include "Octree.h"
#include "Transform.h"

// Idea: Once octree is set up use methods inside the raytracer file

// Dividing the scene into a cube of 8 boxes
#define TopRightF 1
#define TopRightB 5
#define TopLeftF 0
#define TopLeftB 3
#define BotRightF 2
#define BotRightB 6 
#define BotLeftF 4 
#define BotLeftB 7

// create a struct for points in box
// Think of a "point" as a collision with a object in scene
struct Point {
	int x, y, z;
	vec3 default = vec3(-1, -1, -1);
	Point() {
		default;
	}

	Point(int a, int b, int c) {
		default = vec3(a, b, c);
	}
};

// Octree class
class Octree {
	// if point == NULL, internal node (non-leaf/root node)
	// if point has vector (-1,-1,-1) then empty node
	Point* point;

	// Get cube(i.e. scence's) boundary with left most and right most vertices
	Point* topLeftF, * botRightB;
	// Set up children
	vector<Octree*> child;

public:
	// Constructor
	Octree()
	{
		// Declare empty node
		point = new Point();
	}

	// Constructor for one vector
	Octree(vec3 vector)
	{
		// Declares a point node
		point = new Point(vector[0], vector[1], vector[2]);
	}

	// Constructor with six arguments
	Octree(vec3 v1, vec3 v2) {
		// Constructs the Octree with defined boundaries
		//if (v2[0] < v1[0] || v2[1] < v1[1] || v2[2] < v2[2]) {
		//	cout << "Invalid boundary" << endl;
		//	return;
		//}

		//// Set up empty node and cube(i.e. "scene") boundary
		//topLeftF = new Point(v1[0], v1[1], v1[2]);
		//botRightB = new Point(v2[0], v2[1], v2[2]);
		//point = nullptr;

		//// Dividing a box into 8 null children
		//child.assign(8, nullptr);
		//for (int i = TopLeftF; i <= BotLeftB;++i) {
		//	child[i] = new Octree();
		//}
	}

	// Inserts a point in octree
	void insertPoint(int x, int y, int z) {

		// If the point already exists in the octree
		//if (find(x, y, z)) {
		//	cout << "Point already exists in octree" << endl;
		//	return;
		//}

		//// Check if the point is out of scene
		//if (x < topLeftF->x || y < botRightB->y) {
		//	cout << "Point out of bounds" << endl;
		//	return;
		//}
	}
};


