/*
 * @author Ofir Paz
 * @version (17/08/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <stdio.h>
#include "../assembler_ast/assembler_ast.h"
/* -------------------------- */

/* warning_t data type. represents all the possible warnings. */
typedef enum {NO_WARNING, LABEL_DEF_ON_ENT_GUID_WARN, LABEL_DEF_ON_EXT_GUID_WARN} warning_t;

/* ---Finals--- */
#define ANSI_COLOR_PURPLE "\x1B[35m"
#define ANSI_COLOR_BLUE     "\x1B[34m"
#define ANSI_COLOR_RESET    "\x1b[0m"
/* ------------ */

/* ---Macros--- */
/* ------------ */

/* ---------------Prototypes--------------- */
void printWarning(warning_t warn, const char *file_name, int lineNumber);
/* ---------------------------------------- */

/*
 * Prints a warning message with information about the warning, file name, and line number.
 *
 * @param   warn            The warning type to print.
 * @param   *file_name      The name of the file where the warning occurred.
 * @param   lineNumber      The line number where the warning occurred.
 */
void printWarning(warning_t warn, const char *file_name, int lineNumber)
{
    /* Array to hold all the different warning messages. */
    const char *warningMSG[] =
            {
            "NO_WARNING",
            "Label definition spotted on .entry guidance (the assembler will ignore the label).",
            "Label definition spotted on .extern guidance (the assembler will ignore the label)."
            };

    /* Print the warning. */
    fprintf(stderr, "\n" ANSI_COLOR_PURPLE "Warning:" ANSI_COLOR_RESET " %s\n", warningMSG[warn]);

    /* Print information about where the warning was found. */
    fprintf(stderr, ANSI_COLOR_BLUE "In file: " ANSI_COLOR_RESET "\"%s\", "
                    ANSI_COLOR_BLUE "On line: " ANSI_COLOR_RESET "%d\n", file_name, lineNumber);
}

/*
 * Handles warnings by finding them if there are, making the necessary changes in the given AST
 * and displaying information about the warning, file name, and line number.
 *
 * @param   *file_name      The name of the file where the warning will be handled (if there is).
 * @param   lineNumber      The line number where the warning will be handled (if there is).
 * @param   *lineAst        The Abstract Syntax Tree (AST) associated with the line.
 */
void handleWarnings(const char *file_name, int lineNumber, ast_t *lineAst)
{
    /* Warnings can happen only on guidance sentences for now. */
    if (getSentence(lineAst).sentenceType == GUIDANCE_SENTENCE)
        /* Distinguish and handle various warnings. */
        switch (getSentence(lineAst).sentence.guidance)
        {
            case ent:
                if (deleteLabel(lineAst) == SUCCESS_CODE)
                    printWarning(LABEL_DEF_ON_ENT_GUID_WARN, file_name, lineNumber);
                break;
            case ext:
                if (deleteLabel(lineAst) == SUCCESS_CODE)
                    printWarning(LABEL_DEF_ON_EXT_GUID_WARN, file_name, lineNumber);
                break;
            default: break;
        }
}