/**
 * @file phase1.h
 * @author Li Jiaqi
 * @brief This file exports the Phase 1 procedure. It scans through the .asm file given,
 *      stores the tags and their memory addresses in a label table,
 *      and returns the LabelTable object.
 * @date 2022-02-24
 * 
 */

#ifndef PHASE1_H
#define PHASE1_H

#include "labelTable.h"
#include <vector>

namespace Phase1
{
    /**
     * @brief The function does the first procedure in a mips assembler.
     *      It scans through all the labels in the file with their addresses, 
     *      and stores them in a label table. 
     *      
     * @param filename Name of the input assembly file.
     * @return LabelTable A LabelTable object that stores the labels and addresses
     *      in the assembly file.
     * @note Comments are detected and removed.
     *      A temporary file is generated containing the processed information and
     *      the addresses.
     */
    LabelTable pass1(std::string filename, std::string tempfileName);

    /**
     * @brief An auxilary function used to parse a line to a collection of information strings
     *      
     * 
     * @param lineStr The line to be parsed
     * @return std::vector<std::string> 
     * 
     * e.g. parseLineToTokens("add $t1, $s1, $zero") -> {"add", "t1", "s1", "$zero"}
     */
    std::vector<std::string> parseLineToTokens(std::string lineStr);
};

#endif 