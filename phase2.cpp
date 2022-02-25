/**
 * @file phase2.cpp
 * @author Li Jiaqi
 * @brief This file implements the phase2.h interface.
 * @date 2022-02-24
 * 
 */

#include "phase2.h"
#include "Phase1.h"
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>
#include <bitset>


void Phase2::pass2 (std::string outfileName, LabelTable& lt, std::string tempfileName){
    
    // open tempfile generated in phase1
    std::ifstream tempFile;
    tempFile.open(tempfileName);
    assert(tempFile.is_open());

    // create output file
    std::ofstream outfile;
    outfile.open(outfileName);
    assert(outfile.is_open());

    std::string lineStr;
    std::vector<std::string> tokens;
    std::string outputLineStr;

    RegisterTable regTable;

    while (!tempFile.eof()){
        std::getline(tempFile, lineStr);
        tokens = Phase1::parseLineToTokens(lineStr);
        if (lineStr == "") continue;
        outputLineStr = getMachineCode32(tokens, lt, regTable);

        assert(outputLineStr.size() == 32);
        outfile << outputLineStr << '\n';
    }

    tempFile.close();
    outfile.close();

}


std::string Phase2::getMachineCode32(std::vector<std::string> tokens, LabelTable& lt, RegisterTable& regTable){
    // initialize

    uint16_t opcd;  
    uint16_t rs;   
    uint16_t rt;
    uint16_t rd; 
    uint16_t funct;
    int16_t sa;  
    int32_t immediate;
    uint32_t labelAddr;
    uint32_t currentAddr;

    opcd = rs = rt = rd = sa = funct = immediate = labelAddr = currentAddr = 0;
    if (tokens.size() == 0) return "";
    std::string instrc = tokens[0];        // instruction
    
    //scans the operation specifier
    // rules
    // R-type
    if (instrc == "add"){
        funct = 0x20;
        rd = regTable.get(tokens[1]);
        rs = regTable.get(tokens[2]);
        rt = regTable.get(tokens[3]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "addu"){
        funct = 0x21;
        rd = regTable.get(tokens[1]);
        rs = regTable.get(tokens[2]);
        rt = regTable.get(tokens[3]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "and"){
        funct = 0x24;
        rd = regTable.get(tokens[1]);
        rs = regTable.get(tokens[2]);
        rt = regTable.get(tokens[3]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "div"){
        funct = 0x1A;
        rs = regTable.get(tokens[1]);
        rt = regTable.get(tokens[2]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "divu"){
        funct = 0x1B;
        rs = regTable.get(tokens[1]);
        rt = regTable.get(tokens[2]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "jalr"){
        funct = 0x09;
        rd = regTable.get(tokens[1]);
        rs = regTable.get(tokens[2]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "jr"){
        funct = 0x08;
        rs = regTable.get(tokens[1]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "mfhi"){
        funct = 0x10;
        rd = regTable.get(tokens[1]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "mflo"){
        funct = 0x12;
        rd = regTable.get(tokens[1]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "mthi"){
        funct = 0x11;
        rs = regTable.get(tokens[1]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "mtlo"){
        funct = 0x13;
        rs = regTable.get(tokens[1]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "mult"){
        funct = 0x18;
        rs = regTable.get(tokens[1]);
        rt = regTable.get(tokens[2]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "multu"){
        funct = 0x19;
        rs = regTable.get(tokens[1]);
        rt = regTable.get(tokens[2]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "nor"){
        funct = 0x27;
        rd = regTable.get(tokens[1]);
        rs = regTable.get(tokens[2]);
        rt = regTable.get(tokens[3]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "or"){
        funct = 0x25;
        rd = regTable.get(tokens[1]);
        rs = regTable.get(tokens[2]);
        rt = regTable.get(tokens[3]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "sll"){
        funct = 0x00;
        rd = regTable.get(tokens[1]);
        rs = regTable.get(tokens[2]);
        sa = stringToInt(tokens[3]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "sllv"){
        funct = 0x04;
        rd = regTable.get(tokens[1]);
        rt = regTable.get(tokens[2]);
        rs = regTable.get(tokens[3]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "slt"){
        funct = 0x2A;
        rd = regTable.get(tokens[1]);
        rs = regTable.get(tokens[2]);
        rt = regTable.get(tokens[3]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "sltu"){
        funct = 0x2B;
        rd = regTable.get(tokens[1]);
        rs = regTable.get(tokens[2]);
        rt = regTable.get(tokens[3]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "sra"){
        funct = 0x03;
        rd = regTable.get(tokens[1]);
        rt = regTable.get(tokens[2]);
        sa = stringToInt(tokens[3]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "srav"){
        funct = 0x07;
        rd = regTable.get(tokens[1]);
        rt = regTable.get(tokens[2]);
        rs = regTable.get(tokens[3]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "srl"){
        funct = 0x02;
        rd = regTable.get(tokens[1]);
        rt = regTable.get(tokens[2]);
        sa = stringToInt(tokens[3]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "srlv"){
        funct = 0x06;
        rd = regTable.get(tokens[1]);
        rt = regTable.get(tokens[2]);
        rs = regTable.get(tokens[3]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "sub"){
        funct = 0x22;
        rd = regTable.get(tokens[1]);
        rs = regTable.get(tokens[2]);
        rt = regTable.get(tokens[3]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "subu"){
        funct = 0x23;
        rd = regTable.get(tokens[1]);
        rs = regTable.get(tokens[2]);
        rt = regTable.get(tokens[3]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "syscall"){
        funct = 0x0C;
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }
    if (instrc == "xor"){
        funct = 0x26;
        rd = regTable.get(tokens[1]);
        rs = regTable.get(tokens[2]);
        rt = regTable.get(tokens[3]);
        return getRTypeCode(opcd, rs, rt, rd, sa, funct);
    }


    // I-type
    if (instrc == "addi"){
        opcd = 0x08;
        rt = regTable.get(tokens[1]);
        rs = regTable.get(tokens[2]);
        immediate = stringToInt(tokens[3]);
        return getITypeCode(opcd, rs, rt, immediate);
    }
    if (instrc == "addiu"){
        opcd = 0x09;
        rt = regTable.get(tokens[1]);
        rs = regTable.get(tokens[2]);
        immediate = stringToInt(tokens[3]);
        return getITypeCode(opcd, rs, rt, immediate);
    }
    if (instrc == "andi"){
        opcd = 0x0C;
        rt = regTable.get(tokens[1]);
        rs = regTable.get(tokens[2]);
        immediate = stringToInt(tokens[3]);
        return getITypeCode(opcd, rs, rt, immediate);
    }
    if (instrc == "beq"){
        opcd = 0x04;
        rs = regTable.get(tokens[1]);
        rt = regTable.get(tokens[2]);
        labelAddr = lt.get(tokens[3]);
        currentAddr = stringToInt(tokens[4]);
        return getITypeCode(opcd, rs, rt, labelAddr, currentAddr);
    }
    if (instrc == "bgez"){
        opcd = 0x01;
        rs = regTable.get(tokens[1]);
        labelAddr = lt.get(tokens[2]);
        currentAddr = stringToInt(tokens[3]);
        rt = 1;
        return getITypeCode(opcd, rs, rt, labelAddr, currentAddr);
    }
    if (instrc == "bgtz"){
        opcd = 0x07;
        rs = regTable.get(tokens[1]);
        labelAddr = lt.get(tokens[2]);
        currentAddr = stringToInt(tokens[3]);
        return getITypeCode(opcd, rs, rt, labelAddr, currentAddr);
    }
    if (instrc == "blez"){
        opcd = 0x06;
        rs = regTable.get(tokens[1]);
        labelAddr = lt.get(tokens[2]);
        currentAddr = stringToInt(tokens[3]);
        return getITypeCode(opcd, rs, rt, labelAddr, currentAddr);
    }
    if (instrc == "bltz"){
        opcd = 0x01;
        rs = regTable.get(tokens[1]);
        labelAddr = lt.get(tokens[2]);
        currentAddr = stringToInt(tokens[3]);
        return getITypeCode(opcd, rs, rt, labelAddr, currentAddr);
    }
    if (instrc == "bne"){
        opcd = 0x05;
        rs = regTable.get(tokens[1]);
        rt = regTable.get(tokens[2]);
        labelAddr = lt.get(tokens[3]);
        currentAddr = stringToInt(tokens[4]);
        return getITypeCode(opcd, rs, rt, labelAddr, currentAddr);
    }
    if (instrc == "lb"){
        opcd = 0x20;
        rt = regTable.get(tokens[1]);
        immediate = stringToInt(tokens[2]);
        rs = regTable.get(tokens[3]);
        return getITypeCode(opcd, rs, rt, immediate);
    }
    if (instrc == "lbu"){
        opcd = 0x24;
        rt = regTable.get(tokens[1]);
        immediate = stringToInt(tokens[2]);
        rs = regTable.get(tokens[3]);
        return getITypeCode(opcd, rs, rt, immediate);
    }
    if (instrc == "lh"){
        opcd = 0x21;
        rt = regTable.get(tokens[1]);
        immediate = stringToInt(tokens[2]);
        rs = regTable.get(tokens[3]);
        return getITypeCode(opcd, rs, rt, immediate);
    }
    if (instrc == "lhu"){
        opcd = 0x25;
        rt = regTable.get(tokens[1]);
        immediate = stringToInt(tokens[2]);
        rs = regTable.get(tokens[3]);
        return getITypeCode(opcd, rs, rt, immediate);
    }
    if (instrc == "lui"){
        opcd = 0x0F;
        rt = regTable.get(tokens[1]);
        immediate = stringToInt(tokens[2]);
        return getITypeCode(opcd, rs, rt, immediate);
    }
    if (instrc == "lw"){
        opcd = 0x23;
        rt = regTable.get(tokens[1]);
        immediate = stringToInt(tokens[2]);
        rs = regTable.get(tokens[3]);
        return getITypeCode(opcd, rs, rt, immediate);
    }
    if (instrc == "ori"){
        opcd = 0x0D;
        rt = regTable.get(tokens[1]);
        rs = regTable.get(tokens[2]);
        immediate = stringToInt(tokens[3]);
        return getITypeCode(opcd, rs, rt, immediate);
    }
    if (instrc == "sb"){
        opcd = 0x28;
        rt = regTable.get(tokens[1]);
        immediate = stringToInt(tokens[2]);
        rs = regTable.get(tokens[3]);
        return getITypeCode(opcd, rs, rt, immediate);
    }
    if (instrc == "slti"){
        opcd = 0x0A;
        rt = regTable.get(tokens[1]);
        rs = regTable.get(tokens[2]);
        immediate = stringToInt(tokens[3]);
        return getITypeCode(opcd, rs, rt, immediate);
    }
    if (instrc == "sltiu"){
        opcd = 0x0B;
        rt = regTable.get(tokens[1]);
        rs = regTable.get(tokens[2]);
        immediate = stringToInt(tokens[3]);
        return getITypeCode(opcd, rs, rt, immediate);
    }
    if (instrc == "sh"){
        opcd = 0x29;
        rt = regTable.get(tokens[1]);
        immediate = stringToInt(tokens[2]);
        rs = regTable.get(tokens[3]);
        return getITypeCode(opcd, rs, rt, immediate);
    }
    if (instrc == "sw"){
        opcd = 0x2B;
        rt = regTable.get(tokens[1]);
        immediate = stringToInt(tokens[2]);
        rs = regTable.get(tokens[3]);
        return getITypeCode(opcd, rs, rt, immediate);
    }
    if (instrc == "xori"){
        opcd = 0x0E;
        rt = regTable.get(tokens[1]);
        rs = regTable.get(tokens[2]);
        immediate = stringToInt(tokens[3]);
        return getITypeCode(opcd, rs, rt, immediate);
    }
    if (instrc == "lwl"){
        opcd = 0x22;
        rt = regTable.get(tokens[1]);
        immediate = stringToInt(tokens[2]);
        rs = regTable.get(tokens[3]);
        return getITypeCode(opcd, rs, rt, immediate);
    }
    if (instrc == "lwr"){
        opcd = 0x26;
        rt = regTable.get(tokens[1]);
        immediate = stringToInt(tokens[2]);
        rs = regTable.get(tokens[3]);
        return getITypeCode(opcd, rs, rt, immediate);
    }
    if (instrc == "swl"){
        opcd = 0x2A;
        rt = regTable.get(tokens[1]);
        immediate = stringToInt(tokens[2]);
        rs = regTable.get(tokens[3]);
        return getITypeCode(opcd, rs, rt, immediate);
    }
    if (instrc == "swr"){
        opcd = 0x2E;
        rt = regTable.get(tokens[1]);
        immediate = stringToInt(tokens[2]);
        rs = regTable.get(tokens[3]);
        return getITypeCode(opcd, rs, rt, immediate);
    }


    // J-type
    if (instrc == "j"){
        opcd = 0x02;
        labelAddr = lt.get(tokens[1]);
        return getJTypeCode(opcd, labelAddr);
    }
    if (instrc == "jal"){
        opcd = 0x03;
        labelAddr = lt.get(tokens[1]);
        return getJTypeCode(opcd, labelAddr);
    }

    assert(false);   // if no match for instruction
    return "";

}



std::string Phase2::getRTypeCode(uint16_t opcd, uint16_t rs, uint16_t rt, uint16_t rd, int16_t sa, uint16_t funct){
    std::string returnStr = toBinary(opcd, 6) + toBinary(rs, 5)
        + toBinary(rt, 5) + toBinary(rd, 5) + toBinary(sa, 5)
        + toBinary(funct, 6);
    return returnStr;
}



std::string Phase2::getITypeCode(uint16_t opcd, uint16_t rs, uint16_t rt, int32_t immediate){
    std::string returnStr = toBinary(opcd, 6) + toBinary(rs, 5)
        + toBinary(rt, 5) + toBinary(immediate, 16);
    return returnStr;
}

std::string Phase2::getITypeCode(uint16_t opcd, uint16_t rs, uint16_t rt, uint32_t labelAddr, uint32_t currentAddr){
    int32_t diff = labelAddr - currentAddr - 4;
    diff = diff >> 2;     // drop 2 lower bits
    std::string returnStr = toBinary(opcd, 6) + toBinary(rs, 5) 
        + toBinary(rt, 5) + toBinary(diff, 16);
    return returnStr;
}

std::string Phase2::getJTypeCode(uint16_t opcd, uint32_t labelAddr){
    labelAddr = labelAddr >> 2;     // drop 2 lower bits
    std::string addr30 = toBinary(labelAddr, 30);
    std::string addr26 = addr30.substr(4);
    std::string returnStr = toBinary(opcd, 6) + addr26;
    return returnStr;
}

int64_t Phase2::stringToInt(std::string str){
    std::istringstream iss(str);
    int64_t returnVal;
    iss >> returnVal;
    return returnVal;
}

std::string Phase2::toBinary(int64_t src, int targetDigitNumber){
    std::string binaryAddress = std::bitset<32>(src).to_string();   // convert to 32-bit binary form
    int initialIndex = 32 - targetDigitNumber;
    return binaryAddress.substr(initialIndex);
}

