#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ffmpeg.setTranscode(false);
	ffmpeg.start();
	ofAddListener(ffmpeg.onFileProcessed, this, &ofApp::onFileProcessed);

	videoSlice();	
	
}

void ofApp::videoSlice(){
	// load target video
	ofFilePath path;
	ofFile file;
	ofDirectory dir;
	vector<string> videoFiles;
	vector<float> videoLength;
	vector<int> videoFrames;
	vector<string> fileName;
	vector<float> fps;
	string targetVideoPath = "original/";
	dir.listDir(targetVideoPath);
	dir.allowExt("mp4");	// allow only mp4 file. 
	dis.allowExt("mov");	// allow only mov file.
	dir.sort();

	// check video Information
	cout << "== start video Check..... ============================================= " << endl;
	for(unsigned int i=0; i<(int)dir.size(); i++){
		tmpCheckPlayer.load(dir.getPath(i));
		cout << "== VIDEO ID [" << i << "] INFO ====================================" << endl;
		cout << "== FILE    : " << dir.getPath(i) << endl;
		cout << "== FPS     : " << tmpCheckPlayer.getTotalNumFrames() / tmpCheckPlayer.getDuration() << endl;
		cout << "== LENGTH  : " << tmpCheckPlayer.getDuration() <<  "Seconds " << endl;
		cout << "== FRAMES  : " << tmpCheckPlayer.getTotalNumFrames() << "Frames" << endl;
		videoFiles.push_back(dir.getPath(i));

		fileName.push_back(dir[i].getFileName().substr(0, dir[i].getFileName().size()-4));
		fps.push_back(tmpCheckPlayer.getTotalNumFrames() / tmpCheckPlayer.getDuration());
		videoLength.push_back(tmpCheckPlayer.getDuration());
		videoFrames.push_back(tmpCheckPlayer.getTotalNumFrames());
		cout << "==================================================================== " << endl;
	}

	for(unsigned int i=0; i<(int)dir.size(); i++){
		for(unsigned int j=0; j<videoFiles.size(); j++){
			ofDirectory dir;
			dir.createDirectory(fileName[j]);
//			ffmpeg.setTargetFolder("../" + fileName[j]);
			unsigned int totalFrame = 0;
			double startPoint = 0.f;
			bool isDone = false;
			int tryCount = 0;
			int tFrame;

			while(!isDone ){
				tryCount ++;
				tFrame=int(ofRandom(24, 108));

				lastDoneTimer = ofGetElapsedTimeMillis();

				// cout << video
				if((totalFrame < videoFrames[j] - 108)){
					// ffmpeg.start();
					ffmpeg.addTask(path.getAbsolutePath(videoFiles[j], true), "../" + fileName[j] + "/" , startPoint, tFrame);
					cout << tryCount << " == " << videoFiles[j] << " : " << "\t" << startPoint << "\t" << tFrame << " - " << totalFrame << " / " <<videoFrames[j] << endl;
					
				} else {
					// ffmpeg.addTask(videoFiles[j], startPoint, videoFrames[j] - totalFrame);
					// cout << tryCount << " == " << videoFiles[j] << " : " << "\t" << startPoint << "\t" << videoFrames[j] - totalFrame << " - " << totalFrame << " / " << videoFrames[j] << endl;
					isDone = true;
					cout << "done " << endl;
				}

//				if(tryCount > 10)	isDone = true;		// test for only 10 number of files
				
				// while (ofGetElapsedTimeMillis() - lastDoneTimer < 1000) {}

				totalFrame = totalFrame + (unsigned int)tFrame;
				startPoint = startPoint + (tFrame * 1/fps[j]);
			}
		}
	}

	//  push to pending queue

	while(ffmpeg.processingQueueSize() > 0 ){
		if(lastProcessedVideoNums != ffmpeg.processingQueueSize()){
			cout << "VIDEO PROCESSING.... " << ffmpeg.processingQueueSize() << "videos are left." << endl;
			lastProcessedVideoNums = ffmpeg.processingQueueSize();
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

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

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::onFileProcessed(ofxVideoSlicer::endEvent & ev) {
	cout << ev.file << " processed with the message " << ev.message;
}
