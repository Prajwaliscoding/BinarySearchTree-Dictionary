#ifndef BST_H
#define BST_H

#include <stddef.h>

#define WORD_MAX 128
#define DEF_MAX 512

typedef struct Node
{
    char word[WORD_MAX];
    char def[DEF_MAX];
    struct Node *left, *right;
} Node;

/* Core BST operations (case-insensitive on 'word') */
Node *bst_insert(Node *root, const char *word, const char *def);
/* Returns pointer to node if found, else NULL */
Node *bst_find(Node *root, const char *word);
/* Deletes the node with given word (if present), returns (possibly new) root */
Node *bst_delete(Node *root, const char *word);
/* In-order traversal to stdout: "- word: definition" */
void bst_inorder(Node *root);
/* Free entire tree */
void bst_free(Node *root);

#endif /* BST_H */
