#pragma once

#include <fstream>
#include <sstream>
#include <cstdlib>
#include "ofMain.h"

class Triangle {
public:
	Triangle(int i1, int i2, int i3) { vertInd[0] = i1, vertInd[1] = i2, vertInd[2] = i3; }
	int vertInd[3];
};

class MyMesh {
public:
	vector<glm::vec3> verts;
	vector<Triangle> triangles;

	void drawMesh();
};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void loadFile(string fileName);

		
		ofEasyCam cam;

		MyMesh mesh;
		
};
