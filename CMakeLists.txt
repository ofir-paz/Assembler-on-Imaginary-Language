cmake_minimum_required(VERSION 3.25)
project(mmn_14 C)

set(CMAKE_C_STANDARD 90)

add_executable(mmn_14 main.c general_help_methods.c general_help_methods.h new-data-types/boolean.h
        errors/error_check.c errors/error_handle.c
        transitions/pre-processor.c  transitions/pre-processor.h FileHandling/readFromFile.c
        FileHandling/readFromFile.h
        FileHandling/writeToFile.c FileHandling/writeToFile.h encoding/encoding-finals/opcodes.h
        encoding/encoding-finals/addressing-methods.h transitions/first-transition.c
        transitions/first-transition.h transitions/second-transition.c
        transitions/second-transition.h encoding/encoding-finals/encoding-type.h
        encoding/encoding-finals/encoding-type.h
        encoding/encoding-finals/encoding-type.h assembler.c assembler.h errors/warnings.c
        errors/warnings.h general-enums/indexes.h diagnoses/diagnose_line.c
        diagnoses/diagnose_line.h new-data-types/param_num.h encoding/encoding-finals/sentenceType.h
        new-data-types/process_result.h errors/system_errors.c errors/system_errors.h
        errors/errors.c errors/errors.h FileHandling/fileHelpMethods.c
        FileHandling/fileHelpMethods.h errors/error_types/SystemError.h
        errors/error_types/SyntaxError.h errors/error_types/LogicalError.h
        NameTable/NameTable.c encoding/encoding.c encoding/encoding.h
        encoding/encoding-help-methods.c encoding/encoding-help-methods.h
        errors/error_types/ImgSystemError.h diagnoses/diagnose_help_methods.c
        diagnoses/diagnose_help_methods.h new-data-types/word_number.h NameTable/NameTable.h
        general-enums/programEnums.h
        errors/error_types/error_constant.h errors/error_types/error_types.h transitions/TransitionNumber.h errors/PreProcessorErrors/PreProcessorErrors.c errors/PreProcessorErrors/PreProcessorErrors.h)
