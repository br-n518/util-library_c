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
#ifndef XML_DOC_H
#define XML_DOC_H

#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#include "../alloc.h"

#include "node.h"
#include "hash.h"
#include "strbuff.h"

/**
 * @brief Max length for XML node names, attribute names, encoding string, and XML filename.
 */
#define XML_STRING_BUFFER_SIZE 256
/**
 * @brief Max length for XML attribute values.
 */
#define XML_LARGE_STRING_BUFFER_SIZE 2048
/**
 * @brief Connect child nodes to parent node in xml_node_free.
 * @see xml_node_free
 */
#define XML_NODE_CONNECT_CHILDREN 1
/**
 * @brief Delete all child nodes recursively then free the given node in xml_node_free.
 * @see xml_node_free
 */
#define XML_NODE_DELETE_CHILDREN 0

// NOTE: Comments are ignored and don't get handled.
// Tags are automatically condensed when a node has no children and no text body.



/**
 * @brief Represents an XML text element. This object isn't allocated, but used to store an allocated string.
 * @see create_xml_text
 * @see free_xml_text
 * @warning The other xml_* structs behave differently from xml_text, because xml_text is referenced by data, not pointer.
 * 
 */
struct xml_text {
	char *text; /**< Character string representing text. */
	size_t text_len; /**< Length of character string. */
};
/**
 * @brief Represents an XML attribute element.
 * @see xml_attribute_create
 * @see xml_attribute_free
 * 
 */
struct xml_attribute {
	char name[XML_STRING_BUFFER_SIZE]; /**< Attribute name (left of equals sign) */
	struct xml_text text_body; /**< Attribute value (right of equals sign; double-quoted) */
};
/**
 * @brief Represents an XML node element.
 * @see xml_node_create
 * @see xml_node_free
 * @see xml_doc
 * 
 */
struct xml_node {
	struct xml_node *parent_node; /**< Parent node (root node has no parent) */
	node_t *child_nodes; /**< Linear linked list of child nodes (stored as void* cast as @struct xml_node) */
	struct xml_text text_body; /**< Optional text body for XML node. */
	char name[XML_STRING_BUFFER_SIZE]; /**< XML node tagname. E.g. name "asdf" -> <asdf>...</asdf> */
	hash_table attributes; /**< Node attributes are stored in a hash table. Retrieved in arbitrary order. */
};
/**
 * @brief Represents an XML document.
 * @see xml_doc_create
 * @see xml_doc_free
 * 
 */
struct xml_doc {
	char encoding[XML_STRING_BUFFER_SIZE]; /**< Encoding attribute for XML header (defaults to "UTF-8" */
	char version_major, version_minor; /**< XML version major (the 1 in 1.0) */ /**< XML version minor (the 0 in 1.0) */
	struct xml_node *root_node; /**< Root node of XML tree. */
};



#ifdef __cplusplus
extern "C" {
#endif

// return 1 for matching filename extension ( ".xml", or ".XML", or ".xMl" etc: case-insensitive )
char xml_check_filename( const char *fname, const int len );

struct xml_doc*       xml_doc_create       ();
struct xml_node*      xml_node_create      ( const char *name ); // strings are copied
struct xml_attribute* xml_attribute_create ( const char *name, const char *value );

void xml_text_create ( struct xml_text *t, const char *value );
void xml_text_append ( struct xml_text *t, const char *value );

void xml_text_free      ( struct xml_text* );
void xml_attribute_free ( struct xml_attribute* );
void xml_node_free      ( struct xml_node*, const char connect_children ); //connect_children as 0 will delete child nodes recursively.
void xml_doc_free       ( struct xml_doc* );

// open XML file
struct xml_doc* xml_doc_open( const char *fname, const char strict_formatting_bool );
struct xml_doc* xml_doc_parse( const char *x_data, const size_t x_data_len, const char strict_formatting_bool );

// save XML file
void xml_doc_save            ( struct xml_doc *doc, const char *fname );
void xml_doc_save_sans_prolog( struct xml_doc *doc, const char *fname );

// attributes must live in a node, so no xml_attribute functions
void xml_node_set_attr  ( struct xml_node*, const char *name, const char *value );
void xml_node_apply_attr( struct xml_node*, struct xml_attribute* );

struct xml_attribute* xml_node_get_attr      ( struct xml_node*, const char *name );
struct xml_text*      xml_node_get_attr_value( struct xml_node*, const char *name );

void xml_node_add_child      ( struct xml_node*, struct xml_node* );
void xml_node_insert_child_at( struct xml_node*, struct xml_node*, int idx );


void xml_node_set_text   ( struct xml_node *node, const char *new_text );
void xml_node_append_text( struct xml_node *node, const char *text );

char* xml_doc_to_string( struct xml_doc *doc, const char include_prolog );




#ifdef __cplusplus
}
#endif

#endif
