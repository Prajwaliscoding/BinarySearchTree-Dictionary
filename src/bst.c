#include "bst.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Node *new_node(const char *w, const char *d)
{
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n)
    {
        perror("malloc");
        exit(1);
    }
    safe_strcpy(n->word, w, WORD_MAX);
    safe_strcpy(n->def, d, DEF_MAX);
    n->left = n->right = NULL;
    return n;
}

Node *bst_insert(Node *root, const char *w, const char *d)
{
    if (!root)
        return new_node(w, d);
    int cmp = stricmp(w, root->word);
    if (cmp == 0)
    {
        /* Update definition if word exists */
        safe_strcpy(root->def, d, DEF_MAX);
    }
    else if (cmp < 0)
    {
        root->left = bst_insert(root->left, w, d);
    }
    else
    {
        root->right = bst_insert(root->right, w, d);
    }
    return root;
}

Node *bst_find(Node *root, const char *w)
{
    while (root)
    {
        int cmp = stricmp(w, root->word);
        if (cmp == 0)
            return root;
        root = (cmp < 0) ? root->left : root->right;
    }
    return NULL;
}

static Node *bst_min(Node *root)
{
    while (root && root->left)
        root = root->left;
    return root;
}

Node *bst_delete(Node *root, const char *w)
{
    if (!root)
        return NULL;
    int cmp = stricmp(w, root->word);

    if (cmp < 0)
    {
        root->left = bst_delete(root->left, w);
    }
    else if (cmp > 0)
    {
        root->right = bst_delete(root->right, w);
    }
    else
    {
        /* Found node */
        if (!root->left)
        {
            Node *r = root->right;
            free(root);
            return r;
        }
        else if (!root->right)
        {
            Node *l = root->left;
            free(root);
            return l;
        }
        else
        {
            /* Two children: replace with inorder successor */
            Node *m = bst_min(root->right);
            safe_strcpy(root->word, m->word, WORD_MAX);
            safe_strcpy(root->def, m->def, DEF_MAX);
            root->right = bst_delete(root->right, m->word);
        }
    }
    return root;
}

void bst_inorder(Node *root)
{
    if (!root)
        return;
    bst_inorder(root->left);
    printf("- %s: %s\n", root->word, root->def);
    bst_inorder(root->right);
}

void bst_free(Node *root)
{
    if (!root)
        return;
    bst_free(root->left);
    bst_free(root->right);
    free(root);
}
