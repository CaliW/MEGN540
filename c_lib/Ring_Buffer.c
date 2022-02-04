#include "Ring_Buffer.h"

// define constant masks for use later based on length chosen
// these are global scope only to this c file
const uint8_t RB_MASK_F = RB_LENGTH_F-1;
const uint8_t RB_MASK_C = RB_LENGTH_C-1; 


/* Initialization */
void rb_initialize_F( struct Ring_Buffer_F* p_buf )
{
    // set start and end indicies to 0
    // no point changing data
    p_buf->start_index = 0;
    p_buf->end_index = 0;
}

void rb_initialize_C( struct Ring_Buffer_C* p_buf )
{
    // set start and end indicies to 0
    // no point changing data
    
    // your code here!
    p_buf->start_index = 0;
    p_buf->end_index = 0;
}


/* Return active Length of Buffer */
uint8_t rb_length_F( const struct Ring_Buffer_F* p_buf)
{
    // calculate the active length using the mask and 2's complement to help
    // verify for your self why this works!
    uint8_t length = (p_buf->end_index - p_buf->start_index) & RB_MASK_F;
    return length;
}
uint8_t rb_length_C( const struct Ring_Buffer_C* p_buf)
{
    // your code here!
    // make sure to use the correct mask!
    uint8_t length = (p_buf->end_index - p_buf->start_index) & RB_MASK_C;
    return length;
}

/* Append element to end and lengthen */
void rb_push_back_F( struct Ring_Buffer_F* p_buf, float value)
{   
    // Put data at index end
    p_buf->buffer[p_buf->end_index] = value;
    // Increment the end index and wrap using the mask.
    p_buf->end_index ++;
    p_buf->end_index = p_buf->end_index & RB_MASK_F;
    // If the end equals the start increment the start index`
    if (p_buf->end_index == p_buf->start_index)
        p_buf->start_index ++;
        p_buf->start_index = p_buf->start_index & RB_MASK_F;
}
void rb_push_back_C( struct Ring_Buffer_C* p_buf, char value)
{
    // Put data at index end
    p_buf->buffer[p_buf->end_index] = value;
    // Increment the end index and wrap using the mask.
    p_buf->end_index ++;
    p_buf->end_index = p_buf->end_index & RB_MASK_C;
    // If the end equals the start increment the start index`
    if (p_buf->end_index == p_buf->start_index)
        p_buf->start_index ++;
        p_buf->start_index = p_buf->start_index & RB_MASK_C;
}

/* Append element to front and lengthen */
void rb_push_front_F( struct Ring_Buffer_F* p_buf, float value)
{
    // Decrement the start index and wrap using the mask.
    p_buf->start_index --;
    p_buf->start_index = (p_buf->start_index & RB_MASK_F);
    // If the end equals the start, decrement the end index`
    if (p_buf->end_index == p_buf->start_index)
    {
        p_buf->end_index --;
        p_buf->end_index = (p_buf->end_index & RB_MASK_F);
    }
        //(p_buf->end_index --) & RB_MASK_F; //shorthand?
    // Set the value at the start index as desired.
    p_buf->buffer[p_buf->start_index] = value;
}
void rb_push_front_C( struct Ring_Buffer_C* p_buf, char value)
{
    // Decrement the start index and wrap using the mask.
    p_buf->start_index --;
    p_buf->start_index = (p_buf->start_index & RB_MASK_C);
    // If the end equals the start decrement the end index`
    if (p_buf->end_index == p_buf->start_index)
    {
        p_buf->end_index --;
        p_buf->end_index = (p_buf->end_index & RB_MASK_C);
    }
    // Set the value at the start index as desired.
    p_buf->buffer[p_buf->start_index] = value;
}

/* Remove element from end and shorten */
float rb_pop_back_F( struct Ring_Buffer_F* p_buf)
{
    // if end does not equal start (length zero),
    if (p_buf->end_index != p_buf->start_index) //aka if ring buffer length != 0, can't reduce nothing
    {    
        //reduce end index by 1 and mask
        p_buf->end_index --;
        p_buf->end_index = p_buf->end_index & RB_MASK_F; // () needed?
        //return value at at end
        return p_buf->buffer[p_buf->end_index];
    }
    // else return zero if length of list is zero
    else //else buffer length = 0
        return 0;
}
char  rb_pop_back_C( struct Ring_Buffer_C* p_buf)
{
    // if end does not equal start (length zero),
    //    reduce end index by 1 and mask
    // 	  return value at at end
    // else return zero if length of list is zero
    if (p_buf->end_index != p_buf->start_index) //aka if ring buffer length != 0, can't reduce nothing
    {
        p_buf->end_index --;
        p_buf->end_index = p_buf->end_index & RB_MASK_C; // () needed?
        return p_buf->buffer[p_buf->end_index];
    }
    else
        return 0;
}

/* Remove element from start and shorten */
float rb_pop_front_F( struct Ring_Buffer_F* p_buf)
{
    // get value to return at front
    float return_val = p_buf->buffer[p_buf->start_index];
    // if end does not equal start (length zero),
    //    increase start index by 1 and mask
    if (p_buf->end_index != p_buf->start_index)
    {
        //uint8_t return_val = p_buf->buffer[p_buf->start_index]; //can be here or at top
        p_buf->start_index ++;
        p_buf->start_index = p_buf->start_index & RB_MASK_F;
        return return_val;
    }
    // else return zero if length of list is zero
    else //if start_index = end_index, length = 0
        return 0;
}
char  rb_pop_front_C( struct Ring_Buffer_C* p_buf)
{
    // get value to return at front
    // if end does not equal start (length zero),
    //    increase start index by 1 and mask
    // else return zero if length of list is zero
    // return value
    float return_val = p_buf->buffer[p_buf->start_index];
    if (p_buf->end_index != p_buf->start_index)
    {
        p_buf->start_index ++;
        p_buf->start_index = p_buf->start_index & RB_MASK_C;
        return return_val;
    }
    else 
        return 0;
}

/* access element */
float rb_get_F( const struct Ring_Buffer_F* p_buf, uint8_t index)
{
    // return value at start + index wrapped properly
    uint8_t rb_index = p_buf->start_index + index;
    rb_index = rb_index & RB_MASK_F;
    return p_buf->buffer[rb_index];
}
char  rb_get_C( const struct Ring_Buffer_C* p_buf, uint8_t index)
{
    uint8_t rb_index = p_buf->start_index + index;
    rb_index = rb_index & RB_MASK_C;
    return p_buf->buffer[rb_index];
}

/* set element - This behavior is 
   poorly defined if inedex is outside of active length.
   Use of the push_back or push_front methods are prefered.
*/
void  rb_set_F( struct Ring_Buffer_F* p_buf, uint8_t index, float value)
{
    // set value at start + index wrapped properly
    uint8_t rb_index = p_buf->start_index + index;
    rb_index = rb_index & RB_MASK_F;
    p_buf->buffer[rb_index] = value;
}
void  rb_set_C( struct Ring_Buffer_C* p_buf, uint8_t index, char value)
{
    // set value at start + index wrapped properly
    uint8_t rb_index = p_buf->start_index + index;
    rb_index = rb_index & RB_MASK_C;
    p_buf->buffer[rb_index] = value;
}

