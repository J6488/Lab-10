#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
	int count;
	struct trie* next[26];
};

// Inserts the word to the trie structure
struct Trie* createTrie();
void insert(struct Trie *pTrie, char *word)
{
	int i, k, n = strlen(word);
	struct Trie* temp = pTrie;
	for(k = 0; k < n; k++){
		i = word[k] - 'a';
		if(!temp->next[i]){
			temp->next[i] = createTrie();
		}
		temp = temp->next[i];
	}
	temp->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{	
	int i, k, n = strlen(word);
	struct Trie* temp = pTrie;
	for(k = 0; k < n; k++){
		i = word[k] - 'a';
		if(temp->next[i] == NULL){
			return 0;
		}
		temp = temp->next[i];
	}
	return temp->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
	int i;
	for(i = 0; i < 26; i++){
		if(pTrie->next[i] != NULL){
			deallocateTrie(pTrie->next[i]);
		}
	}
	free(pTrie);
	return pTrie;
}

// Initializes a trie structure
struct Trie *createTrie()
{
	int i;
	struct Trie* trie = (struct Trie*)malloc(sizeof(struct Trie));
	if(trie != NULL){
		trie->count = 0;
		for(i = 0; i < 26; i++){
			trie->next[i] = NULL;
		}
	}
	return trie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
	int i, n;
	FILE* f = fopen(filename, "r");
	fscanf(f, "%d", &n);
	for(i = 0; i < n; i++){
		pInWords[i] = malloc(sizeof(char) * 21);
		fscanf(f, "%s", pInWords[i]); 
	}
	fclose(f);
	return n;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}
