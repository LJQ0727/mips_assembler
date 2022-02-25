/**
 * @file labelTable.h
 * @author Li Jiaqi
 * @brief This file exports the LabelTable class, which is a data 
 *      structure maintaining labels and their addresses.
 * @date 2022-02-24
 * 
 */

#ifndef LABELTABLE_H
#define LABELTABLE_H

#include <string>
#include <iostream>

class LabelTable
{
public:

    /**
     * @brief Construct a new Label Table object
     */
    LabelTable();

    /**
     * @brief Destroy the Label Table object
     */
    ~LabelTable();

    /**
     * @brief Add new item to the label table
     */
    void add(std::string label, uint32_t address);
    
    /**
     * @brief Get the address of a label. 
     * 
     * @return The address represented in 32-bit unsigned int
     */
    uint32_t get(std::string label); 
    


private:
    struct Item{
        std::string label;
        uint32_t address;      // address represented in a 32-bit unsigned int
        Item* link;     // link to the next item
    };
    Item* firstItem;        // pointer to the first item in the table
    Item* lastItem;
    
};

#endif
