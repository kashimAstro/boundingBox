#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "ofxAssimpModelLoader.h"

class xApp : public ofBaseApp {
	public:
		ofEasyCam cam;
		ofShader cap;
		ofImage icap;
		ofxAssimpModelLoader model;
		ofSpherePrimitive sphere;

		vector<ofVec3f> bBoxAssimp;
		vector<ofVec3f> bBoxSphere;
		int w,h;

		vector<ofVec3f> ofxBBox(ofMesh mesh) {
		  vector<ofVec3f> res;
		  if (mesh.getNumVertices() > 0) {
			  float min_x, max_x, min_y, max_y, min_z, max_z;
			  min_x = max_x = mesh.getVertex(0).x;
                          min_y = max_y = mesh.getVertex(0).y;
                          min_z = max_z = mesh.getVertex(0).z;
		          for (int i = 0; i < mesh.getNumVertices(); i++) {
			            if (mesh.getVertex(i).x < min_x) min_x = mesh.getVertex(i).x;
			            if (mesh.getVertex(i).x > max_x) max_x = mesh.getVertex(i).x;
			            if (mesh.getVertex(i).y < min_y) min_y = mesh.getVertex(i).y;
			            if (mesh.getVertex(i).y > max_y) max_y = mesh.getVertex(i).y;
			            if (mesh.getVertex(i).z < min_z) min_z = mesh.getVertex(i).z;
			            if (mesh.getVertex(i).z > max_z) max_z = mesh.getVertex(i).z;
			  }
		          ofVec3f size = ofVec3f(max_x-min_x, max_y-min_y, max_z-min_z);
		          ofVec3f center = ofVec3f((min_x+max_x)/2, (min_y+max_y)/2, (min_z+max_z)/2);
			  res.push_back(size);
                          res.push_back(center);
		  }	
		  return res;
		}

		void setup(){
			ofSetFrameRate(150);

			w=ofGetScreenWidth();
			h=ofGetScreenHeight();

			model.loadModel("model.obj");
			bBoxAssimp = ofxBBox( model.getMesh(4) );
			sphere.setRadius(85);
			bBoxSphere = ofxBBox(sphere.getMesh());

			cap.load("cap");
			ofDisableArbTex();
			icap.loadImage("cap1.jpg");
		}

		void update(){
			ofSetWindowTitle(ofToString(ofGetFrameRate()));
		}

		void draw(){
			ofBackgroundGradient(155,0);
			cam.begin();
			ofEnableDepthTest();
			ofPushMatrix();
				ofTranslate(450,0,0);
				ofDrawBox(bBoxSphere[1], bBoxSphere[0].x, bBoxSphere[0].y, bBoxSphere[0].z);

				cap.begin();
			        cap.setUniformTexture("tMatCap", icap, 1);
				sphere.draw();
				cap.end();

			ofPopMatrix();
			
			ofPushMatrix();
				cap.begin();
			        cap.setUniformTexture("tMatCap", icap, 1);
				model.drawFaces();
				cap.end();

				ofNoFill();
	 			ofDrawBox(bBoxAssimp[1], bBoxAssimp[0].x, bBoxAssimp[0].y, bBoxAssimp[0].z);
			ofPopMatrix();
			ofDisableDepthTest();
			cam.end();
		}

		void keyPressed(int key){

		}
};

int main( ){
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1280, 720, OF_WINDOW);
	ofRunApp(new xApp());
}
