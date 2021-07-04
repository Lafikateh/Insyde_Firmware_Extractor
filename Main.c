// C Standard Library Headers
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define InsydeFlash_BIOSIMG_Signature_Length 16 
const uint8_t InsydeFlash_BIOSIMG_Signature[16] = "$_IFLASH_BIOSIMG";

typedef struct
{
	uint8_t signature[InsydeFlash_BIOSIMG_Signature_Length];
	uint32_t full_size;
	uint32_t used_size;
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
		
		return NULL;
	}
	else
	{
		return NULL;
	}
}

bool read_file(FILE* handle, void* buffer, unsigned int* size)
{
	if(handle != NULL && size != NULL)
	{
		if(buffer != NULL)
		{
			fseek(handle, 0, SEEK_END);
			*size = ftell(handle);
			fseek(handle, 0, SEEK_SET);
			fread(buffer, 1, *size, handle);
		}
		else
		{
			fseek(handle, 0, SEEK_END);
			*size = ftell(handle);
			fseek(handle, 0, SEEK_SET);
		}
		
		return true;
	}
	else
	{
		return false;
	}
}

// Program Entry Point
int main(int argument_count, char* argument_list[])
{
	// Print program header
	printf("Insyde UEFI Firmware Extractor v1.0.2\n");

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
		}

		// Attempt to open the source file
		FILE* source_file = fopen(source_path, "rb");
		if(source_file != NULL)
		{
			// Get the source file size
			unsigned int source_file_size = 0;
			read_file(source_file, NULL, &source_file_size);
			
			// Read the source file
			unsigned char* source_file_buffer = malloc(source_file_size);
			bool read_result = read_file(source_file, source_file_buffer, &source_file_size);
			if (read_result == true)
			{
				// Attempt to find the insydeflash firmware header
				unsigned char* header_pointer = find_pattern(source_file_buffer, source_file_buffer + source_file_size, InsydeFlash_BIOSIMG_Signature, InsydeFlash_BIOSIMG_Signature_Length);
				if (header_pointer != NULL)
				{
					// Map the header pointer to the source file buffer
					InsydeFlash_Firmware_Header* header = (InsydeFlash_Firmware_Header*)(header_pointer);

					// Allocate the target file buffer
					unsigned long target_file_size = header->used_size;
					unsigned char* target_file_buffer = malloc(target_file_size);

					// Copy the UEFI Image to the target file buffer
					unsigned char* firmware_image_pointer = header_pointer + sizeof(InsydeFlash_Firmware_Header);
					memcpy(target_file_buffer, firmware_image_pointer, target_file_size);

					// Write the modified file
					FILE* destination_file = fopen(target_path, "wb");
					fwrite(target_file_buffer, 1, target_file_size, destination_file);

					// Free the file buffers
					free(target_file_buffer);
					free(source_file_buffer);
					
					// Close the file handles
					fclose(destination_file);
					fclose(source_file);
					
					return 0;
				}
				else
				{
					// Print error
					printf("InsydeFlash firmware signature not found in the file!\n");
					
					// Close the file handles
					fclose(source_file);

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
