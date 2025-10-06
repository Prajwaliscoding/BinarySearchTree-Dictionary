#ifndef IO_H
#define IO_H

#include "bst.h"

/* Save BST to CSV file: each line "word,definition" */
int bst_save_csv(Node *root, const char *path);
/* Load from CSV (merge/update): returns (possibly new) root */
Node *bst_load_csv(Node *root, const char *path);

#endif /* IO_H */
