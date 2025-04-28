#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Split the linked list into two parts
void splitList(Node *head, Node **firstHalf, Node **secondHalf)
{
    asm volatile(
        "mv a0, %0\n\t"
        "mv a1, %1\n\t"//firstHalf
        "mv a2, %2\n\t"//secondHalf
        "sd a0, 0(a1)\n\t"
        "beqz a0, end_split\n\t"
        "ld a3, 8(a0)\n\t"// 8 is the offset of next pointer
        "beqz a3, end_split\n\t"
        
        "mv a4, a0\n\t"// slow = head
        "ld a5, 8(a0)\n\t"// fast = head->next
        
    "find_middle:\n\t"
        "beqz a5, middle_found\n\t"
        "ld a5, 8(a5)\n\t"// fast = fast->next
        "beqz a5, middle_found\n\t"
        "ld a5, 8(a5)\n\t"// repeat fast = fast->next, make it faster
        "beqz a5, middle_found\n\t"
        "ld a4, 8(a4)\n\t"// slow = slow->next
        "j find_middle\n\t"
        
    "middle_found:\n\t"
        "ld a5, 8(a4)\n\t"
        "sd a5, 0(a2)\n\t"
        // Set slow->next to NULL to terminate first half
        "li a5, 0\n\t"
        "sd a5, 8(a4)\n\t"

    "end_split:\n\t"
        :
        : "r"(head), "r"(firstHalf), "r"(secondHalf)
        : "a0", "a1", "a2", "a3", "a4", "a5", "memory"
        );
}

// Merge two sorted linked lists
Node *mergeSortedLists(Node *a, Node *b)
{
    Node *result = NULL;
    Node *tail = NULL;

    asm volatile(
        "mv a0, %0\n\t"         // a0 = a
        "mv a1, %1\n\t"         // a1 = b

        "beqz a0, ONLYB\n\t"
        "beqz a1, ONLYA\n\t"
        
        // Compare first nodes to determine initial iteration
        "lw a2, 0(a0)\n\t"
        "lw a3, 0(a1)\n\t"
        "ble a2, a3, start_a\n\t"
        
        "mv a4, a1\n\t"         // stat w/ b
        "ld a1, 8(a1)\n\t"      
        "j initial_end\n\t"
        
    "start_a:\n\t"
        "mv a4, a0\n\t"         // start w/ a
        "ld a0, 8(a0)\n\t"
        
    "initial_end:\n\t"
        "mv a5, a4\n\t"         // tail = result
        "j LOOP\n\t"
        
    "ONLYA:\n\t"
        "mv a4, a0\n\t"         // result = a
        "j end_merge\n\t"
        
    "ONLYB:\n\t"
        "mv a4, a1\n\t"         // result = b
        "j end_merge\n\t"
        
    "LOOP:\n\t"
        "beqz a0, append_b\n\t"
        "beqz a1, append_a\n\t"
        
        "lw a2, 0(a0)\n\t"
        "lw a3, 0(a1)\n\t"
        "ble a2, a3, take_a\n\t"
        
        "sd a1, 8(a5)\n\t" 
        "mv a5, a1\n\t"
        "ld a1, 8(a1)\n\t"
        "j LOOP\n\t"
        
    "take_a:\n\t"
        "sd a0, 8(a5)\n\t" 
        "mv a5, a0\n\t"    
        "ld a0, 8(a0)\n\t" 
        "j LOOP\n\t"
        
    "append_b:\n\t"
        "beqz a1, end_merge\n\t"
        "sd a1, 8(a5)\n\t" 
        "j end_merge\n\t"
        
    "append_a:\n\t"
        "beqz a0, end_merge\n\t"
        "sd a0, 8(a5)\n\t" 
        
    "end_merge:\n\t"
        "mv %2, a4\n\t"
        : "=r"(a), "=r"(b), "=r"(result)
        : "0"(a), "1"(b)
        : "a0", "a1", "a2", "a3", "a4", "a5", "memory"
	);

    return result;
}

// Merge Sort function for linked list
Node *mergeSort(Node *head)
{
    if (!head || !head->next)
        return head; // Return directly if there is only one node

    Node *firstHalf, *secondHalf;
    splitList(head, &firstHalf,
              &secondHalf); // Split the list into two sublists

    firstHalf = mergeSort(firstHalf);   // Recursively sort the left half
    secondHalf = mergeSort(secondHalf); // Recursively sort the right half

    return mergeSortedLists(firstHalf, secondHalf); // Merge the sorted sublists
}

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
    int list_size;
    fscanf(input, "%d", &list_size);
    Node *head = (list_size > 0) ? (Node *)malloc(sizeof(Node)) : NULL;
    Node *cur = head;
    for (int i = 0; i < list_size; i++) {
        fscanf(input, "%d", &(cur->data));
        if (i + 1 < list_size)
            cur->next = (Node *)malloc(sizeof(Node));
        cur = cur->next;
    }
    fclose(input);

    // Linked list sort
    head = mergeSort(head);

    cur = head;
    while (cur) {
        printf("%d ", cur->data);
        asm volatile(
            "ld %0, 8(%0)\n\t"  // cur = cur->next
            : "+r"(cur)
            :
            : "memory"
	    );
    }
    printf("\n");
    return 0;
}
