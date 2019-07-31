#ifndef __MEM_ALLOC_H__
#define __MEM_ALLOC_H__

#define MALLOC(type, placeHolder, size)\
if(((placeHolder) = (type*)malloc((size))) == NULL)\
{\
    fprintf(stderr, "Dynamic memory allocation(malloc) failed at: %s, %s", __FILE__, __LINE__);\
    exit(EXIT_FAILURE);\
}

#define CALLOC(type, placeHolder, nBlock, blockSize)\
if(((placeHolder) = (type)calloc((nBlock),(blockSize))) == NULL)\
{\
    fprintf(stderr, "Dynamic memory allocation(calloc) failed at: %s, %s", __FILE__, __LINE__);\
    exit(EXIT_FAILURE);\
}

#define REALLOC(type, placeHolder, size)\
if(((placeHolder) = (type)realloc((size))) == NULL)\
{\
    fprintf(stderr, "Dynamic memory allocation(realloc) failed at: %s, %s", __FILE__, __LINE__);\
    exit(EXIT_FAILURE);\
}

#endif /*EO_MEM_ALLOC_H*/
