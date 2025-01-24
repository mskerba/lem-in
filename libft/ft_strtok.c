#include "libft.h"

char *ft_strtok(char *str, const char *delim)
{
    static char *save_ptr; // Save the state for subsequent calls
    char *token;

    // If `str` is not NULL, initialize `save_ptr`
    if (str != NULL)
        save_ptr = str;

    // If `save_ptr` is NULL, return NULL (no more tokens)
    if (save_ptr == NULL)
        return NULL;

    // Skip initial delimiters
    while (*save_ptr && ft_strchr(delim, *save_ptr))
        save_ptr++;

    // If we reach the end of the string, return NULL
    if (*save_ptr == '\0')
        return NULL;

    // Mark the beginning of the token
    token = save_ptr;

    // Find the next delimiter
    while (*save_ptr && !ft_strchr(delim, *save_ptr))
        save_ptr++;

    // If we find a delimiter, replace it with '\0' and advance `save_ptr`
    if (*save_ptr)
    {
        *save_ptr = '\0';
        save_ptr++;
    }

    return token;
}
