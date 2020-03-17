#include <fstream>
#include <iostream>
#include <string>
#include "ppm.h"

using namespace imaging;
using namespace std;

float * imaging::ReadPPM(const char * filename, int * w, int * h) {

	ifstream file(filename, ios::in | ios::binary);

	if (!file.is_open())
	{
		cerr << "Error opening file" << endl;
		return nullptr;
	}

	string type;
	
	for (int i = 0; i < 4; i++) {
		file >> type;
	}

	int size = 3 * (*w) * (*h);

	float* image = (float*)malloc(sizeof(float)*size);
	char temp;

	file.get();
	for (int i = 0; i < size; i++) {
		file.get(temp);
		image[i] = ( unsigned char )temp / (float)255 ;
	}

	file.close();
	return image;

}

bool imaging::WritePPM(const float * data, int w, int h, const char * filename) {

	ofstream file(filename, ios::out | ios::binary | ios::app);
	
	if (!file.is_open())
	{
		cerr << "Error opening file" << endl;
		return false;
	}

	int size = 3 * w * h;
	unsigned char *temp = new unsigned char[size];
	for (int i = 0; i < size; i < i++) {
		temp[i] = data[i];
	}

	file.write((char*)&temp[0], sizeof(char)*size);

	file.flush();
	file.clear();
	file.close();

	return true;

}
