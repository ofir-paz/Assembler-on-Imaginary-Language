/*
 * @author Ofir Paz
 * @version (09/08/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <stdlib.h>
#include "../new-data-types/boolean.h"
#include "../NameTable/NameTable.h"
#include "encoding-finals/encoding_finals.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */

/* Ranges, as defined and explained in this file's description. */
enum {OPCODE_LOW = 5, OPCODE_HIGH = 8, ARG_LOW = 2, ARG_HIGH = 11,
    DEST_MTD_LOW = 2, DEST_MTD_HIGH = 4, SRC_MTD_LOW, SRC_MTD_HIGH,
    DEST_REG_LOW = 2, DEST_REG_HIGH = 6, SRC_REG_LOW = 7, SRC_REG_HIGH = 11,
    DIR_DATA_LOW = 2, DIR_DATA_HIGH = 11,
    ARE_LOW = 0, ARE_HIGH = 1,
    DATA_LOW = 0, DATA_HIGH = 11};

#define ZERO_BYTE 0
#define BYTES_FOR_WORD 2
#define FULL_1_BYTE 0xff
#define BITS_IN_BYTE 8
#define START_WORD_RANGE 0
#define END_WORD_RANGE 11
/* ------------ */

typedef unsigned char word_t[BYTES_FOR_WORD];

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

void encodeInstantArg(word_t word, int instantVal)
{
    encodeToWordARE(word, ABSOLUTE);
    setBitsInRangeToVal(word, DIR_DATA_LOW,DIR_DATA_HIGH, instantVal);
}

void encodeDirectArg(word_t word, const char *directLabel, NameTable *normalLabels,
                     NameTable *extLabels, char **extFileContents, int address)
{
    /* Get the label value from the extern table (if it's there). */
    name_data_t *labelVal = getDataByName(normalLabels, directLabel);

    if (labelVal != NULL) /* Label in argument is defined in this file. */
    {
        encodeToWordARE(word, RELOCATABLE); /* Relocatable encoding. */
        setBitsInRangeToVal(word, DIR_DATA_LOW, DIR_DATA_HIGH, labelVal -> num);
    }
    else /* Label in argument is an extern label. */
    {
        encodeToWordARE(word, EXTERNAL); /* External encoding */
        /* The address will be found in the linking stage. */
        setBitsInRangeToVal(word, DIR_DATA_LOW, DIR_DATA_HIGH, ZERO_BYTE);
        addToExtFileContent(extFileContents, address);
    }
}

void encodeDirectRegisterArg(word_t word, register_t aRegister, boolean isDest)
{
    encodeToWordARE(word, ABSOLUTE);

    if (isDest == TRUE)
        setBitsInRangeToVal(word, DEST_REG_LOW, DEST_REG_HIGH, (int) aRegister);
    else /* isSource == TRUE */
        setBitsInRangeToVal(word, SRC_REG_LOW, SRC_REG_HIGH, (int) aRegister);
}

void encodeToWordARE(word_t word, encoding_type_t encodingType)
{
    setBitsInRangeToVal(word, ARE_LOW, ARE_HIGH, encodingType);
}