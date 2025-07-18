// Marvin Orozoc
// Assignment 6: Name Game
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 26
#define OFFSET 'A'
typedef struct TrieNode TrieNode;
struct TrieNode
{
	TrieNode *children[SIZE];
	int nodeTotal;
	int subtreeSum;
};
// Function prototypes for Tries
TrieNode *createNode();
TrieNode *insert(TrieNode *root, char *name, int amnt);
int contains(TrieNode *root, char *oldName);
int subtreeSumGet(TrieNode *root, char *str);
void cleanTrie(TrieNode *root);
int main()
{
	int n, e, event, amnt; // variables that will be used
	// initializes the trie
	TrieNode *root = NULL;
	// dynamic memory allocation for strings
	char *name = (char *)malloc(21 * sizeof(char));
	char *oldName = (char *)malloc(21 * sizeof(char));
	// gets the values of numbers of monkeys and events
	scanf("%d %d", &n, &e);
	for (int i = 0; i < e; i++)
	{
		scanf("%d", &event);
		// scans for a string and number of mangoes and inserts into Trie
		if (event == 1)
		{
			scanf("%s", name);
			scanf("%d", &amnt);
			root = insert(root, name, amnt);
		}
		// scans two string the first one being the old name and second the new
		name if (event == 2)
		{
			scanf("%s %s", oldName, name);
			int oldNameamnt = contains(root, oldName);
			insert(root, oldName, -1 * oldNameamnt);
			insert(root, name, oldNameamnt);
		}
		// scans for a string and retrieves the subtreeSum of that string
		if (event == 3)
		{
			int total;
			// scans string and finds the subtreeTotal of it
			scanf("%s", name);
			total = subtreeSumGet(root, name);
			printf("%d\n", total);
		}
	}
	// freeing of all memory dynamically allocated
	cleanTrie(root);
	free(name);
	free(oldName);
	return 0;
}
// creates a node in the Trie
TrieNode *createNode()
{
	TrieNode *result = (TrieNode *)malloc(sizeof(TrieNode));
	result->nodeTotal = 0;
	result->subtreeSum = 0;
	for (int i = 0; i < SIZE; i++)
	{
		result->children[i] = NULL;
	}
	return result;
}
// inserts nodes with each index of the string and stores mangos
TrieNode *insert(TrieNode *root, char *name, int amnt)
{
	// The trie was empty
	if (root == NULL)
	{
		root = createNode();
	}
	root->subtreeSum += amnt; // adds the nodeTotal to each nodes subtreeSum that it passes through
		// Check if the code is empty
		if (name[0] == '\0')
	{
		root->nodeTotal += amnt; // if code is empty the nodeTotal is set to
		scanned value
	}
	else
	{
		// recursive call to iterate through each index of the string and
create nodes for each
root->children[name[0] - OFFSET] = insert(root->children[name[0] -
OFFSET], name + 1, amnt);
	}
	return root;
}
// Finds the Node and gets the nodeTotal variable from it
int contains(TrieNode *root, char *oldName)
{
	if (root == NULL)
		return 0;
	if (oldName[0] == '\0')
		return root->nodeTotal; // returns the corresponding nodeTotal of string
		// recursive call to iterate through string until base case
		return contains(root->children[oldName[0] - OFFSET], oldName + 1);
}
// same as contains() but with subtreeSum instead
int subtreeSumGet(TrieNode *root, char *str)
{
	if (root == NULL)
		return 0;
	if (str[0] == '\0')
		return root->subtreeSum;
	return subtreeSumGet(root->children[str[0] - OFFSET], str + 1);
}
// deletes and frees the memory from the Trie
void cleanTrie(TrieNode *root)
{
	if (root == NULL)
		return;
	for (int i = 0; i < SIZE; i++)
		cleanTrie(root->children[i]);
	free(root);
}