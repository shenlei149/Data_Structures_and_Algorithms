#ifndef INFRA_MEMORY_INCLUDED
#define INFRA_MEMORY_INCLUDED

#define InfraMemory_ALLOC(nbytes) InfraMemory_alloc((nbytes), __FILE__, __LINE__)
#define InfraMemory_CALLOC(count, nbytes) InfraMemory_calloc((count), (nbytes), __FILE__, __LINE__)
#define InfraMemory_RESIZE(ptr, nbytes) ((ptr) = InfraMemory_resize((ptr), (nbytes), __FILE__, __LINE__))
#define InfraMemory_FREE(ptr) ((void)(InfraMemory_free((ptr)), (ptr) = 0))

// allocates an uninitialized block to hold *p and sets p to theaddress of that block.
#define InfraMemory_NEW(p) ((p) = ALLOC((long)sizeof *(p)))

// same as NEW(p), but also clears the block.
#define InfraMemory_NEW0(p) ((p) = CALLOC(1, (long)sizeof *(p)))

extern void *InfraMemory_alloc(long nbytes, const char *file, int line);
extern void *InfraMemory_calloc(long count, long nbytes, const char *file, int line);
extern void *InfraMemory_resize(void *ptr, long nbytes, const char *file, int line);
extern void InfraMemory_free(void *ptr);

#endif
