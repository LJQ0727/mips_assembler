/**
 * @file registerTable.cpp
 * @author Li Jiaqi
 * @brief This file implements the registerTable.h interface.
 * @date 2022-02-22
 * 
 */

#include "registerTable.h"
#include <cassert>


RegisterTable::RegisterTable(){
    // initialize the register table to mips registers
    registerTable.clear();
    add("$zero");
    add("$at");
    add("$v0");
    add("$v1");
    add("$a0");
    add("$a1");
    add("$a2");
    add("$a3");
    add("$t0");
    add("$t1");
    add("$t2");
    add("$t3");
    add("$t4");
    add("$t5");
    add("$t6");
    add("$t7");
    add("$s0");
    add("$s1");
    add("$s2");
    add("$s3");
    add("$s4");
    add("$s5");
    add("$s6");
    add("$s7");
    add("$t8");
    add("$t9");
    add("$k0");
    add("$k1");
    add("$gp");
    add("$sp");
    add("$s8");         // $s8 or $fp, $fp is converted to $s8 in the "get" method
    add("$ra");
}



void RegisterTable::add(std::string registerName){
    registerTable.push_back(registerName);
}

int RegisterTable::get(std::string registerName){
    if (registerName == "$fp") registerName = "$s8";
    for (int i = 0; i < registerTable.size(); i++)
    {
        if (registerTable[i] == registerName) return i;
    }
    assert(false);      // trigger error when not getting result
    return 1;
}
