/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * This file has the functions to check errors in the second transition
 * phase of the assembler.
 */

/* ---Include header files--- */
#include <stddef.h>
#include "../../new-data-types/boolean.h"
#include "../../NameTable/NameTable.h"
#include "../../assembler_ast/assembler_ast.h"
#include "../error_types/error_types.h"
#include "../assembler_errors.h"
/* -------------------------- */

/* ---Finals--- */
/* ------------ */

/* ---Macros--- */
/* ------------ */

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

/*
 * Handles a line error during the second transition phase, updating the error status.
 * Will do nothing if there was no error.
 *
 * @param   *file_name      The name of the file where the error occurred.
 * @param   currLine        The current line number where the error occurred.
 * @param   lineError       The specific error that occurred (can be NO_ERROR).
 * @param   *wasError       Pointer to a boolean indicating whether an error was encountered.
 */
void handleLineErrorInSecondTrans(const char *file_name, int currLine, Error lineError,
                                  boolean *wasError)
{
    if (lineError != NO_ERROR) /* Act only if there was an error. */
    {
        handle_assembler_error(file_name, currLine, lineError);
        *wasError = TRUE; /* Update error status. */
    }
}

/*
 * Checks for a logical error related to an entry label.
 * The only logical error that needs to be checked in the second transition is
 * whether an entry label is defined in the file.
 *
 * @param   *entLabel       The entry label to check for errors.
 * @param   *normalLabels   Pointer to the NameTable containing normal labels.
 *
 * @return  The specific error found, or NO_ERROR if there was no error.
 */
LogicalError checkEntryLabelError(const char *entLabel, NameTable *normalLabels)
{
    return (isNameInTable(normalLabels, entLabel))? NO_ERROR : ENTRY_LABEL_NOT_DEFINED_IN_FILE_ERR;
}

/*
 * Checks for a logical error related to an undefined label argument.
 *
 * @param   *lineAst        The Abstract Syntax Tree (AST) for the line to check.
 * @param   *normalLabels   Pointer to the NameTable containing normal labels.
 * @param   *extLabels      Pointer to the NameTable containing external labels.
 *
 * @return  The specific error found, or NO_ERROR if there was no error.
 */
LogicalError checkUndefinedLabelArgumentError(ast_t *lineAst, NameTable *normalLabels,
                                              NameTable *extLabels)
{
    LogicalError undefinedLabelArgError = NO_ERROR; /* Logical error to return. */

    /* Need to check for undefined label arg only in direction sentences. */
    if (getSentence(lineAst).sentenceType == DIRECTION_SENTENCE)
    {
        arg_node_t *currArg = getArgList(lineAst); /* First argument. */
        /* Go through all the arguments and check for undefined label. */
        while (currArg != NULL && undefinedLabelArgError == NO_ERROR)
        {
            if (getArgData(currArg).dataType == STRING) /* If the argument is label. */
                /* If it is undefined. */
                if (isNameInTable(normalLabels, getArgData(currArg).data.string) == FALSE &&
                    isNameInTable(extLabels, getArgData(currArg).data.string) == FALSE)
                        undefinedLabelArgError = USE_OF_UNDEFINED_LABEL_ERR;

            currArg = getNextNode(currArg); /* Go to next argument. */
        }
    }

    return undefinedLabelArgError;
}