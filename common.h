// common.h -- Defines typedefs and some global functions.
//             From JamesM's kernel development tutorials.

#ifndef COMMON_H
#define COMMON_H

// Some nice typedefs, to standardise sizes across platforms.
// These typedefs are written for 32-bit X86.
typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;

typedef char* va_list;

#define va_start(ap, last_arg) ((void)((ap) = (va_list)&(last_arg) + sizeof(last_arg)))
#define va_arg(ap, type) (*(type*)((ap) += sizeof(type), (ap) - sizeof(type)))
#define va_end(ap) ((void)(ap = (va_list)0))

#define bool _Bool
#define true 1
#define false 0
#define __bool_true_false_are_defined 1

void outb(u16int port, u8int value);
u8int inb(u16int port);
u16int inw(u16int port);

#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

extern void panic(const char *message, const char *file, u32int line);
extern void panic_assert(const char *file, u32int line, const char *desc);

void memcpy(u8int *dest, const u8int *src, u32int len);
void memset(u8int *dest, u8int val, u32int len);
int strcmp(char *str1, char *str2);
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);
int strlen(char *src);


#endif // COMMON_H
