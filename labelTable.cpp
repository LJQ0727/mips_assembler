/**
 * @file labelTable.cpp
 * @author Li Jiaqi
 * @brief This file implements the labelTable.h interface.
 * @date 2022-02-24
 * 
 */

#include "labelTable.h"

LabelTable::LabelTable()
{
    // initialize
    firstItem = nullptr;
    lastItem = nullptr;
}

void LabelTable::add(std::string label, uint32_t address){
    Item* newItem = new Item;
    // set the properties of newly created item
    newItem->label = label;
    newItem->address = address;
    newItem->link = nullptr;
    if (firstItem == nullptr){
        firstItem = newItem;
        lastItem = newItem;
    }
    else{
        lastItem->link = newItem;
        lastItem = newItem;
    }
}

uint32_t LabelTable::get(std::string label){
    // traverse and match
    Item* scannedItem = firstItem;
    while (scannedItem != nullptr){
        if (scannedItem->label == label) return scannedItem->address;
        scannedItem = scannedItem->link;
    }
    // if no matching
    
    std::cout << "error: no matching label";
    return 1;
}

// frees memory
LabelTable::~LabelTable(){
    
    Item* scannedItem = firstItem;
    Item* nextItem;
    while (scannedItem != nullptr){
        nextItem = scannedItem->link;
        delete scannedItem;
        scannedItem = nextItem;
    }
}
