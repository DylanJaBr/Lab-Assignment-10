#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the trie node structure
struct Trie {
    struct Trie *children[26];
    int count;
};//end Trie

// Insert a word into the trie
void insert(struct Trie **ppTrie, char *word) {

    // If the trie doesn't exist, create a new node
    if (*ppTrie == NULL) {
        *ppTrie = malloc(sizeof(struct Trie));
        memset((*ppTrie)->children, 0, sizeof((*ppTrie)->children));
        (*ppTrie)->count = 0;
    }//end if

    struct Trie *pTrie = *ppTrie;
    // Traverse the trie to the appropriate node for the word
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (pTrie->children[index] == NULL) {
            pTrie->children[index] = malloc(sizeof(struct Trie));
            memset(pTrie->children[index]->children, 0, sizeof(pTrie->children[index]->children));
            pTrie->children[index]->count = 0;
        }//end if

        pTrie = pTrie->children[index];
    }//end for
    // Increment the count for the final node of the word
    pTrie->count++;
}//end insert

// Find the number of occurrences of a word in the trie
int numberOfOccurances(struct Trie *pTrie, char *word) {

    // Traverse the trie to the appropriate node for the word
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (pTrie->children[index] == NULL) {
            return 0;
        }//end if

        pTrie = pTrie->children[index];
    }//end for
    // Return the count for the final node of the word
    
    return pTrie->count;
}//end numberofoccurances

// Deallocate the trie and all of its nodes
struct Trie *deallocateTrie(struct Trie *pTrie) {

    if (pTrie != NULL) {
        for (int i = 0; i < 26; i++) {
            if (pTrie->children[i] != NULL) {
                deallocateTrie(pTrie->children[i]);
            }//end if
        }//end ofr

        free(pTrie);
    }//end if

    return NULL;
}//end deallocateTrie

int main(void) {
    // Read the number of words in the dictionary
    int n;
    scanf("%d", &n);

    // Parse each word and insert it into the trie
    struct Trie *trie = NULL;
    char word[101];
    for (int i = 0; i < n; i++) {
        scanf("%s", word);
        insert(&trie, word);
    }//end for

    // Check the number of occurrences of each word in the trie
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }//end for

    // Deallocate the trie and check for errors
    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }//end if

    // Return 0 to indicate successful program execution
    return 0;
}//end main
