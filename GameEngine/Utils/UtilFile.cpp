#include "UtilFile.h"

#include <fstream>

string UtilFile::readFile(string fileName) {
    string out;

    ifstream inputFile(fileName.c_str());

    if (inputFile.is_open()) {

        // Check for BOM (UTF-8 signature)
        std::string first3Bytes;
        inputFile >> first3Bytes;
        
        if (first3Bytes[0] != '\xEF' && first3Bytes[1] != '\xBB' && first3Bytes[2] != '\xBF') {
            inputFile.seekg(0);
        } else {
            inputFile.seekg(0);
            inputFile.seekg(3);
        }
        
        string line;
        while (getline(inputFile, line)) {
            out.append(line.append("\n"));
        }
        inputFile.close();
    } else {
        printf("Unable to open the file -> %s\n", fileName.c_str());
    }
    
    return out;
}
