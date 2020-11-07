#pragma once

// C Standard Library Headers
#include <stdbool.h>

typedef struct
{
	char* data;
	unsigned int length;
} string;

// Duplicate an string
// Returns char* on success, or NULL on failure
char* c_duplicate_string_c(const char* text);

// Create an string using an existing const char* string
// Returns string* on success, or NULL on failure
string* create_string(const char* text);

// Free an string
// Returns true on success, or false on failure
bool free_string(string* string_handle);

// Append an string to the string
// Returns string* on success, or NULL on failure
string* append_string(string* existing_string, string* new_string);

// Append an string to the string
// Returns string* on success, or NULL on failure
string* append_string_c(string* existing_string, const char* new_string);

// Append an string to the string
// Returns char* on success, or NULL on failure
char* c_append_string_c(char* existing_string, const char* new_string);

// Replace an source string with the replacement string
// Returns string* on success, or NULL on failure
string* replace_string(string* string_handle, const string* source_string, const string* replacement_string);

// Replace an source string with the replacement string
// Returns string* on success, or NULL on failure
string* replace_string_c(string* string_handle, const char* source_string, const char* replacement_string);

// Replace an source string with the replacement string
// Returns char* on success, or NULL on failure
char* c_replace_string_c(char* string_handle, const char* source_string, const char* replacement_string);
