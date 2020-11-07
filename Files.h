#pragma once

// C Standard Library Headers
#include <stdbool.h>

typedef struct
{
	unsigned char* data;
	unsigned long long size;
} data_buffer;

// Create an buffer
// Returns data_buffer* on success, or NULL on failure
data_buffer* create_buffer(unsigned char* data, unsigned long long size);

// Free an buffer
// Returns true on success, or false on failure
bool free_buffer(data_buffer* buffer);

// Check if path exists
// Returns true on success, or false on failure
bool check_if_exists(const char* path);

// Check if path is a file
// Returns true on success, or false on failure
bool check_if_file(const char* path);

// Check if path is a directory
// Returns true on success, or false on failure
bool check_if_directory(const char* path);

// Get file length
// Returns file length on success, or 0 on failure
unsigned long long get_file_length(const char* path);

// Read an file
// Returns data_buffer* on success, or NULL on failure
data_buffer* read_file(const char* path);

// Write an file
// Returns true on success, or false on failure
bool write_file(const char* path, const data_buffer* buffer);
