/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file contains functions to check errors
 * that can occur in the program.
 * */

/* ---Include header files--- */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../general-enums/neededKeys.h"
#include "../new-data-types//boolean.h"
#include "../help_methods.h"
#include "../transitions//diagnose_input.h"
/* -------------------------- */

/* ---Finals--- */
#define ZERO_NUMBER 0
#define ZERO_INDEX 0
#define LEGAL_DOTS_IN_FLOAT 1
#define EMPTY_LINE "\n\0"
/* ------------ */

/* Returns TRUE if param const char *line is an empty line {enter,null}, otherwise FALSE. */
boolean isEmptyLine(const char *line)
{
    return sameStrings(line, EMPTY_LINE);
}

/* Checks if the function is a defined handle complex function.
 * Returns TRUE if it is, otherwise FALSE */
boolean isDefinedFunction(const char *command)
{
    return (getFunction(command) != NULL)? TRUE : FALSE;
}

/* Checks if the param int i is an index of param const char *str.
 * Returns TRUE if i is an index of the given string, otherwise FALSE. */
boolean isIndexInStr(const char *str, int i)
{
    /* Note that strlen(str) is also an index, and the value is '\0'. */
    return (0 <= i && i <= strlen(str))? TRUE : FALSE;
}

/* Checks for illegal comma after the function in param const char *command.
 * Returns TRUE if there is a comma after the command, otherwise FALSE. */
boolean isCommaAfterCmd(const char *command)
{
    /* Getting the index of the comma in command, will be the index
     * of null terminator of there is no comma. */
    int nextComma = nextCommaIndex(command, ZERO_INDEX);

    /* Returning TRUE if the char in index nextComma of command is a comma,
     * otherwise FALSE. */
    return isCurrCharComma(command, nextComma);
}

/* Checks if the next char in param const char *line from param int index
 * that is not empty (space/tab) is a comma.
 * Returns TRUE if the next char is a comma, otherwise FALSE. */
boolean isNextCharComma(const char *line, int index)
{
    int nextChIndex = nextCharIndex(line, index);
    return (line[nextChIndex] == COMMA)? TRUE : FALSE;
}

/* Checks if the param const char *command is a valid function.
 * If it is, returns NO_ERROR, otherwise returns the specific error caught. */
Error checkCommandError(const char *command)
{
    Error error; /* Value to return, we don't know the error yet. */
    char *lowerCase = strToLowerCase(command);

    if (isDefinedFunction(command) == TRUE) /* Checks if there is an error */
        error = NO_ERROR;

    /* Try to catch a specific error in case there is */
    else if (isCommaAfterCmd(command) == TRUE) /* See if the error is illegal comma after the command */
        error = COMMA_AFTER_CMD;
    /* See if the user didn't input the command in lower case letter */
    else if (isDefinedFunction(lowerCase) == TRUE)
        error = WRONG_CASE_FUNC;
    else /* No specific function error, we call it undefined function. */
        error = UNDEFINED_FUNC;

    free(lowerCase);
    return  error; /* Return the found error */
}

/* Checks if the area in param const char *line between the end index of
 * the parameter in line numbered paramNum with type pType and the index
 * of the next param is valid (comma-wise)
 * Returns NO_ERROR if it's valid, otherwise the specific error that occurs. */
Error checkCommaError(const char *line, ParamNum paramNum, paramtype pType)
{
    Error error = NO_ERROR; /* Value to return, we assume there is no error. */

    /* Index to check commas from */
    int index = findParamIndex(line, paramNum) + findParamLen(line, paramNum, pType);

    /* Checks if the char between the two params is a comma */
    if (isCurrCharComma(line, index) == TRUE || isNextCharComma(line, index) == TRUE)
    {
        int commaIndex; /* We know there is a comma index */

        /* Assign commaIndex to the nearest comma */
        if (isCurrCharComma(line, index) == TRUE)
            commaIndex = index;
        else
            commaIndex = nextCharIndex(line, index);

        if (isNextCharComma(line, commaIndex) == TRUE) /* check for multiple consecutive commas */
            error = CONSEC_COMMAS;
        else /* The area between this param and the next one is valid */
            error = NO_ERROR;
    }
    else /* Missing a comma */
        error = NO_COMMA;

    return error;
}

