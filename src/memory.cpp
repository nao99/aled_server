//
// Created by NOsipov on 11/28/2021.
//

#include "memory.h"

void initializeMemory(unsigned int memoryCount) {
    EEPROM.begin(memoryCount);
}

uint8_t read(int memoryIndex) {
    return EEPROM.read(memoryIndex);
}

void persist(int memoryIndex, char symbol) {
    EEPROM.write(memoryIndex, symbol);
}

void persist(int memoryIndex, char symbols[]) {
    size_t symbolsLength = strlen(symbols);
    for (int i = 0; i < symbolsLength; i++) {
        persist(memoryIndex + i, symbols[i]);
    }
}

void persist(int memoryIndex, String* str) {
    for (int i = 0; i < str->length(); i++) {
        persist(memoryIndex + i, (*str)[i]);
    }
}

void commit() {
    EEPROM.commit();
}
