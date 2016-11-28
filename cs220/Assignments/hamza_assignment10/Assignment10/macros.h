//
//  macros.h
//  Assignments
//
//  Created by Moaz Hamza on 11/9/16.
//  Copyright © 2016 Moaz Hamza. All rights reserved.
//

#ifndef macros_h
#define macros_h
/* Helper macros */
#define BIT_MASK(len)  (BIT(len) - 1)
#define BF_MASK(start, len)  ( BIT_MASK(len) << (start) )
#define BIT(n) (1 << (n))
#define IS_SET_ANY(v, mask) (v & (mask))


/* Question 1 */
#define TEST_IF_ANY_SET(v, start, end) ( v & BF_MASK((start), (end)-(start-1)) )

#define TEST_IF_ALL_SET(v, start, end) ( !(TEST_IF_ANY_SET(v, start, end) \
                                        ^ (BF_MASK((start), ((end) - (start-1))))) )


#define COUNT_NUM_SET(v, start, end) ( __builtin_popcount(v & (BF_MASK((start), (end)-(start-1))) ))


#endif /* macros_h */
