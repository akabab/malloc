#include "malloc.h"

extern t_region				*g_heap[3];
extern pthread_mutex_t		g_mutex;

void		free_exec(void *ptr)
{
	t_block		*b;
	t_region	*r;

	if (!ptr)
		return ;
	if ((r = get_valid_region(ptr)) != NULL)
	{
		b = get_block(ptr);
		b->is_free = TRUE;
		if (b->prev && b->prev->is_free)
			b = fusion_block(b->prev);
		if (b->next && b->next->is_free)
			fusion_block(b);
		if (!b->next && !b->prev)
		{
			if (r->type == LARGE || (r->prev || r->next))
				free_region(r);
		}
	}
}

void		free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	free_exec(ptr);
	pthread_mutex_unlock(&g_mutex);
}
