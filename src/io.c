#include "io.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

/* Recursive save (in-order) */
static void save_csv_rec(Node *root, FILE *f)
{
    if (!root)
        return;
    save_csv_rec(root->left, f);

    /* sanitize newlines in fields */
    char w[WORD_MAX], d[DEF_MAX];
    safe_strcpy(w, root->word, WORD_MAX);
    safe_strcpy(d, root->def, DEF_MAX);
    for (char *p = w; *p; ++p)
        if (*p == '\n' || *p == '\r')
            *p = ' ';
    for (char *p = d; *p; ++p)
        if (*p == '\n' || *p == '\r')
            *p = ' ';

    /* NOTE: Simple CSV: split on first comma when reading.
       If you want to support commas in fields, you'd need proper CSV quoting. */
    fprintf(f, "%s,%s\n", w, d);

    save_csv_rec(root->right, f);
}

int bst_save_csv(Node *root, const char *path)
{
    FILE *f = fopen(path, "w");
    if (!f)
    {
        perror("fopen");
        return -1;
    }
    save_csv_rec(root, f);
    fclose(f);
    return 0;
}

Node *bst_load_csv(Node *root, const char *path)
{
    FILE *f = fopen(path, "r");
    if (!f)
    {
        perror("fopen");
        return root;
    }

    char line[WORD_MAX + DEF_MAX + 16];
    while (fgets(line, sizeof line, f))
    {
        trim_newline(line);
        char *comma = strchr(line, ',');
        if (!comma)
            continue;
        *comma = '\0';
        char *w = trim_spaces(line);
        char *d = trim_spaces(comma + 1);
        if (*w)
        {
            root = bst_insert(root, w, d);
        }
    }
    fclose(f);
    return root;
}