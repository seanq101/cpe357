#ifndef FW_H
#define FW_H

struct map_element {
	map_element * next;
	char *key;
	int frequency;
};

struct map_table {
	map_element ** buckets;
	int map_size;
	int used_size;
};

#endif
