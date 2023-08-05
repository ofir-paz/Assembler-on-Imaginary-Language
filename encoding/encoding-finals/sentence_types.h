/*
 * @author Ofir Paz
 * @version (28/07/2023)
 *
 * Header file for the sentence_type.c file.
 */

#ifndef MMN_14_SENTENCE_TYPES_H
#define MMN_14_SENTENCE_TYPES_H

typedef enum {NO_SENTENCE_TYPE, GUIDANCE_SENTENCE, DIRECTION_SENTENCE} sentence_type_t;

typedef struct
{
    union
    {
        opcodes_t opcode;
        guidance_t guidance;
    } sentence;
    sentence_type_t sentenceType;
} sentence_t;

#endif /* MMN_14_SENTENCE_TYPES_H */
