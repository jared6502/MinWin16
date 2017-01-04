#include "conn.h"

interface *start;

int default_connect()
{
	return SUCCESS;
}

int default_disconnect()
{
	return SUCCESS;
}

int default_rx(uint8_t *buffer, int len)
{
	return SUCCESS;
}

int default_tx(uint8_t *buffer, int len)
{
	return SUCCESS;
}

void load()
{
	start = 0;
}

void unload()
{
	if (start != 0)
	{
		interface *i;
		interface *n;
		
		i = start;
		
		do
		{
			n = i->next;
			free(i);
			i = n;
		} while (n != 0);
	}
}

interface *getlastinterface()
{
	interface *last = start;
	
	while (last != 0)
	{
		last = last->next;
	}
	
	return last;
}

interface *new_interface()
{
	interface *last;
	
	last = getlastinterface();
	
	if (last == 0)
	{
		last = malloc(sizeof(interface));
		start = last;
	}
	else
	{
		last->next = malloc(sizeof(interface));
		last = last->next;
	}
	
	if (last != 0)
	{
		last->connect = default_connect;
		last->disconnect = default_disconnect;
		last->rx = default_rx;
		last->tx = default_tx;
	}
	
	return last;
}

void *delete_interface(interface *del)
{
	//deleting the starting element
	if (del == start)
	{
		start = start->next;
		free(del);
		return;
	}
	
	interface *prv = start;
	
	//find the element before the one to be removed
	while (prv->next != del && prv->next != 0)
	{
		prv = prv->next;
	}
	
	//remove the link from the chain
	if (prv->next != 0)
	{
		prv->next = prv->next->next;
		free(del);
	}
}

