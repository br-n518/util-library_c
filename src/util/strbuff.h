/* strbuff.h
 *
 * Copyright (c) 2019 br-n518
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef STRBUFF_H_
#define STRBUFF_H_



#include <assert.h>
#include <ctype.h>
#include <stdlib.h>



#ifndef STRBUFF_PARTITION_SIZE
/**
 * @brief Size of strbuff memory blocks.
 * Can be defined at compile time before including strbuff.h .
 * 
 * 
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
	int put_pos; /**< Position in @p curr to place next character. @see sb_putc() */
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
