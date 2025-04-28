#include <stdio.h>

int arraySearch(int *p_a, int arr_size, int target)
{
    int result = -1;

    asm volatile(
        "add t0, zero, zero\n\t"
	"add t1, t0, %[p_a]\n\t"
	"add t3, zero, %[arr_size]\n\t"
	"add t4, zero, %[target]\n\t"
"LOOP:\n\t"
	"blt t0, t3, LOOP2\n\t"
	"addi t0, zero, -1\n\t"
	"j EXIT\n\t"
"LOOP2:\n\t"
	"slli t5, t0, 2\n\t"
	"add t5, t1, t5\n\t"
	"lw t6, 0(t5)\n\t"
	"sub t2, t6, t4\n\t"
	"beq t2, zero, EXIT\n\t"
	"addi t0, t0, 1\n\t"
	"j LOOP\n\t"
"EXIT:\n\t"
	"add %[result], t0, zero\n\t"
	:[result]"+r"(result)
        :[p_a]"r"(p_a), [arr_size]"r"(arr_size), [target]"r"(target)
	:"t0","t1","t3","t4","t5","t6","t2","memory");

    return result;
}

// Main function to test the implementation
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
    int target;
    fscanf(input, "%d", &target);
    fclose(input);

    int *p_a = &arr[0];

    int index = arraySearch(p_a, arr_size, target);

    // Print the result
    printf("%d ", index);
    printf("\n");

    return 0;
}
