"DFLOOP:\n\t"
    "addi %[add_cnt], %[add_cnt], 1\n\t"
    "addi %[arr_size], %[arr_size], -1\n\t"

    "addi %[dlw_cnt], %[dlw_cnt], 1\n\t"
    "fld f0, 0(%[h])\n\t"
    "addi %[dlw_cnt], %[dlw_cnt], 1\n\t"
    "fld f1, 0(%[x])\n\t"

    "addi %[dmul_cnt], %[dmul_cnt], 1\n\t"
    "fmul.d %[result], %[result], f0\n\t"
    "addi %[dmul_cnt], %[dmul_cnt], 1\n\t"
    "fmul.d %[result], %[result], f1\n\t"

    "addi %[add_cnt], %[add_cnt], 1\n\t"
    "addi %[h], %[h], 8\n\t"
    "addi %[add_cnt], %[add_cnt], 1\n\t"
    "addi %[x], %[x], 8\n\t"

    "addi %[others_cnt], %[others_cnt], 1\n\t"
    "bne %[arr_size], x0, DFLOOP\n\t"
"DFEXIT:\n\t"
