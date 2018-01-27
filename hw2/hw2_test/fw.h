#ifndef FW_H
#define FW_H

struct hashmap_item {
	Hashmap_Item next;
	char *key;
	int frequency;
};

struct hashmap {
	Hashmap_Item * buckets;
	size_t size;
	size_t count;
};

#endif
