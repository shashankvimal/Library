#ifndef __UTILS_H__
#define __UTILS_H__

#define ASSERT(expression, message) !(expression) ? printf("%s line: %d, in file:%s \n", #message, __LINE__, __FILE__), exit(0) : (void)(0)

typedef unsigned char bool;

#endif /*END_OF___UTILS_H__*/
