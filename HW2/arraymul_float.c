"SFLOOP:\n\t"
    "addi %[add_cnt], %[add_cnt], 1\n\t"
    "addi %[arr_size], %[arr_size], -1\n\t"
    
    "addi %[flw_cnt], %[flw_cnt], 1\n\t"
    "flw f0, 0(%[h])\n\t"
    "addi %[flw_cnt], %[flw_cnt], 1\n\t"
    "flw f1, 0(%[x])\n\t"
    
    "addi %[fmul_cnt], %[fmul_cnt], 1\n\t"
    "fmul.s %[result], %[result], f0\n\t"
    "addi %[fmul_cnt], %[fmul_cnt], 1\n\t"
    "fmul.s %[result], %[result], f1\n\t"
    
    "addi %[add_cnt], %[add_cnt], 1\n\t"
    "addi %[h], %[h], 4\n\t"
    "addi %[add_cnt], %[add_cnt], 1\n\t"
    "addi %[x], %[x], 4\n\t"
    
    "addi %[others_cnt], %[others_cnt], 1\n\t"
    "bne %[arr_size], x0, SFLOOP\n\t"
"SFEXIT:\n\t"
