#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255,255,255);
	ofSetVerticalSync(true);
    Tresh = 160;

    src_img.loadImage("images/Portrait.png");

    cpy_img.clone(src_img);
    rot_img.clone(cpy_img);
    cpy_img.setAnchorPercent(.5,.5);

    int w = cpy_img.width;
    int h = cpy_img.height;

    float fact = float (ofGetWidth()) / w ;
    printf("fact = %f\n", fact);
    fact = 0.7;
    cpy_img.resize(w * fact, h * fact);
    // rot_img.update();

    int d = ofDist(0,0,cpy_img.width,cpy_img.height);
    ofSetWindowShape(cpy_img.width,cpy_img.height);

	computeBinarization(&cpy_img, Tresh);
	computeBinarization(&rot_img, Tresh);
	// computeHisto(cpy_img);
}

//--------------------------------------------------------------
void ofApp::update(){
	// if(rot){
	// 	angle -= 0.1;
	// 	// chec maximum
	// }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotateZ(angle);
    ofSetHexColor(0xffffff);
	cpy_img.draw(0, 0);

	if(angle > -5.0 && rot){
		find_rotation();
		angle -=0.1;
	}
	else{
		rot = false;
		angle = best_angle;
	}
	// drawHisto(-ofGetWidth()/2, 600);
}

void ofApp::computeHisto(ofImage img){
  	ofColor col_hsb;
    // int histo[25x5] = {0};
    histDat.clear();

	unsigned char *data = img.getPixels();
    int components = 3;

    int pixs = 0;

	for (int x=0; x<img.width; x++) {
		for (int y=0; y<img.height; y++) {
	        //Read pixel (x,y) color components
	        // int index = components * (x + x<img.width * y);
	        // int red = data[ index ];
	        // int green = data[ index + 1 ];
	        // int blue = data[ index + 2 ];

	        ofColor c = img.getColor(x, y);
	        if (c.getBrightness()  == 0){
	        	pixs++;
	        	// getchar();
	        }
        }
    	// printf("%d  - ", pixs);
        histDat.push_back(pixs);
        pixs = 0;
    }
}

/**
 * @brief Binarize an image with a specific trshold
 * 
 * @param img poiter to the image to modify
 * @param tresh value of treshold for 0 to 255
 */
void ofApp::computeBinarization(ofImage *img, int tresh){

	//Getting pointer to pixel array of tdf
	unsigned char *data = img->getPixels();
	//Calculate number of pixel components
	int components = img->bpp / 8;
	//Modify pixel array
	for (int y=0; y<img->height; y++) {
	    for (int x=0; x<img->width; x++) {

	        //Read pixel (x,y) color components
	        int index = components * (x + img->width * y);
	        int gray = data[ index ];

	        int bin = 0;

	        if (gray > tresh)
	        	bin = 255;

	        //Set red 
	        data[ index + RED] = bin ;
	        //Set green 
	        data[ index + GREEN ] = bin;
	        //Set blue 
	        data[ index + BLUE] = bin;

	    }
	}
	//Calling img.update() to apply changes
	img->update();	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	int max = -1;


	switch (key){
		// case 'p':
		// 	Tresh+=10;
		// 	cpy_img.clone(src_img);
		// 	computeBinarization(&cpy_img, Tresh);
		// 	printf("plus\n");
		// 	computeHisto(cpy_img);
		// 	break;
		// case 'm':	
		// 	Tresh-=10;
		// 	cpy_img.clone(src_img);
		// 	computeBinarization(&cpy_img, Tresh);
		// 	printf("moins\n");
		// 	computeHisto(cpy_img);
		// 	break;
		case 'r':
    		angle -= 0.1;
			break;
		case ' ':
			cpy_img.grabScreen(0,0,ofGetWidth(),ofGetHeight());
			// cpy_img.save("image/ratated.png");
			ofSaveImage(cpy_img, "image/ratated.png");
			break;
		case 't':
			break;
		default:
			break;

	}

	printf("angle = %f ; max = %d\n", angle, max);

}

void ofApp::find_rotation(){
	int max = -1;
	usleep(100000);
	rot_img.grabScreen(0,0,ofGetWidth(),ofGetHeight());
	computeBinarization(&rot_img, Tresh);
	for (int i = 0; i < histDat.size(); ++i)
	{
		if (histDat[i] > max){
			// printf("%d - ", histDat[i]);
			max = histDat[i];
		}
	}
	computeHisto(rot_img);
	for (int i = 0; i < histDat.size(); ++i)
	{
		if (histDat[i] > max){
			printf("%d - ", histDat[i]);
			max = histDat[i];
		}
	}
	if (max > best_max){
		best_max = max;
		best_angle = angle;
		printf("\n%f is the new best angle\n", best_angle);
	}
	// all_max.push_back(max);
	// printf(" max = %d\n", max);
}

/**
 * @brief draw the histogram from the Histodata
 */
void ofApp::drawHisto(int start_x, int start_y){
	// draw a line for each elmt in the hestoData
	int x_pos = start_x, end_y;
    ofSetHexColor(0xff0000);

	for (std::vector<int>::iterator i = histDat.begin(); i != histDat.end(); ++i){
    	end_y = start_y - (*i);
    	// printf("%d\n", (*i));
    	ofLine(x_pos++, start_y, x_pos, end_y);
	}
}
