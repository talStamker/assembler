.entry MAIN
 add r2,STR
LOOP: jmp END
 prn #-5
 sub r1, r4
 inc K
 mov S1.2 ,r3
 bne LOOP
END: hlt