/* Checks if the parameter that's supposed to be in index int index in
 * param const char *line exist.
 * Returns TRUE if it does, otherwise FALSE. */
boolean isParamExist(const char *line, int index)
{
    boolean isParamExist = FALSE; /* Value to return */

    if (isIndexInStr(line, index)) /* If the index is an index of line */
        /* If it's not the end of line */
        if (*(line + index) != ENTER_KEY && *(line + index) != NULL_TERMINATOR)
            isParamExist = TRUE; /* Assign value to return to TRUE */
    return isParamExist;
}

/* Returns TRUE if the number in const char *line between
 * param int start and param int end is just a sign, otherwise FALSE. */
boolean isOnlySign(const char *line, int start, int end)
{
    boolean isOnlySign = FALSE; /* Value to return, we assume the number is not only a sign */

    /* Checks if the error is that the user entered only the sign of the float */
    if (isPlusOrMinus(*(line + start)) && nextInt(start) == end)
        isOnlySign = TRUE; /* Assign value to return to TRUE if so */

    return isOnlySign;
}

/* Checks if the string in const char *str from index int start to
 * index int end represents only numbers and dots.
 * if end >= len(str), will address to len(str) as the end index of the float.
 * Returns TRUE if the string represents number and dots, otherwise FALSE. */
boolean isFloat(const char *str, int start, int end)
{
    boolean isFloat = TRUE; /* Value to return, We assume the strings represents a float. */
    int currIndex = start; /* Loop variable */
    while (isIndexInStr(str, currIndex) && currIndex < end) {
        /* Checks if the char in the curr index is neither a dot nor a number */
        if (isCurrCharDot(str, currIndex) == FALSE &&
                isCurrCharNumber(str, currIndex) == FALSE)
            isFloat = FALSE; /* If so, assign the value to return to FALSE. */
        currIndex++; /* Go to next index */
    }

    return isFloat;
}

/* Checks if float param number paramNum in const char *line is valid.
 * Returns NO_ERROR if it is, otherwise the specific error caught. */
Error checkParamFloatError(const char *line, ParamNum paramNum)
{
    Error error = NO_ERROR; /* Assuming there is no error. */
    int start = findParamIndex(line, paramNum); /* Start index of parameter in line. */

    int end = nextEmptyCommaIndex(line, start); /* End will be the next comma or empty space. */

    if (isParamExist(line, start)) /* Checking if the param exist */
    {
        /* Adding 1 to start if the user decided to pick a sign for the float */
        if (isPlusOrMinus(*(line + start)))
            start++;

        /* Checks if the error is that the user entered only the sign of the float */
        if (isOnlySign(line, start - 1, end) == TRUE)
            error = ONLY_SIGN;

        /* Check if the param is a comma */
        else if (isCurrCharComma(line, start) == TRUE)
            error = COMMA_AFTER_CMD;

        /* Checks if the error is that the user didn't input a number */
        else if (isFloat(line, start, end) == FALSE)
            error = NOT_A_FLOAT;

        /* Checks if the error is invalid amount of dots in the number */
        else if (countDots(line, start, end) > LEGAL_DOTS_IN_FLOAT)
            error = TOO_MANY_DOTS;

    }
    else /* The parameter doesn't exist */
        error = NO_FLOAT_PARAM;

    return error;
}

/* Returns TRUE if the char in const char *line after int index is empty
 * (space; tab; enter; null), otherwise FALSE. */
boolean isNextEmpty(const char *line, int index)
{
    boolean isNextEmpty = FALSE; /* Value to return, we assume the char after is not empty. */
    int nextI = nextInt(index); /* Index + 1, will be used to check the char after the one in index */

    /* Checks if the next char even exist */
    if (isIndexInStr(line, nextI) == TRUE){
        char nextCh = *(line + nextI); /* The char after the one in index */
        switch (nextCh) /* Checks if the next char is empty */
        {
            case COMMA: /* We count a comma as an empty here because it can come after the param */
            case SPACE_KEY:
            case TAB_KEY:
            case ENTER_KEY:
            case NULL_TERMINATOR:
                isNextEmpty = TRUE; /* Set value to return to TRUE if so */
                break;
            default:
                isNextEmpty = FALSE; /* Otherwise FALSE */
        } /* End of switch */
    } /* End of if */
    return isNextEmpty;
}

