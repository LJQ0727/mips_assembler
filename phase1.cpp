/**
 * @file phase1.cpp
 * @author Li Jiaqi
 * @brief This file implements the phase1.h interface.
 * @date 2022-02-24
 * 
 */


#include "phase1.h"
#include <fstream>
#include <string>
#include <vector>
#include <cassert>


LabelTable Phase1::pass1(std::string filename, std::string tempfileName){

    const uint32_t STARTING_ADDRESS = 0x400000;
    
    LabelTable lt;

    std::ifstream infile;
    infile.open(filename);
    if (!infile.is_open()){
        filename = "../" + filename;            // try the parent directory if the infile is not present
        infile.open(filename);
        assert(infile.is_open());
    }


    uint32_t address = STARTING_ADDRESS;            
    std::string lineStr;
    bool isTextSegment = false;
    bool isInstructionLine = false;

    std::ofstream tempFile;
    tempFile.open(tempfileName);     // generate a temporary file
    assert(tempFile.is_open());



    while (!infile.eof()){
        std::getline(infile, lineStr);

        isInstructionLine = false;

        // remove comments in this line
        if (lineStr.find('#') != std::string::npos) lineStr = lineStr.substr(0, lineStr.find('#'));

        // find .text identifier and if so, move to next line
        if (lineStr.find(".text") != std::string::npos){
            isTextSegment = true;
            continue;
        }

        // if not in text segment, move to next
        if (!isTextSegment) continue;
        // if there's no content, move to next
        if (lineStr == "") continue;

        std::vector<std::string> tokens = parseLineToTokens(lineStr);
        if (tokens.size() == 0) continue;
        if (tokens[0].find(':') != std::string::npos){          // identify if there's label in the first token
            lt.add(tokens[0].substr(0, tokens[0].size()-1), address);   // add label to table, excluding ":"
            tokens.erase(tokens.begin());           // remove the label in the token
        }

        if (tokens.size() != 0) isInstructionLine = true;
        else continue;
        
        // assign next memory address and add information to temp file
        if (isTextSegment && isInstructionLine){
            int tokenSize = tokens.size();
            for (int i = 0; i < tokenSize; i++){
                tempFile << tokens[i] << ' ';
            }
            tempFile << address << '\n';            
            address += 4;
        }
    }

    infile.close();
    tempFile.close();
    return lt;
    
}

std::vector<std::string> Phase1::parseLineToTokens(std::string lineStr){

    int lineLength = lineStr.size();
    char scannedChar;
    bool isInNewToken = true;
    bool isSeparater;
    std::string buffer;
    std::vector<std::string> tokens;
    bool hasColon;

    for (int i = 0; i < lineLength; i++){

        scannedChar = lineStr[i];
        hasColon = false;
        if (lineStr.find(':') != std::string::npos) hasColon = true;
        if (isInNewToken) buffer = "";
        if (scannedChar == ' ' || scannedChar == '\t' || scannedChar == ',' 
        || scannedChar == '(' || scannedChar == ')' || scannedChar == '\r' || scannedChar == ':'){
            isSeparater = true;      // whitespace, tab, comma and other separators won't be in token
        }
        else isSeparater = false;
        
        if (!isSeparater){
            buffer += scannedChar;
            isInNewToken = false;         
        }
        else{
            if (buffer != "") {
                tokens.push_back(buffer);
                isInNewToken = true;
                buffer = "";
            }
        }
        if ((i == lineLength - 1) && buffer != "") tokens.push_back(buffer);    // push buffer at line end
    }

    if (hasColon) tokens[0] += ':';     // add the colon back for label detection afterwards
    return tokens;
}

