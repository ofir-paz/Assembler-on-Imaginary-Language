
; Error testing file

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
 label:  ,

; finish label syntax errors


; Command syntax errors

; EXPECTED_OP_GUI_ERR
label:

; COMMA_AFTER_COMMAND_ERR
mov,