/* Returns TRUE if param char ch is a letter, otherwise FALSE */
boolean isLetter(char ch)
{
    boolean isLetter = FALSE; /* Value to return */

    /* Checks if ch is a letter */
    if ((ch >= CHAR_A && ch <= CHAR_Z) || (ch >= CHAR_a && ch <= CHAR_z))
        isLetter = TRUE; /* Assigns the value to return to TRUE if so */

    return isLetter;
}

/* Returns TRUE if param char letter is a capital letter, otherwise FALSE. */
boolean isCapitalLetter(char letter)
{
    return (toupper(letter) == letter)? TRUE : FALSE;
}

/* Returns true if param char complex represents a defined complex, otherwise FALSE. */
boolean isDefinedComplex(char complex)
{
    return (complex >= CHAR_A && complex <= CHAR_F)? TRUE : FALSE;
}

/* Checks for errors in the char param numbered paramNum of const char *line.
 * Returns NO_ERROR if there is no error, otherwise the specific error caught. */
Error checkParamCharError(const char *line, ParamNum paramNum)
{
    Error error = NO_ERROR; /* Assuming there is no error. */

    int index = findParamIndex(line, paramNum); /* Index of parameter in line. */

    /* Checking if the param exist */
    if (isParamExist(line, index))
    {
        char param = *(line + index);

        if (isCurrCharComma(line, index) == TRUE) /* Check if the param is a comma */
            error = COMMA_AFTER_CMD;
        else if (isNextEmpty(line, index) == FALSE) /* Checks if the param is not one char */
            error = NOT_ONE_CHAR;
        else if (isLetter(param) == FALSE) /* Checks if the param is not a letter */
            error = NOT_LETTER;
        else if (isCapitalLetter(param) == FALSE) /* Checks if the param is not a capital letter */
            error = NOT_CAPITAL;
        else if (isDefinedComplex(param) == FALSE) /* Checks if the param is a defined complex */
            error = UNDEFINED_C_VAR;
        else
            error = NO_ERROR;
    }
    else
        error = NO_CHAR_PARAM;

    return error;
}

/* Checks for illegal extraneous text after the last parameter param lastParam in param const char *line.
 * Returns NO_ERROR if there is no extraneous text, otherwise the specific error caught. */
Error checkExtraneousTextError(const char *line, ParamNum lastParam, paramtype pType)
{
    Error error = NO_ERROR; /* Value to return, we assume there is no error. */

    /* Last index of the last param */
    int lastIndexOfLastParam = findParamIndex(line, lastParam) +
            findParamLen(line, lastParam, pType) - 1;

    int lastChIndex = nextCharIndex(line, lastIndexOfLastParam);
    char lastCh = line[lastChIndex];

    if (lastCh == COMMA) /* Checks for extraneous comma error */
        error = EXTRANEOUS_COMMA;
    else if (lastCh != NULL_TERMINATOR && lastCh != ENTER_KEY) /* Checks for extraneous text error */
        error = EXTRANEOUS_TXT;
    else /* No extraneous text! */
        error = NO_ERROR;
    return error;
}

/* Checks for errors in the stop command.
 * Returns NO_ERROR if there are no errors, otherwise the specific error caught. */
Error checkStopError(const char *line)
{
    Error error = NO_ERROR; /* Value to return, we assume there is no error. */
    char lastCh = line[nextWordIndex(line, ZERO_INDEX)]; /* First char after "stop". */

    if (lastCh != NULL_TERMINATOR && lastCh != ENTER_KEY) /* Checks for extraneous text error */
        error = EXTRANEOUS_TXT;
    else /* No stop errors! */
        error = NO_ERROR;
    return error;
}

/* Checks if an input line is too long ( > 80).
 * param const char *line is the input line.
 * Returns TRUE if the line is too long, otherwise FALSE. */
boolean isLineTooLong(const char *line)
{
    /* The only situation where a line is too long is when it doesn't end with '\n'. */
    return (line[strlen(line) - 1] != ENTER_KEY)? TRUE : FALSE;
}