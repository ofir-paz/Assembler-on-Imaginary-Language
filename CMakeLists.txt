cmake_minimum_required(VERSION 3.25)
project(mmn_14 C)

set(CMAKE_C_STANDARD 90)

add_executable(mmn_14 main.c new-data-types/boolean.h
        errors/error_check.c errors/error_handle.c
        transitions/pre-processor.c  transitions/pre-processor.h FileHandling/readFromFile.c
        FileHandling/readFromFile.h
        FileHandling/writeToFile.c FileHandling/writeToFile.h encoding/encoding-finals/opcodes.h
        encoding/encoding-finals/addressing_methods.h transitions/first-transition.c
        transitions/first-transition.h
        encoding/encoding-finals/encoding_types.h
        encoding/encoding-finals/encoding_types.h
        encoding/encoding-finals/encoding_types.h assembler.c assembler.h errors/warnings.c
        errors/warnings.h general-enums/indexes.h diagnoses/diagnose_line.c
        diagnoses/diagnose_line.h encoding/encoding-finals/guidance.h
        new-data-types/process_result.h errors/system_errors.c errors/system_errors.h
        errors/errors.c errors/errors.h FileHandling/fileHelpMethods.c
        FileHandling/fileHelpMethods.h errors/error_types/SystemError.h
        errors/error_types/SyntaxError.h errors/error_types/LogicalError.h
        NameTable/NameTable.c encoding/encoding.c encoding/encoding.h
        errors/error_types/ImgSystemError.h diagnoses/diagnose_util.c
        diagnoses/diagnose_util.h new-data-types/word_number.h NameTable/NameTable.h
        general-enums/programFinals.h
        errors/error_types/error_constant.h errors/error_types/error_types.h
        errors/PreProcessorErrors/PreProcessorErrors.c
        errors/PreProcessorErrors/PreProcessorErrors.h diagnoses/assembler_lang_related_diagnoses.c
        diagnoses/assembler_lang_related_diagnoses.h encoding/encoding-finals/encoding_finals.h
        encoding/encoding-finals/sentence_types.h assembler_ast/assembler_ast.c assembler_ast/assembler_ast.h
        encoding/encoding-finals/registers.h transitions/first_transition_util.c
        transitions/first_transition_util.h util/memoryUtil.c util/memoryUtil.h
        util/stringsUtil.c util/stringsUtil.h general-enums/assemblerFinals.h util/numberUtil.c
        util/numberUtil.h encoding/encoding-finals/label_types.h errors/FirstTransitionErrors/FirstTransitionErrors.c errors/FirstTransitionErrors/FirstTransitionErrors.h transitions/second_transition.c transitions/second_transition.h
        encoding/wordHandling.c
        encoding/wordHandling.h
        encoding/encodingUtil.c
        encoding/encodingUtil.h
        encoding/encoding-finals/ranges.h
        encoding/encodingDataStructures/MemoryImage.h
        encoding/encodingDataStructures/word.h
)
