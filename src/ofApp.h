#pragma once

#include "ofMain.h"
#include <unistd.h>

#define RED 0
#define GREEN 1
#define BLUE 2


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		// void keyReleased(int key);
		// void mouseMoved(int x, int y );
		// void mouseDragged(int x, int y, int button);
		// void mousePressed(int x, int y, int button);
		// void mouseReleased(int x, int y, int button);
		// void windowResized(int w, int h);
		// void dragEvent(ofDragInfo dragInfo);
		// void gotMessage(ofMessage msg);

		void computeHisto(ofImage img);
		void computeBinarization(ofImage *img, int tresh);
		void drawHisto(int start_x, int start_y);
		void find_rotation();
		void draw_vert_grid
draw_vert_grid(int start_x, int start_y);


		ofImage src_img, cpy_img, rot_img;
		int Tresh;
		float angle=0;

		bool rot = true;
		bool last_grab = false;

        std::vector<int> histDat;
        int best_max = -1;
        float best_angle = 0;


		
};
