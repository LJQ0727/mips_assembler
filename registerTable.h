/**
 * @file registerTable.h
 * @author Li Jiaqi
 * @brief This file exports the RegisterTable class - a look-up table
 *      for mips registers. It is initialized to contain the names of   
 *      all mips registers, like "$t1" and their register number represented
 *      by their index.
 * @date 2022-02-22
 * 
 */

#ifndef REGISTERTABLE_H
#define REGISTERTABLE_H

#include <vector>
#include <string>

class RegisterTable{
public:

    /**
     * @brief Construct a new RegisterTable object with all mips 
     *      register names added by their index
     */
    RegisterTable();

    /**
     * @brief The data structure for the register table
     *      implemented with STL vector class
     */
    std::vector<std::string> registerTable;

    /**
     * @brief Adds a new register name to the look-up table;
     *      its register number implicitly interpreted as its
     *      index in the order they are added.
     * 
     * @param registerName The name of the register. e.g. "$t1"
     */
    void add(std::string registerName);

    /**
     * @brief Retrieves the register number by its name
     * 
     * @param registerName The name of the register. e.g. "$t1"
     * @return int The register number
     */
    int get(std::string registerName);      // gets register number directly
};





#endif