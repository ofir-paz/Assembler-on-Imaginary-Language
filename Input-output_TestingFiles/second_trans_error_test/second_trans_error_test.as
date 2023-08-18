
; Second transition error test file.

.entry label1

; ENTRY_LABEL_NOT_DEFINED_IN_FILE_ERR
.entry label2

; USE_OF_UNDEFINED_LABEL_ERR
label1:dec label2

.extern label1