/*
 * This is free and unencumbered software released into the public domain.
 * 
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 * 
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * 
 * For more information, please refer to <http://unlicense.org>
 */
#ifndef STRBUFF_H_
#define STRBUFF_H_



#include <assert.h>
#include <ctype.h>


#include "../alloc.h"



#ifndef STRBUFF_PARTITION_SIZE
/**
 * @brief Size of strbuff memory blocks. Can be defined at compile time before including strbuff.h
 */
#	define STRBUFF_PARTITION_SIZE 32
#endif

struct strbuff_part {
	char data[STRBUFF_PARTITION_SIZE];
	struct strbuff_part *next;
};

/**
 * @brief strbuff is for recording a continuous string of characters.
 * 
 * You should use the sb_* functions to modify a strbuff.
 * The index functions (sb_setc, sb_getc) are slow compared to the rest.
 * 
 * 
 */
typedef struct strbuff {
	struct strbuff_part head; /**< Head of string chain. */
	struct strbuff_part *curr; /**< Current tail of chain. */
	int put_pos; /**< Position in @p curr to place next character. @see sb_putc */
} strbuff;



#ifdef __cplusplus
extern "C" {
#endif


void sb_init( strbuff *sb );
void sb_reset( strbuff *sb );
void sb_clear( strbuff *sb );
void sb_free( strbuff *sb );

int sb_len( strbuff *sb );

void sb_putc( strbuff *sb, const char ch );

void sb_setc( strbuff *sb, const int index, const char ch );
char sb_getc( strbuff *sb, const int index );

int sb_gets( strbuff *sb, char *dest, const int max_chars );
void sb_puts( strbuff *sb, const char *src, const int src_len );


void sb_cat( strbuff *sb, strbuff *cat );


char* sb_cstr( strbuff *sb );

void sb_strip_trailing( strbuff *sb );

int sb_get_next_line( strbuff *dest_buffer, const char *data, const int data_len, const int from_idx );



#ifdef __cplusplus
}
#endif


#endif
