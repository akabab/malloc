#include <unistd.h>
#include <sys/mman.h>

int main () 
{
	char	*p;
	
	p = (char *)mmap(0, 400 * getpagesize(), PROT_READ | PROT_WRITE, MAP_ANON| MAP_PRIVATE,-1,0);
	int i = 0;
	while (i < 1024) {
		p[0] = 42;
		p += 1024;
		i++;
	}
	return (0);
}
