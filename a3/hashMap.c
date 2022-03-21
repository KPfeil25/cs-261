#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>
#include <assert.h>

int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
	return r;
}

void initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

void freeMap (struct hashMap * ht)
{
	int i;
	struct hashLink* t1;
	struct hashLink* t2;
	for (i = 0; i < ht->tableSize; i++) {
		t1 = ht->table[i];
		while(t1 != NULL) {
			t2 = t1->next;
			free(t1->key);
			free(t1);
			t1 = t2;
		}
	}
	free(ht->table);
	ht->table = 0;
	ht->tableSize = 0;
	ht->count = 0;
}

void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{
	int hash, hashidx;
	hashLink* newlnk;

	assert(ht && k);

	if (EQ(HASHING_FUNCTION, 1)) {
		hash = stringHash1(k);
	}
	else {
		hash = stringHash2(k);
	}
	hashidx = (ValueType) (labs(hash) % ht->tableSize);

	newlnk = (hashLink*)malloc(sizeof(hashLink));
	assert(newlnk);
	
	newlnk->key = (KeyType)malloc(sizeof(char*) * strlen(k) + 1);

	assert(newlnk->key);
	strcpy(newlnk->key, k);

	newlnk->value = v;

	newlnk->next =  ht->table[hashidx];
	ht->table[hashidx] = newlnk;

	ht->count++;

}

ValueType* atMap (struct hashMap * ht, KeyType k)
{

	int hash, hashidx;
	hashLink* curr;
	
	assert (ht && k);
	
	if (EQ(HASHING_FUNCTION, 1)) {
		hash = stringHash1(k);
	}
	else {
		hash = stringHash2(k);
	}
	hashidx = (ValueType)(labs(hash) % ht->tableSize);

	/* loop through the entire table to see if the value can be found. If not, return NULL */

	curr = ht->table[hashidx];
	while (curr) {
		if (EQ(strcmp(curr->key, k), 0)) {
			return &(curr->value);
		}
		else {
			curr = curr->next;
		}
	}
	return NULL;
}

int containsKey (struct hashMap * ht, KeyType k)
{ 
	if (atMap(ht, k) == 0) {
		return 0;
	}
	else {
		return 1;
	}
}

void removeKey (struct hashMap * ht, KeyType k)
{ 
	int bucket = stringHash2(k) % ht->tableSize;
	hashLink* curr;
	hashLink* prev;

	if (ht->table[bucket] == 0) {
		return;
	}
	else {
		curr = ht->table[bucket];
		prev = ht->table[bucket];
		while (curr != 0) {
			if (strcmp(curr->key, k) == 0) {
				if (curr == ht->table[bucket]) {
					ht->table[bucket] = curr->next;
				}
				else {
					prev->next = curr->next;
				}
				free(curr);
				ht->count--;
				return;
			}
			else {
				prev = curr;
				curr = curr->next;
			}
		}
	}

}

int sizeMap (struct hashMap *ht)
{
	return ht->count;
}

int capacityMap(struct hashMap *ht)
{
	return ht->tableSize;
}

int emptyBuckets(struct hashMap *ht)
{
	int buffer = 0;
	int i;
	for (i = 0; i < ht->tableSize; i++) {
		if (ht->table[i] == 0) {
			buffer++;
		}
		return buffer;
	}
}

float tableLoad(struct hashMap *ht)
{
	return (float)sizeMap(ht) / (float)capacityMap(ht);
}
