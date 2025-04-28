    "addi %[others_cnt], %[others_cnt], 1\n\t"
    "vsetvli t0, %[arr_size], e32, m1\n\t"

"Vector_Loop:\n\t"
    "addi %[add_cnt], %[add_cnt], 1\n\t"
    "addi %[arr_size], %[arr_size], -4\n\t"
    
    "addi %[lw_cnt], %[lw_cnt], 1\n\t"
    "vle32.v v0, 0(%[h])\n\t"
    "addi %[lw_cnt], %[lw_cnt], 1\n\t"
    "vle32.v v1, 0(%[x])\n\t"
    
    "addi %[fmul_cnt], %[fmul_cnt], 1\n\t"
    "vfmul.vv v2, v0, v1\n\t"
    "addi %[fadd_cnt], %[fadd_cnt], 1\n\t"
    "vfadd.vf v2, v2, %[id]\n\t"
    
    "addi %[sw_cnt], %[sw_cnt], 1\n\t"
    "vse32.v v2, 0(%[y])\n\t"
    
    "addi %[add_cnt], %[add_cnt], 1\n\t"
    "addi %[h], %[h], 16\n\t"
    "addi %[add_cnt], %[add_cnt], 1\n\t"
    "addi %[x], %[x], 16\n\t"
    "addi %[add_cnt], %[add_cnt], 1\n\t"
    "addi %[y], %[y], 16\n\t"
    
    "addi %[others_cnt], %[others_cnt], 1\n\t"
    "bne %[arr_size], x0, Vector_Loop\n\t"
    
"Vector_EXIT:\n\t"
