cmake_minimum_required(VERSION 3.25)
project(mmn_14 C)

set(CMAKE_C_STANDARD 90)

add_executable(mmn_14 main.c help_methods.c help_methods.h new-data-types/boolean.h
        new-data-types/Error.h errors/error_check.c errors/error_handle.c
        transitions/pre-processor.c  transitions/pre-processor.h fileHandling/readFromFile.c
        fileHandling/readFromFile.h
        fileHandling/writeToFile.c fileHandling/writeToFile.h encoding/encoding-finals/opcodes.h
        encoding/encoding-finals/addressing-methods.h transitions/first-transition.c
        transitions/first-transition.h transitions/second-transition.c
        transitions/second-transition.h encoding/encoding-finals/encoding-type.h encoding/encoding-finals/encoding-type.h
        encoding/encoding-finals/encoding-type.h assembler_handle.c assembler_handle.h errors/warnings.c errors/warnings.h general-enums/neededFinals.h transitions/diagnose_input.c transitions/diagnose_input.h new-data-types/param_num.h encoding/encoding-finals/sentenceType.h new-data-types/process_result.h errors/system_errors.c errors/system_errors.h errors/errors.c errors/errors.h fileHandling/fileHelpMethods.c fileHandling/fileHelpMethods.h fileHandling/fileErrors.c fileHandling/fileErrors.h errors/error_types/SystemError.h errors/error_types/SyntaxError.h errors/error_types/LogicalError.h LinkedList/LinkedList.c LinkedList/LinkedList.h encoding/encode-line.c encoding/encode-line.h encoding/encoding-help-methods.c encoding/encoding-help-methods.h)
