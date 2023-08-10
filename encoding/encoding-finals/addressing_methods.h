/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file contains the new data type 'boolean'.
 * */

#ifndef MMN_14_ADDRESSING_METHODS_H
#define MMN_14_ADDRESSING_METHODS_H

/* Represents all the addressing methods. (NO_ADD_METHOD represents data type) */
typedef enum {ZERO_ADD_MTD = 0, INSTANT = 1, DIRECT = 3, DIRECT_REGISTER = 5, NO_ADD_METHOD = -1}
    addressing_method_t;

#endif /* MMN_14_ADDRESSING_METHODS_H */