#ifndef __CONN_H__
#define __CONN_H__

#define CONN_NAMELEN 32

typedef struct
{
	int (*connect)();
	int (*disconnect)();
	int (*rx)(uint8_t *buffer, int len);
	int (*tx)(uint8_t *buffer, int len);
	int id;
	char name[CONN_NAMELEN];
	interface *next;
} interface;

#define SUCCESS 0
#define NOT_IMPLEMENTED -1

#endif
