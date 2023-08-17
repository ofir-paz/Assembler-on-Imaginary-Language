
; Logical error testing file.


; Label related logical errors:

; MULTIPLE_NORMAL_LABEL_DEF_ERR
label: .data 1
label: .data 1

; Finish label related logical errors.


; Guidance related logical errors:

; ARGUMENT_IS_NOT_LABEL_ERR
.entry 1
.extern @r0

; EXPECTED_NUMBER_ARG_ERR
.data label

; Finish guidance related logical errors.


; Addressing methods related logical errors:

; ILLEGAL_DEST_ARG_MTD_ERR
mov @r0,0

; ILLEGAL_SRC_ARG_MTD_ERR
lea @r0, @r0

; Finish Addressing methods related logical errors.


; Entry label related logical errors:

; MULTIPLE_ENTRY_LABEL_DEF_ERR
.entry label, label
.entry label

; Finish entry label related logical errors.


; Extern label related logical errors:

; MULTIPLE_EXTERN_LABEL_DEF_ERR
.extern ext1, ext1
.extern ext1

; Finish extern label related logical errors.


; Label tables related logical errors:

; LABEL_DEFINED_AS_NORMAL_AND_EXT_ERR
ext1:.string ""

; LABEL_DEFINED_AS_ENT_AND_EXT_ERR
.entry ext1

; Finish label tables related logical errors.