#include <iostream>
#include <string>
#include "Image.h"
#include "../ppm/ppm.h"

using namespace std;
using namespace imaging;

int main(int argc,char* argv[]) {

	string filename;
	Image *image = new Image();
	float * temp;
	/*Color * pixel = new Color();
	Color * negative = new Color(1,1,1);
	int x = 0;
	int y = 0; */

	if (argc == 1) {
		cout << "File name of the image to load:" << endl;
		cin >> filename;
	}
	else {
		filename = argv[1];
	}

	if ((*image).load(filename, ".ppm")) {

		int size = 3 * (*image).getHeight()*(*image).getWidth();
		int a = (*image).getWidth();
		int *b = &a;
		int c = (*image).getHeight();
		int *d = &c;
		temp = ReadPPM(filename.c_str(), b, d);

		/*for (int i = 0; i <size; i++) {
			(*pixel).r = temp[i];
			(*pixel).g = temp[++i];
			(*pixel).b = temp[++i];
			(*image).setPixel(x,y,(*negative) - (*image).getPixel(x,y));
			if (x == (*image).getWidth() - 1) {
				y = y + 1;
				x = 0;
			}
			else {
				x = x + 1;
			}
		}
		
		x=0;
		y=0;

		for(int i=0; i<size; i++){
			temp[i] = (*image).getPixel(x,y).r;
			temp[++i] = (*image).getPixel(x,y).g;
			temp[++i] = (*image).getPixel(x,y).b;
			if (x == (*image).getWidth() - 1) {
				y = y + 1;
				x = 0;
			}
			else {
				x = x + 1;
			}
		}*/
		

		for (int i = 0; i < size; i++) {
			temp[i] = (1.0f - temp[i])*255;
		}

		string newfilename(filename.begin(), filename.end() - 4);
		newfilename = newfilename + "_neg.ppm";
	
		if ((*image).save(newfilename, ".ppm")) {
			if (WritePPM(temp, a, c, newfilename.c_str())) {
				cout << "Image dimensions are: " << a << " X " << c << endl;
				cout << "Dhmiourghsa eikona: " << newfilename << endl;
			}
		}
	}

	system("PAUSE");
	return 0;
}