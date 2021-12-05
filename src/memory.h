//
// Created by NOsipov on 11/28/2021.
//

#ifndef ALED_MEMORY_H
#define ALED_MEMORY_H

#include "Arduino.h"
#include "EEPROM.h"

/**
 * Initializes memory
 * In fact, gives an access to specified number of memory's cells
 *
 * @param memoryCount a number of memory's cells
 */
extern void initializeMemory(unsigned int memoryCount);

/**
 * Reads a data from memory by memory's index
 *
 * @param memoryIndex a memory's index
 * @return a read data
 */
extern uint8_t read(int memoryIndex);

/**
 * Persists a char symbol in memory by specified memory's index
 * E.g.
 *
 * Memory structure (numbers 0-9 - indexes, not data):
 * --------------
 * |0|1|2|3|4|...
 * --------------
 *
 * Char to persist:
 * <code>
 *  int memoryIndex = 2;
 *  char symbol = 'w';
 * </code>
 *
 * Result in memory:
 * --------------
 * |0|1|w|3|4|...
 * --------------
 *
 * @param memoryIndex a memory's index
 * @param symbol      a symbol to persist
 */
extern void persist(int memoryIndex, char symbol);

/**
 * Persists a char array in memory by specified memory's index
 * E.g.
 *
 * Memory structure (numbers 0-9 - indexes, not data):
 * --------------
 * |0|1|2|3|4|...
 * --------------
 *
 * Char array to persist:
 * <code>
 *  int memoryIndex = 2;
 *  char symbol[2] = {'w', 'o'};
 * </code>
 *
 * Result in memory:
 * --------------
 * |0|1|w|o|4|...
 * --------------
 *
 * @param memoryIndex a memory's index
 * @param symbols     symbols to persist
 */
extern void persist(int memoryIndex, char symbols[]);

/**
 * Persists a string in memory by specified memory's index
 * E.g.
 *
 * Memory structure (numbers 0-9 - indexes, not data):
 * --------------
 * |0|1|2|3|4|...
 * --------------
 *
 * String to persist:
 * <code>
 *  int memoryIndex = 0;
 *  String str = "world";
 * </code>
 *
 * Result in memory:
 * --------------
 * |w|o|r|l|d|...
 * --------------
 *
 * @param memoryIndex a memory's index
 * @param str         a string to persist
 */
extern void persist(int memoryIndex, String* str);

/**
 * Commits every data which was persisted
 * In fact, writes this data into memory
 */
extern void commit();

#endif //ALED_MEMORY_H
