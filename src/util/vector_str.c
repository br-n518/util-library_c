/* vector_str.c
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
#include "vector_str.h"


void vs_init( vector_str *s) {
	s->head = NULL;
}

vs_node* vs_node_create( const char c ) {
	vs_node *ret = _MALLOC( sizeof( vs_node ) );
	ret->data = c;
	ret->next = NULL;
	return ret;
}

void vs_node_free( vs_node *n ) {
	if ( n ) {
		if ( n->next ) {
			vs_node_free( n->next );
		}
		_FREE( n );
	}
}

void vs_destroy( vector_str *s ) {
	vs_node_free( s->head );
}

void vs_set( vector_str *s, const char *src ) {
	vs_node_free( s->head );
	s->head = NULL;
	int len = strlen( src );
	if ( len > 0 ) {
		s->head = vs_node_create( src[0] );
		vs_node *curr = s->head;
		int i = 0;
		while ( ++i < len ) {
			curr->next = vs_node_create( src[i] );
			curr = curr->next;
		}
	}
}

void vs_append( vector_str *s, const char *src ) {
	if ( s->head ) {
		vs_node *curr = s->head;
		while ( curr->next )
			curr = curr->next;
		int len = strlen(src);
		for ( int i = 0; i < len; i++ ) {
			curr->next = vs_node_create( src[i] );
			curr = curr->next;
		}
	} else {
		vs_set( s, src );
	}
}

void vs_insert( vector_str *s, const char *src, const int index ) {
	vs_node *a = s->head;
	
	if ( index > 0 ) {
		int i = 1;
	
		while ( i < index ) {
			if ( a->next ) {
				i++;
				a = a->next;
			} else {
				break;
			}
		}
		if ( i == index ) {
			vs_node *b = a->next;
			int si = 0;
			while ( src[si] ) {
				a->next = vs_node_create( src[si] );
				a = a->next;
				si++;
			}
			a->next = b;
		}
	} else {
		s->head = vs_node_create( src[0] );
		vs_node *b = a;
		a = s->head;
		int si = 1;
		while ( src[si] ) {
			a->next = vs_node_create( src[si] );
			a = a->next;
			si++;
		}
		a->next = b;
	}
}


char vs_char_at( vector_str *s, const int index ) {
	vs_node *curr = s->head;
	int i = 0;
	while ( i < index ) {
		if ( curr->next ) {
			curr = curr->next;
			i++;
		} else {
			// no next, index out of bounds
			return '\0';
		}
	}
	return curr->data;
}


int vs_index_of_c( vector_str *s, const char c ) {
	if ( s->head ) {
		vs_node *curr = s->head;
		int i = 0;
		while ( curr->data != c ) {
			if ( curr->next ) {
				curr = curr->next;
				i++;
			} else {
				return -1;
			}
		}
		return i;
	}
	return -1;
}

int vs_index_of_s( vector_str *s, const char *c ) {
	if ( s->head ) {
		vs_node *curr = s->head, *temp = NULL;
		int i = 0, ci = 0, clen = strlen(c);
		while ( curr ) {
			if ( curr->data == c[ci] ) {
				ci++;
			}
			if ( ci > 0 ) temp = curr->next;
			while ( temp ) {
				if ( temp->data == c[ci] ) {
					temp = temp->next;
					ci++;
					if ( ci == clen ) return i;
				} else {
					ci = 0;
					temp = NULL;
				}
			}
			i++;
			curr = curr->next;
		}
	}
	return -1;
}



int vs_index_of_c_idx( vector_str *s, const char c, const int index ) {
	if ( s->head ) {
		vs_node *curr = s->head;
		int i = 0;
		if ( !curr )
			return -1;
		while ( i < index ) {
			curr = curr->next;
			if ( !curr )
				return -1;
			i++;
		}
		while ( curr->data != c ) {
			if ( curr->next ) {
				curr = curr->next;
				i++;
			} else {
				return -1;
			}
		}
		return i;
	}
	return -1;
}


int vs_index_of_s_idx( vector_str *s, const char *c, const int index ) {
	if ( s->head ) {
		vs_node *curr = s->head, *temp = NULL;
		int i = 0, ci = 0, clen = strlen(c);
		if ( !curr )
			return -1;
		while ( i < index ) {
			curr = curr->next;
			if ( !curr )
				return -1;
			i++;
		}
		while ( curr ) {
			if ( curr->data == c[ci] ) {
				ci++;
			}
			if ( ci > 0 ) temp = curr->next;
			while ( temp ) {
				if ( temp->data == c[ci] ) {
					temp = temp->next;
					ci++;
					if ( ci == clen )
						return i;
				} else {
					ci = 0;
					temp = NULL;
				}
			}
			i++;
			curr = curr->next;
		}
	}
	return -1;
}



int vs_length( vector_str *s ) {
	vs_node *curr = s->head;
	int i = 0;
	while ( curr ) {
		i++;
		curr = curr->next;
	}
	return i;
}

char* vs_cstr( vector_str *s ) {
	char *ret = _MALLOC( vs_length( s ) + 1 );
	int i = 0;
	vs_node *curr = s->head;
	while ( curr ) {
		ret[i] = curr->data;
		curr = curr->next;
		i++;
	}
	ret[i] = '\0';
	return ret;
}



void vs_replace( vector_str *s, const char *from, const char *to ) {
	int flen = strlen( from );
	vs_node *curr = s->head, *prev = NULL;
	// search for 'from'
	while ( curr ) {
		if ( curr->data == from[0] ) {
			vs_node *check = curr;
			int i = 0;
			while ( ++i < flen ) {
				check = check->next;
				if ( !( check && check->data == from[i] ) ) {
					i = -1;
					break;
				}
			}
			// if all 'from' chars matched
			if ( i == flen ) {
				// store tail
				vs_node *tail = check->next;
				// allow free, without freeing tail.
				check->next = NULL;
				// done with check pointer
				check = NULL;
				// if curr is not head node
				if ( prev ) {
					// clear 'from' string
					vs_node_free( curr );
					curr = NULL;
					// set null for vs_append call
					prev->next = NULL;
					// append replacement text 'to'
					vs_append( s, to );
				} else {
					// curr is head node
					// just set whole string
					vs_set( s, to );
				}
				// apply tail
				if ( s->head ) {
					check = s->head;
					while ( check->next )
						check = check->next;
					check->next = tail;
				} else {
					s->head = tail;
				}
				// done processing
				return;
			}
		}
		prev = curr;
		curr = curr->next;
	}
}



void vs_replace_idx( vector_str *s, const char *from, const char *to, const int index ) {
	vs_node *curr = s->head, *prev = NULL, *check;
	
	if ( !curr )
		return;
	
	int flen = strlen( from );
	int i = 0;
	
	while ( i < index ) {
		curr = curr->next;
		if ( !curr )
			return;
		i++;
	}
	// search for 'from'
	while ( curr ) {
		if ( curr->data == from[0] ) {
			check = curr;
			i = 0;
			while ( ++i < flen ) {
				check = check->next;
				if ( !( check && check->data == from[i] ) ) {
					i = -1;
					break;
				}
			}
			// if all 'from' chars matched
			if ( i == flen ) {
				// store tail
				vs_node *tail = check->next;
				// allow free, without freeing tail.
				check->next = NULL;
				// done with check pointer
				check = NULL;
				// if curr is not head node
				if ( prev ) {
					// clear 'from' string
					vs_node_free( curr );
					curr = NULL;
					// set null for vs_append call
					prev->next = NULL;
					// append replacement text 'to'
					vs_append( s, to );
				} else {
					// curr is head node
					// just set whole string
					vs_set( s, to );
				}
				// apply tail
				if ( s->head ) {
					check = s->head;
					while ( check->next )
						check = check->next;
					check->next = tail;
				} else {
					s->head = tail;
				}
				// done processing
				return;
			}
		}
		prev = curr;
		curr = curr->next;
	}
}



int vs_test( vector_str *s, const char *cstr ) {
	char *p = vs_cstr( s );
	int ret = ( strcmp( p, cstr ) == 0 );
	_FREE( p );
	
	return ret;
	
}



