
; Presume the body of the macro is valid.

mcro m1
.string ""
endmcro
m1

mcro a
mov @r0, @r1
endmcro

mcro stop
.data 1
endmcro

stop

mcro ext ext1
.string ""
endmcro ext1

ext

; line too long aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa