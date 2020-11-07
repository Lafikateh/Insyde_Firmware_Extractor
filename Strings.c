// C Standard Library Headers
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Program Headers
#include "Strings.h"

// Duplicate an string
// Returns char* on success, or NULL on failure
char* c_duplicate_string_c(const char* text)
{
	// Check if the text pointer is valid
	if (text != NULL)
	{
		// Get length and allocate the new string
		int new_text_size = strlen(text) + 1;
		char* new_text = malloc(new_text_size);

		// Copy the string to the new string
		strcpy(new_text, text);

		// Return the duplicated string
		return new_text;
	}
	else
	{
		// Return NULL
		return NULL;
	}
}

// Create an string using an existing const char* string
// Returns string* on success, or NULL on failure
string* create_string(const char* text)
{
	// Check if the text pointer is valid
	if (text != NULL)
	{
		// Determine the string's length including the terminating character using the strlen function
		unsigned int string_length = strlen(text) + 1;

		// Allocate and fill the string structure
		string* new_string = malloc(sizeof(string));
		new_string->length = string_length;
		new_string->data = malloc(string_length);

		// Copy the existing string's data to the string structure
		strcpy(new_string->data, text);

		// Return an pointer to the string structure
		return new_string;
	}
	else
	{
		// Return NULL
		return NULL;
	}
}

// Free an string
// Returns true on success, or false on failure
bool free_string(string* string_handle)
{
	if (string_handle != NULL)
	{
		// Free the string's memory and structure
		free(string_handle->data);
		free(string_handle);

		// Return true
		return true;
	}
	else
	{
		// Return false
		return false;
	}
}

// Append an string to the string
// Returns string* on success, or NULL on failure
string* append_string(string* existing_string, string* new_string)
{
	if (existing_string != NULL && new_string != NULL)
	{
		// Get both string's length
		unsigned int existing_string_length = strlen(existing_string->data);
		unsigned int new_string_length = strlen(new_string->data);

		// Calculate appended string length
		unsigned int appended_string_length = existing_string_length + new_string_length + 1;

		// Reallocate the existing string to an larger buffer
		existing_string->data = realloc(existing_string->data, appended_string_length);

		// Append the new string
		strcat(existing_string->data, new_string->data);

		// Update the string length
		existing_string->length = appended_string_length - 1;

		// Return the appended string
		return existing_string;
	}
	else
	{
		// Return NULL
		return NULL;
	}
}

// Append an string to the string
// Returns string* on success, or NULL on failure
string* append_string_c(string* existing_string, const char* new_string)
{
	if (existing_string != NULL && new_string != NULL)
	{
		// Get both string's length
		unsigned int existing_string_length = strlen(existing_string->data);
		unsigned int new_string_length = strlen(new_string);

		// Calculate appended string length
		unsigned int appended_string_length = existing_string_length + new_string_length + 1;

		// Reallocate the existing string to an larger buffer
		existing_string->data = realloc(existing_string->data, appended_string_length);

		// Append the new string
		strcat(existing_string->data, new_string);

		// Update the string length
		existing_string->length = appended_string_length - 1;

		// Return the appended string
		return existing_string;
	}
	else
	{
		// Return NULL
		return NULL;
	}
}

// Append an string to the string
// Returns char* on success, or NULL on failure
char* c_append_string_c(char* existing_string, const char* new_string)
{
	if (existing_string != NULL && new_string != NULL)
	{
		// Get both string's length
		unsigned int existing_string_length = strlen(existing_string);
		unsigned int new_string_length = strlen(new_string);

		// Calculate appended string length
		unsigned int appended_string_length = existing_string_length + new_string_length + 1;

		// Reallocate the existing string to an larger buffer
		existing_string = realloc(existing_string, appended_string_length);

		// Append the new string
		strcat(existing_string, new_string);

		// Return the appended string
		return existing_string;
	}
	else
	{
		// Return NULL
		return NULL;
	}
}

// Replace an source string with the replacement string
// Returns string* on success, or NULL on failure
string* replace_string(string* string_handle, const string* source_string, const string* replacement_string)
{
	// Check if the string pointers are valid
	if (string_handle != NULL && source_string != NULL && replacement_string != NULL)
	{
		// Check if the string data pointers are valid
		if (string_handle->data != NULL && source_string->data != NULL && replacement_string->data != NULL)
		{
			char* old_text = string_handle->data;
			char* new_text = NULL;
			char* temp_text = NULL;
			int search_size = strlen(source_string->data);

			// Count occurences
			int occurence_count = 0;
			for (temp_text = strstr(string_handle->data, source_string->data); temp_text != NULL; temp_text = strstr(temp_text + search_size, source_string->data))
			{
				occurence_count++;
			}

			// Check occurence count
			if (occurence_count > 0)
			{
				// Calculate final length including the terminating character
				int final_length = (strlen(replacement_string->data) - search_size) * occurence_count + strlen(string_handle->data) + 1;

				// Allocate and zero-fill the new text
				new_text = calloc(final_length, sizeof(char));

				// Clear the new text
				strcpy(new_text, "");

				// Replace every occurence of source_string with replace_string
				for (temp_text = strstr(string_handle->data, source_string->data); temp_text != NULL; temp_text = strstr(temp_text + search_size, source_string->data))
				{
					// Copy the regular text
					strncpy(new_text + strlen(new_text), old_text, temp_text - old_text);

					// Copy the replacement text
					strcpy(new_text + strlen(new_text), replacement_string->data);

					// Calculate the starting position after the search match
					old_text = temp_text + search_size;
				}

				// Copy the remaining part
				strcpy(new_text + strlen(new_text), old_text);

				// Free the old data buffer and fill the structure with new values
				free(string_handle->data);
				string_handle->data = new_text;
				string_handle->length = final_length;

				// Return the modified string pointer
				return string_handle;
			}
			else
			{
				// Return the non-modified string pointer
				return string_handle;
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
		return NULL;
	}
}

// Replace an source string with the replacement string
// Returns string* on success, or NULL on failure
string* replace_string_c(string* string_handle, const char* source_string, const char* replacement_string)
{
	// Check if the string pointers are valid
	if (string_handle != NULL && source_string != NULL && replacement_string != NULL)
	{
		// Check if the string data pointers are valid
		if (string_handle->data != NULL && source_string != NULL && replacement_string != NULL)
		{
			char* old_text = string_handle->data;
			char* new_text = NULL;
			char* temp_text = NULL;
			int search_size = strlen(source_string);

			// Count occurences
			int occurence_count = 0;
			for (temp_text = strstr(string_handle->data, source_string); temp_text != NULL; temp_text = strstr(temp_text + search_size, source_string))
			{
				occurence_count++;
			}

			// Check occurence count
			if (occurence_count > 0)
			{
				// Calculate final length including the terminating character
				int final_length = (strlen(replacement_string) - search_size) * occurence_count + strlen(string_handle->data) + 1;

				// Allocate and zero-fill the new text
				new_text = calloc(final_length, sizeof(char));

				// Clear the new text
				strcpy(new_text, "");

				// Replace every occurence of source_string with replace_string
				for (temp_text = strstr(string_handle->data, source_string); temp_text != NULL; temp_text = strstr(temp_text + search_size, source_string))
				{
					// Copy the regular text
					strncpy(new_text + strlen(new_text), old_text, temp_text - old_text);

					// Copy the replacement text
					strcpy(new_text + strlen(new_text), replacement_string);

					// Calculate the starting position after the search match
					old_text = temp_text + search_size;
				}

				// Copy the remaining part
				strcpy(new_text + strlen(new_text), old_text);

				// Free the old data buffer and fill the structure with new values
				free(string_handle->data);
				string_handle->data = new_text;
				string_handle->length = final_length;

				// Return the modified string pointer
				return string_handle;
			}
			else
			{
				// Return the non-modified string pointer
				return string_handle;
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
		return NULL;
	}
}

// Replace an source string with the replacement string
// Returns char* on success, or NULL on failure
char* c_replace_string_c(char* string_handle, const char* source_string, const char* replacement_string)
{
	// Check if the string pointers are valid
	if (string_handle != NULL && source_string != NULL && replacement_string != NULL)
	{
		char* old_text = string_handle;
		char* new_text = NULL;
		char* temp_text = NULL;
		int search_size = strlen(source_string);

		// Count occurences
		int occurence_count = 0;
		for (temp_text = strstr(string_handle, source_string); temp_text != NULL; temp_text = strstr(temp_text + search_size, source_string))
		{
			occurence_count++;
		}

		// Check occurence count
		if (occurence_count > 0)
		{
			// Calculate final length including the terminating character
			int final_length = (strlen(replacement_string) - search_size) * occurence_count + strlen(string_handle) + 1;

			// Allocate and zero-fill the new text
			new_text = calloc(final_length, sizeof(char));

			// Clear the new text
			strcpy(new_text, "");

			// Replace every occurence of source_string with replace_string
			for (temp_text = strstr(string_handle, source_string); temp_text != NULL; temp_text = strstr(temp_text + search_size, source_string))
			{
				// Copy the regular text
				strncpy(new_text + strlen(new_text), old_text, temp_text - old_text);

				// Copy the replacement text
				strcpy(new_text + strlen(new_text), replacement_string);

				// Calculate the starting position after the search match
				old_text = temp_text + search_size;
			}

			// Copy the remaining part
			strcpy(new_text + strlen(new_text), old_text);

			// Return the modified string pointer
			return new_text;
		}
		else
		{
			// Return the non-modified string pointer
			return string_handle;
		}
	}
	else
	{
		// Return NULL
		return NULL;
	}
}
