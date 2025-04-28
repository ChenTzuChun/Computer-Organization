#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }
    int arr_size;
    fscanf(input, "%d", &arr_size);
    int arr[arr_size];

    // Read integers from input file into the array
    for (int i = 0; i < arr_size; i++) {
        int data;
        fscanf(input, "%d", &data);
        arr[i] = data;
    }
    fclose(input);

    int *p_a = &arr[0];

    // array a bubble sort
    /* Original C code segment
    for (int i = 0; i < arr_size - 1; i++) {
        for (int j = 0; j < arr_size - i -1; j++) {
            if (*(p_a + j) > *(p_a + j + 1)) {
                int tmp = *(p_a + j);
                *(p_a + j) = *(p_a + j + 1);
                *(p_a + j + 1) = tmp;
            }
        }
    }
    */

    for (int i = 0; i < arr_size - 1; i++) {
        for (int j = 0; j < arr_size - i - 1; j++) {
            asm volatile(
                "slli t0, %[j], 2\n\t"
		"add t0, %[p_a], t0\n\t"
		"lw t1, 0(t0)\n\t"
		"addi t2, t0, 4\n\t"
		"lw t3, 0(t2)\n\t"
		"sub t4, t1, t3\n\t"
		"ble t4, zero, EXIT\n\t"
		"sw t1, 0(t2)\n\t"
		"sw t3, 0(t0)\n\t"
	"EXIT:\n\t"
		:
                :[p_a]"r"(p_a), [j]"r"(j)
		:"t0", "t1", "t2", "t3", "t4", "memory");
        }
    }
    p_a = &arr[0];
    for (int i = 0; i < arr_size; i++)
        printf("%d ", *p_a++);
    printf("\n");
    return 0;
}    
