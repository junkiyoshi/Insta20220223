#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(3);
	ofEnableDepthTest();

	this->font_size = 80;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);
	ofRotateY(ofGetFrameNum() * -1.5);

	string word = "0123456789";
	int sample_count = 300;

	for(int i = 0; i < 60; i++) {

		int word_index = ofRandom(word.size());
		auto radius = 200 + i - 30;
		glm::vec3 base_location = glm::vec3(0, (int)(ofRandom(600) + ofGetFrameNum() * ofRandom(3, 8)) % 600 - 300, 90);
		auto rotation_y = glm::rotate(glm::mat4(), ofRandom(-PI, PI), glm::vec3(0, 1, 0));

		ofPath chara_path = this->font.getCharacterAsPoints(word[word_index], true, false);
		vector<ofPolyline> outline = chara_path.getOutline();

		ofFill();
		ofSetColor(0);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
			for (auto& vertex : vertices) {

				auto location = vertex - glm::vec3(this->font_size * 0.5, this->font_size * 0.5, 0);
				location.x *= -1;
				location = glm::vec4(base_location + location, 0) * rotation_y;
				location = glm::normalize(location) * radius;
				ofVertex(location);
			}
		}
		ofEndShape(true);

		ofNoFill();
		ofSetColor(255);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
			for (auto& vertex : vertices) {

				auto location = vertex - glm::vec3(this->font_size * 0.5, this->font_size * 0.5, 0);
				location.x *= -1;
				location = glm::vec4(base_location + location, 0) * rotation_y;
				location = glm::normalize(location) * radius;
				ofVertex(location);
			}
		}
		ofEndShape(true);
	}

	this->cam.end();
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}