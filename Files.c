// C Standard Library Headers
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

// Program Headers
#include "Files.h"

// Mode definitions
#define mode_read "rb"
#define mode_write "wb"

// Status definitions
#define status_directory 0040000
#define status_file 0100000

// Create an buffer
// Returns data_buffer* on success, or NULL on failure
data_buffer* create_buffer(const unsigned char* data, const unsigned long long size)
{
	// Check if the data pointer and size are valid
	if (data != NULL && size > 0)
	{
		// Create and fill the data buffer structure
		data_buffer* buffer = malloc(sizeof(data_buffer));
		buffer->data = data;
		buffer->size = size;

		// Return the buffer
		return buffer;
	}
	else
	{
		// Return NULL
		return NULL;
	}
}

// Free an buffer
// Returns true on success, or false on failure
bool free_buffer(const data_buffer* buffer)
{
	// Check if the path is valid
	if (buffer != NULL)
	{
		// Free the buffer's memory and structure
		free(buffer->data);
		free(buffer);

		// Return true
		return true;
	}
	else
	{
		// Return false
		return false;
	}
}

// Check if path exists
// Returns true on success, or false on failure
bool check_if_exists(const char* path)
{
	// Check if the path is valid
	if (path != NULL)
	{
		// Attempt to open the file
		FILE* file = fopen(path, mode_read);

		// Check if the file has been opened
		if (file != NULL)
		{
			// Close the file
			fclose(file);

			// Return true
			return true;
		}
		else
		{
			// Return false
			return false;
		}
	}
	else
	{
		// Return false
		return false;
	}
}

// Check if path is a file
// Returns true on success, or false on failure
bool check_if_file(const char* path)
{
	// Check if the path is valid
	if (path != NULL)
	{
		// Check the path's status
		struct stat path_status;
		int check_status_result = stat(path, &path_status);
		if (check_status_result == 0)
		{
			// Check if the path's status mode contains the file flag
			if (path_status.st_mode & status_file)
			{
				// Return true
				return true;
			}
			else
			{
				// Return false
				return false;
			}
		}
		else
		{
			// Return false
			return false;
		}
	}
	else
	{
		// Return false
		return false;
	}
}

// Check if path is a directory
// Returns true on success, or false on failure
bool check_if_directory(const char* path)
{
	// Check if the path is valid
	if (path != NULL)
	{
		// Check the path's status
		struct stat path_status;
		int check_status_result = stat(path, &path_status);
		if (check_status_result == 0)
		{
			// Check if the path's status mode contains the directory flag
			if (path_status.st_mode & status_directory)
			{
				// Return true
				return true;
			}
			else
			{
				// Return false
				return false;
			}
		}
		else
		{
			// Zglaszamy niepowodzenie
			return 0;
		}
	}
	else
	{
		// Return false
		return false;
	}
}

// Get file length
// Returns file length on success, or 0 on failure
unsigned long long get_file_length(const char* path)
{
	// Check if the path is valid
	if (path != NULL)
	{
		// Probujemy otworzyc plik
		FILE* file = fopen(path, mode_read);

		// Check if the file has been opened
		if (file != NULL)
		{
			// Seek to the end of the file
			fseek(file, 0, SEEK_END);

			// Get the current position in the file
			unsigned long long length = ftell(file);

			// Close the file
			fclose(file);

			// Return length
			return length;
		}
		else
		{
			// Return 0
			return 0;
		}
	}
	else
	{
		// Return 0
		return 0;
	}
}

// Read an file
// Returns data_buffer* on success, or NULL on failure
data_buffer* read_file(const char* path)
{
	// Check if the path is valid
	if (path != NULL)
	{
		// Attempt to open the file
		FILE* file = fopen(path, mode_read);

		// Check if the file has been opened
		if (file != NULL)
		{
			// Seek to the end of the file
			fseek(file, 0, SEEK_END);

			// Get the current position in the file
			const unsigned long length = ftell(file);

			// Return to the start of the file
			fseek(file, 0, SEEK_SET);

			// Check if the file size is valid
			if (length > 0)
			{
				// Allocate memory for the file's data buffer
				unsigned char* data = malloc(length);

				// Attempt to read the file's data
				unsigned long long bytes_read = fread(data, sizeof(unsigned char), length, file);

				// Close the file
				fclose(file);

				// Check if the entire file was read
				if (bytes_read == length)
				{
					// Allocate memory for the buffer's structure and fill it
					data_buffer* buffer = malloc(sizeof(data_buffer));
					buffer->data = data;
					buffer->size = length;

					// Return the buffer
					return buffer;
				}
				else
				{
					// Free the data buffer
					free(data);

					// Return NULL
					return NULL;
				}
			}
			else
			{
				// Close the file
				fclose(file);

				// Return NULL
				return NULL;
			}
		}
		else
		{
			// Return NULL
			return NULL;
		}
	}
	else
	{
		// Return NULL
		return false;
	}
}

// Write an file
// Returns true on success, or false on failure
bool write_file(const char* path, const data_buffer* buffer)
{
	// Check if the path and buffer pointer are valid
	if (path != NULL && buffer != NULL)
	{
		// Attempt to open the file
		FILE* file = fopen(path, mode_write);

		// Check if the file has been opened
		if (file != NULL)
		{
			// Attempt to write the file
			unsigned long long bytes_written = fwrite(buffer->data, sizeof(unsigned char), buffer->size, file);

			// Force the system to write the file
			fflush(file);

			// Close the file
			fclose(file);

			// Check if the entire file was written
			if (bytes_written == buffer->size)
			{
				// Return true
				return true;
			}
			else
			{
				// Return NULL
				return false;
			}
		}
		else
		{
			// Return NULL
			return false;
		}
	}
	else
	{
		// Return NULL
		return false;
	}
}
