
; Syntax error testing file.

; Label error testing:

; EXPECTED_LABEL_ERR
: stop

; EMPTY_BETWEEN_LABEL_AND_COLON_ERR
        label   :stop

; LABEL_START_WITH_NUM_ERR
1label:stop

; LABEL_START_WITH_ILLEGAL_CHAR_ERR
-label:stop

; LABEL_CONTAINS_ILLEGAL_CHAR_ERR
labe-l:stop

; LABEL_TOO_LONG_ERR
l012345678901234567890123456789m:stop

; LABEL_IS_SAVED_WORD_ERR
stop:stop

; MULTIPLE_CONS_COLONS_ERR
 label: :

; COMMA_AFTER_LABEL_ERR
 label:,stop

; finish label syntax errors.


; Command syntax errors:

; EXPECTED_OP_GUI_ERR
label:

; COMMA_AFTER_COMMAND_ERR
mov,

; Finish command syntax errors.


; Guidance syntax errors:

; EXPECTED_GUIDANCE_ERR
l:.

; MULT_DOTS_IN_GUIDANCE_ERR
..

; WRONG_CASE_GUIDANCE_ERR,
.sTring "a"

; UNDEFINED_GUIDANCE_ERR,
.guidance

; Finish guidance syntax errors.


; Operation syntax errors:

; MISSING_GUIDANCE_DOT_ERR
entry a

; WRONG_CASE_OPERATION_ERR
mOv a , a

; UNDEFINED_OPERATION_ERR
operation

; Finish Operation syntax errors.


; General argument errors:

; EXPECTED_COMMA_AND_ARGUMENT_ERR
 l:mov @r0

; EXPECTED_COMMA_ERR
mov @r0 @r0

; EXPECTED_ARGUMENT_ERR
cmp @r0,

; MULTIPLE_CONS_COMMAS_ERR
.data 1,,,,,,2

; Finish general argument errors.


; String argument syntax errors:

; MISSING_OPEN_QUOTES_IN_STRING
.string abc"

; MISSING_CLOSING_QUOTES_IN_STRING
.string "abc

; UNPRINTABLE_CHARS_IN_STRING_ERR
.string "♔♔♔"

; Finish string argument syntax errors.


; Instant value argument syntax errors:

; VALUE_IS_ONLY_SIGN_ERR
.data 1,+,2

; MULTIPLE_SIGNS_IN_VALUE_ERR
cmp --2,@r1

; INSTANT_VALUE_IS_FLOAT_ERR
mov -132.1,@r0

; INSTANT_VALUE_IS_ILLEGAL_NUMBER_ERR
.data +2,-2,32.2.2

; Finish instant value argument syntax errors.


; Label argument syntax errors:

; ARG_LABEL_TOO_LONG_ERR
mov @r0,l012345678901234567890123456789z

; ILLEGAL_CHARS_IN_DIRECT_ARG_ERR
lea l1.d,

; Finish label argument syntax errors.


; Register argument syntax errors:

; EXPECTED_REGISTER_ERR
mov @,@r0

; MULTIPLE_CONS_AT_ERR
lea @@r1

; MISSING_REG_LETTER_ERR
mov @r0, @0

; CAPITAL_REGISTER_LETTER_ERR
mov @R0,@r0

; WRONG_REGISTER_LETTER_ERR
add @t0, @r1

; EXPECTED_REGISTER_NUMBER_ERR
sub @r, @r1

; ILLEGAL_REGISTER_NUMBER_ERR
lea @r8

; EXTRANEOUS_TEXT_AFTER_REG_ERR
mov @r123,@r1

; Finish register argument syntax errors.


; Extraneous text errors:

; EXTRANEOUS_COMMA_ERR
mov @r0,@r0,

; EXTRANEOUS_TXT_ERR
stop ,dads

; EXPECTED_COMMA_OR_EXTRANEOUS_TEXT_ERR
.data 1,+2 -2

; EXPECTED_ARG_OR_EXTRANEOUS_COMMA_ERR
.entry a,

; Finish extraneous text errors.