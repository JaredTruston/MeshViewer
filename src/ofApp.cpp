#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Sets distance of the camera from the origin
	cam.setDistance(30.0);
	// Sets the camera to look at the origin
	cam.lookAt(glm::vec3(0, 0, 0));
	// Sets background color of scene
	ofSetBackgroundColor(ofColor::black);

	/*
	// Hardcode test geometry
	//
	mesh.verts.push_back(glm::vec3(10, 0, 0));		// Vertex 0
	mesh.verts.push_back(glm::vec3(15, 0, 0));		// Vertex 1
	mesh.verts.push_back(glm::vec3(10, 5, 0));		// Vertex 2
	mesh.triangles.push_back(Triangle(0, 1, 2));	// Triangle 0

	mesh.verts.push_back(glm::vec3(10, 0, 5));		// Vertex 3
	mesh.triangles.push_back(Triangle(0, 3, 2));	// Triangle 1

	mesh.triangles.push_back(Triangle(3, 1, 2));	// Triangle 2

	mesh.triangles.push_back(Triangle(0, 3, 1));	// Triangle 3
	*/
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	// Sets transformations for view of the camera
	cam.begin();
	ofDrawGrid();
	ofSetColor(0, 255, 0);  // red, green, blue components for RGB space

	// encapsulate this code in a "drawAxis()" method.
	//
	ofSetColor(ofColor::green);
	ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(0, 5.0, 0));
	ofSetColor(ofColor::red);
	ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(5.0, 0, 0));
	ofSetColor(ofColor::blue);
	ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(0, 0, 5.0));


	// connectivity 
	//
	mesh.drawMesh();

	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

void ofApp::loadFile(string fileName)
{
	// clears verts and triangles vectors
	mesh.verts.clear();
	mesh.triangles.clear();

	ifstream inputStream;	// input stream
	string read;			// reads from input stream
	float ver1, ver2, ver3;	// temporarily stores vertices of triangles
	int i1, i2, i3;			// temporarily stores indices of triangle vertices
	string tempString;		// temporarily stores string read from input stream
	
	// open file
	inputStream.open(fileName);
	
	if (!inputStream) // check if file opening failed
	{
		cout << "File open failed";
		exit();	// special system call to abort program
	}
	else {
		// read from input stream
		while (inputStream >> read) {
			if (read == "v") {		// check for a v to denote vertex
				// reads vertices from input stream
				inputStream >> ver1 >> ver2 >> ver3;

				// adds vertices to mesh's vertices vector
				mesh.verts.push_back(glm::vec3(ver1, ver2, ver3));
				
				//cout << ver1 << " " << ver2 << " " << ver3 << endl;
			}
			else if (read == "f") { // check for an f to denote face
				// reads indices of triangle vertices from input stream
				inputStream >> tempString;
				i1 = stoi(tempString.substr(0, tempString.find("/"))) - 1;
				inputStream >> tempString;
				i2 = stoi(tempString.substr(0, tempString.find("/"))) - 1;
				inputStream >> tempString;
				i3 = stoi(tempString.substr(0, tempString.find("/"))) - 1;

				// adds indices of triangle's vertices to mesh's triangle vector
				mesh.triangles.push_back(Triangle(i1, i2, i3));
				
				//cout << i1 << " " << i2 << " " << i3 << endl;
			}
		}
	}
	// close file
	inputStream.close();

	// print mesh diagnostic information
	cout << "Number of Vertices: " << mesh.verts.size() << endl;
	cout << "Total Number of Faces: " << mesh.triangles.size() << endl;
	cout << "Size of Mesh (in kB): " << sizeof(mesh.verts[0]) * mesh.verts.size() + sizeof(mesh.triangles) * mesh.triangles.size() << endl;

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
	// Reads in files dragged into window
	loadFile(dragInfo.files[0]);
}

//--------------------------------------------------------------
void MyMesh::drawMesh()
{
	// Set color and no fill for Triangle
	ofSetColor(ofColor::white);
	ofNoFill();

	// integer variables to hold vertices of Triangle
	int v1, v2, v3;

	// Iterate through and draw each Triangle in Mesh
	for (Triangle t : triangles) {
		// Record vertices of triangle
		v1 = t.vertInd[0];
		v2 = t.vertInd[1];
		v3 = t.vertInd[2];

		ofDrawTriangle(verts[v1], verts[v2], verts[v3]);
	}
}
