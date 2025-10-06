#include "bst.h"
#include "io.h"
#include "util.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LINE_MAX (WORD_MAX + DEF_MAX + 64)

static void print_help(void)
{
    puts(
        "Commands:\n"
        "  add <word>|<definition>  - Insert or update\n"
        "  find <word>              - Lookup definition\n"
        "  del <word>               - Delete a word\n"
        "  list                     - List all (alphabetical)\n"
        "  save <file.csv>          - Save to CSV\n"
        "  load <file.csv>          - Load from CSV (merge/update)\n"
        "  help                     - Show this help\n"
        "  quit                     - Exit\n");
}

int main(void)
{
    Node *root = NULL;
    char line[LINE_MAX];

    puts("BST Dictionary (C) — type 'help' for commands.");
    for (;;)
    {
        printf("> ");
        if (!fgets(line, sizeof line, stdin))
            break;
        trim_newline(line);
        char *p = trim_spaces(line);
        if (!*p)
            continue;

        if (strncmp(p, "add ", 4) == 0)
        {
            char *payload = p + 4;
            char *bar = strchr(payload, '|');
            if (!bar)
            {
                puts("Usage: add <word>|<definition>");
                continue;
            }
            *bar = '\0';
            char *w = trim_spaces(payload);
            char *d = trim_spaces(bar + 1);
            if (!*w || !*d)
            {
                puts("Both word and definition required.");
                continue;
            }
            root = bst_insert(root, w, d);
            printf("OK: added/updated '%s'\n", w);
        }
        else if (strncmp(p, "find ", 5) == 0)
        {
            char *w = trim_spaces(p + 5);
            if (!*w)
            {
                puts("Usage: find <word>");
                continue;
            }
            Node *n = bst_find(root, w);
            if (n)
                printf("%s: %s\n", n->word, n->def);
            else
                puts("Not found.");
        }
        else if (strncmp(p, "del ", 4) == 0)
        {
            char *w = trim_spaces(p + 4);
            if (!*w)
            {
                puts("Usage: del <word>");
                continue;
            }
            if (bst_find(root, w))
            {
                root = bst_delete(root, w);
                printf("Deleted '%s'\n", w);
            }
            else
            {
                puts("Not found.");
            }
        }
        else if (strcmp(p, "list") == 0)
        {
            if (!root)
                puts("(empty)");
            else
                bst_inorder(root);
        }
        else if (strncmp(p, "save ", 5) == 0)
        {
            char *path = trim_spaces(p + 5);
            if (!*path)
            {
                puts("Usage: save <file.csv>");
                continue;
            }
            if (bst_save_csv(root, path) == 0)
                printf("Saved to %s\n", path);
        }
        else if (strncmp(p, "load ", 5) == 0)
        {
            char *path = trim_spaces(p + 5);
            if (!*path)
            {
                puts("Usage: load <file.csv>");
                continue;
            }
            root = bst_load_csv(root, path);
            printf("Loaded from %s\n", path);
        }
        else if (strcmp(p, "help") == 0)
        {
            print_help();
        }
        else if (strcmp(p, "quit") == 0 || strcmp(p, "exit") == 0)
        {
            break;
        }
        else
        {
            puts("Unknown command. Type 'help'.");
        }
    }

    bst_free(root);
    return 0;
}
