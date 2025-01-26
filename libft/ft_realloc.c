#include "libft.h"


void *ft_realloc(void *ptr, size_t old_size, size_t new_size) {
    void *new_ptr;

    // If the new size is 0, free the old pointer and return NULL
    if (new_size == 0) {
        free(ptr);
        return NULL;
    }

    // If the old pointer is NULL, allocate memory using ft_calloc
    if (!ptr)
        return ft_calloc(1, new_size);

    // Allocate new memory
    new_ptr = malloc(new_size);
    if (!new_ptr)
        return NULL;

    // Copy the contents of the old memory to the new memory
    if (old_size > 0) {
        size_t copy_size = old_size < new_size ? old_size : new_size; // Copy the smaller of old_size and new_size
        ft_memcpy(new_ptr, ptr, copy_size);
    }

    // Free the old memory
    free(ptr);

    return new_ptr;
}
