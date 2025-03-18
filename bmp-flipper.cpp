#include <iostream>    
#include <fstream>    
#include "BMP.h";  

using namespace std;

void mirror_v(ofstream& output, char* imageData, BMPHeader header) {
    for (int i = 0; i < header.height; i++) {
        for (int j = 0; j < header.width / 2; j++) {
            for (int k = 0; k < 3; k++) {
                output.write(&imageData[(i * header.width + j) * 3 + k], 1);
            }
        }
        for (int j = header.width / 2 - 1; j >= 0; j--) {
            for (int k = 0; k < 3; k++) {
                output.write(&imageData[(i * header.width + j) * 3 + k], 1);
            }
        }
    }
    char blank[3] = { 0, 0, 0 };
    if (header.width % 2 == 1) {
        for (int j = 0; j < header.height; j++) {
            output.write(blank, 1);
        }
    }
}

void mirror_h(ofstream& output, char* imageData, BMPHeader header) {
    for (int i = 0; i < header.height / 2; i++) {
        for (int j = 0; j < header.width; j++) {
            for (int k = 0; k < 3; k++) {
                output.write(&imageData[(i * header.width + j) * 3 + k], 1);
            }
        }
    }
    for (int i = header.height / 2; i >= 0; i--) {
        for (int j = 0; j < header.width; j++) {
            for (int k = 0; k < 3; k++) {
                output.write(&imageData[(i * header.width + j) * 3 + k], 1);
            }
        }
    }
    char blank[3] = { 0, 0, 0 };
    if (header.height % 2 == 1) output.write(blank, 3);
}
int main(int argc, char* argv[]) {

    char* out = argv[2];
    char* in = argv[1];
    char* func = argv[3];

    ifstream input(in, ios::binary);

    BMPHeader header;
    input.read((char*)&header, sizeof(header));

    char* imageData = new char[header.sizeImage];
    input.read(imageData, header.sizeImage);

    input.close();
    ofstream output(out, ios::binary);
    output.write((char*)&header, sizeof(header));

    if (strcmp(argv[3], "vertical") == 0) {
        mirror_v(output, imageData, header);
    }
    if (strcmp(argv[3], "horizontal") == 0) {
        mirror_h(output, imageData, header);
    }
    output.close();
    delete[] imageData;

    return 0;
}