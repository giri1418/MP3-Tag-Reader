#ifndef READ_VALIDATE_H
#define READ_VALIDATE_H

#include <stdio.h>

// Enumeration to represent the operation selected by the user
typedef enum
{
    VIEW,
    EDIT,
    HELP,
    ERROR
} OperationType;

// Check the operation type based on command-line arguments
OperationType check_operation_type(char *argv[]);
// Validate command-line arguments for view operation
int validate_view_args(char *argv[]);
// Validate command-line arguments for edit operation
int validate_edit_args(char *argv[]);

#endif