// C Standard Library Headers
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Program Headers
#include "Main.h"
#include "Files.h"
#include "Strings.h"

#define InsydeFlash_BIOSIMG_Signature_Length 16 
const unsigned char InsydeFlash_BIOSIMG_Signature[] = { 0x24, 0x5F, 0x49, 0x46, 0x4C, 0x41, 0x53, 0x48, 0x5F, 0x42, 0x49, 0x4F, 0x53, 0x49, 0x4D, 0x47 }; // "$_IFLASH_BIOSIMG"

typedef struct
{
	unsigned char signature[InsydeFlash_BIOSIMG_Signature_Length];
	unsigned int full_size;
	unsigned int used_size;
} InsydeFlash_Firmware_Header;

// Find an pattern in an buffer
// Returns unsigned char* on success, or NULL on failure
unsigned char* find_pattern(const unsigned char* start, const unsigned char* end, const unsigned char* pattern, const unsigned long length)
{
	// Check if all the pointers and length are valid
	if (start != NULL && end != NULL && pattern != NULL && length > 0 && end > start)
	{
		unsigned int scan = 0;
		unsigned int bad_char_skip[256];
		unsigned int last = length - 1;;
		unsigned int slen = end - start;;

		for (scan = 0; scan <= 255; scan++)
		{
			bad_char_skip[scan] = length;
		}

		for (scan = 0; scan < last; scan++)
		{
			bad_char_skip[pattern[scan]] = last - scan;

		}

		while (slen >= length)
		{
			for (scan = last; start[scan] == pattern[scan]; scan--)
			{
				if (scan == 0)
				{
					return (unsigned char*)(start);
				}
			}

			slen -= bad_char_skip[start[last]];
			start += bad_char_skip[start[last]];
		}

		// Return NULL
		return NULL;
	}
	else
	{
		// Return NULL
		return NULL;
	}
}

// Program Entry Point
int main(int argument_count, char* argument_list[])
{
	// Print program header
	printf("Insyde UEFI Firmware Extractor v1.0.1\n");

	if (argument_count == 1)
	{
		// Print usage
		printf("Usage: input_file [output_file]\n");

		// Report success
		return 0;
	}
	else if (argument_count == 2 || argument_count == 3)
	{
		// Determine the source and target file path
		char* source_path = argument_list[1];
		char* target_path = NULL;
		if (argument_count == 3)
		{
			target_path = argument_list[2];
		}
		else
		{
			target_path = argument_list[1];
			target_path = c_replace_string_c(target_path, ".FD", ".rom");
			target_path = c_replace_string_c(target_path, ".fd", ".rom");
		}

		// Check if the source file exists
		if (check_if_exists(source_path) == true)
		{
			// Attempt to read the source file
			data_buffer* source_buffer = read_file(source_path);
			if (source_buffer != NULL)
			{
				// Attempt to find the insydeflash firmware header
				unsigned char* header_pointer = find_pattern(source_buffer->data, source_buffer->data + source_buffer->size, InsydeFlash_BIOSIMG_Signature, InsydeFlash_BIOSIMG_Signature_Length);
				if (header_pointer != NULL)
				{
					// Map the header pointer to the source file buffer
					InsydeFlash_Firmware_Header* header = (InsydeFlash_Firmware_Header*)(header_pointer);

					// Allocate and zero-fill the target data buffer
					unsigned long target_data_buffer_size = header->used_size;
					unsigned char* target_data_buffer = calloc(target_data_buffer_size, sizeof(unsigned char));

					// Copy the UEFI Image to the target file buffer
					unsigned char* firmware_image_pointer = header_pointer + sizeof(InsydeFlash_Firmware_Header);
					memcpy(target_data_buffer, firmware_image_pointer, target_data_buffer_size);

					// Create the target file buffer
					data_buffer* target_buffer = create_buffer(target_data_buffer, target_data_buffer_size);

					// Attempt to write the modified file
					bool write_result = write_file(target_path, target_buffer);

					// Free the file buffers
					free_buffer(target_buffer);
					free_buffer(source_buffer);

					if (write_result == true)
					{
						return 0;
					}
					else
					{
						// Print error
						printf("Failed to write file \"%s\"", target_path);

						// Return failure
						return 1;
					}
				}
				else
				{
					// Print error
					printf("InsydeFlash firmware signature not found in the file!\n");

					// Free the file buffers
					free_buffer(source_buffer);

					// Return failure
					return 1;
				}
			}
			else
			{
				// Print error
				printf("Failed to read file \"%s\"", source_path);

				// Return failure
				return 1;
			}
		}
		else
		{
			// Print error
			printf("Input file does not exist!\n");

			// Return failure
			return 1;
		}
	}
	else if (argument_count > 3)
	{
		// Print error
		printf("Too many arguments provided!\n");

		// Return failure
		return 1;
	}
}
