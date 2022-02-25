/**
 * @file phase2.h
 * @author Li Jiaqi
 * @brief This file exports the phase 2 procedure and its auxilary functions.
 *      The procedure does the scanning to the temporary file generated in 
 *      phase 1, matches the instructions, registers, or labels,
 *      and generates the machine code output.
 * @date 2022-02-24
 * 
 */

#ifndef PHASE2_H
#define PHASE2_H


#include "labelTable.h"
#include "registerTable.h"

namespace Phase2
{
    /**
     * @brief The function does the second procedure in a mips assembler.
     *      It matches the instructions, registers and labels and generates
     *      machine code output to the output file.
     * 
     * @param outfileName The name of the file to be written in.
     * @param lt A LabelTable object storing all the labels and addresses
     */
    void pass2 (std::string outfileName, LabelTable& lt, std::string tempfileName);

    /**
     * @brief Get the 32-bit machine code
     * 
     * @param tokens A vector containing the tokenized information in an instruction line
     * @param lt A LabelTable object storing all the labels and addresses
     * @param regTable A RegisterTable object storing all the register names and numbers
     * @return std::string The 32-bit machine code matched with the instructions
     */
    std::string getMachineCode32(std::vector<std::string> tokens, LabelTable& lt, RegisterTable& regTable);

    /**
     * @brief Assemble the fields in a mips R-type instruction to machine code
     * 
     * The parameters are all fields of a R-type instruction.
     */
    std::string getRTypeCode(uint16_t opcd, uint16_t rs, uint16_t rt, uint16_t rd, int16_t sa, uint16_t funct);
    
    /**
     * @brief Assemble the fields in a mips I-type instruction to machine code
     */
    std::string getITypeCode(uint16_t opcd, uint16_t rs, uint16_t rt, int32_t immediate);
    
    /**
     * @brief (Overloaded) Assemble the fields in a mips I-type instruction to machine code
     */    
    std::string getITypeCode(uint16_t opcd, uint16_t rs, uint16_t rt, uint32_t labelAddr, uint32_t currentAddr);
    
    /**
     * @brief Assemble the fields in a mips J-type instruction to machine code
     */
    std::string getJTypeCode(uint16_t opcd, uint32_t labelAddr);
    

    /**
     * @brief Convert a string to integer.
     */
    int64_t stringToInt(std::string str);

    /**
     * @brief Convert an integer to binary number in string format.
     *      Negative numbers are represented in 2's complement form
     * 
     * @param src The number to be converted
     * @param targetDigitNumber The desired digits shown in the output
     * @return std::string The binary number
     */
    std::string toBinary(int64_t src, int targetDigitNumber);

};

#endif 