#include <iostream>
#include <fstream>
#include <string>
#include "Image.h"

using namespace imaging;
using namespace std;

Color * Image::getRawDataPtr() {

	return buffer;

}

Color Image::getPixel(unsigned int x, unsigned int y) const {

	if (x < 0 || y < 0 || buffer == nullptr || x >= width || y >= height) {
		Color * color = new Color();
		return  *color;
	}
	return buffer[y*width + x];
}

void Image::setPixel(unsigned int x, unsigned int y, Color & value) {

	if ((x >= 0 && x < width) && (y >= 0 && y < height) && (buffer != nullptr)) {
		buffer[y*width + x] = value;
	}

}

void Image::setData(const Color * & data_ptr) {

	if (buffer != nullptr && width != 0 && height != 0) {
		for (int i = 0; i < width * height; i++) {
			buffer[i] = data_ptr[i];
		}
	}

}

Image::Image() {

	buffer = nullptr;
	width = 0;
	height = 0;

}

Image::Image(unsigned int width, unsigned int height) {

	buffer = (Color *)malloc(3 * width * height * sizeof(float));
	this->width = width;
	this->height = height;

}

Image::Image(unsigned int width, unsigned int height, const Color * data_ptr) {

	buffer = (Color *)malloc(3 * width * height * sizeof(float));
	this->width = width;
	this->height = height;
	setData(data_ptr);

}

Image::Image(const Image &src) {

	buffer = (Color *)malloc(3 * src.width * src.height * sizeof(float));
	this->width = src.width;
	this->height = src.height;
	for (int i = 0; i < width*height; i++) {
		buffer[i] = src.buffer[i];
	}

}

Image::~Image() {

	free(buffer);
	width = 0;
	height = 0;
}

Image & Image::operator = (const Image & right) {

	Image *image = new Image(right);
	return *image;
}

bool Image::load(const std::string & filename, const std::string & format) {

	if (!filename.find(format)) {
		cout << "Error in file format!" << endl;
		return false;
	}
	else {

		ifstream file(filename, ios::in);

		if (!file.is_open())
		{
			cerr << "Error opening file" << endl;
			return false;
		}

		if (width != 0 && height != 0 && buffer != nullptr) {
			width = 0;
			height = 0;
			buffer = nullptr;
		}

		string header;
		int w;
		int h;
		int p;

		file >> header;
		file >> w;
		file >> h;
		file >> p;

		int check = file.tellg();

		if (header.compare("P6") != 0) {
			cout << "File not of P6 Type!" << endl;

			file.close();
			return false;
		}
		if (check == -1) {
			cout << "Invalid data, width or/and length is/are missing!" << endl;

			file.close();
			return false;
		}
		if (p > 255) {
			cout << "Pixel size is over 255!" << endl;

			file.close();
			return false;
		}

		width = w;
		height = h;
		//buffer = (Color *) malloc(3 * width * height * sizeof(float));

		file.close();
		return true;
	}
}

bool Image::save(const std::string & filename, const std::string & format) {

	if (width == 0 || height == 0 /*|| buffer == nullptr*/) {
		cout << "Image not initiallized" << endl;
		return false;
	}
	else if (!filename.find(format)) {
		cout << "Error in file format!" << endl;
		return false;
	}
	else {
		ofstream file(filename, ios::out | ios::binary);

		if (!file.is_open())
		{
			cerr << "Error opening file" << endl;
			return false;
		}

		file << "P6" << endl;
		file << width << " " << height << endl;
		file << "255" << endl;

		file.close();
		return true;

	}

}