#include "../inc/tree.h"
#include "../inc/structs.h"
#include <ctype.h>

void printBT(char *prefix, const node_t *node, bool isLeft)
{
    if (node != NULL)
    {
        printf("%s", prefix);
        if (isLeft && node->parent->right != NULL)
            printf("%s", blue "├──L" res);
        else if (isLeft)
            printf("%s", blue "└──L" res);
        else
            printf("%s", blue "└──R" res);

        printf("(%s, %d, %d)\n", node->word, node->key, node->height);

        char temp_prefix[1000] = "";
        strcat(temp_prefix, prefix);
        if (isLeft && node->parent->right != NULL)
            strcat(temp_prefix, blue "│   " res);
        else
            strcat(temp_prefix, "    ");

        printBT(temp_prefix, node->left, true);
        printBT(temp_prefix, node->right, false);
    }
}

node_t *create(node_t *root, int key, char *str)
{
    node_t *tmp = malloc(sizeof(node_t));
    tmp->key = key;
    strcpy(tmp->word, str);
    tmp->parent = NULL;
    tmp->left = tmp->right = NULL;
    root = tmp;
    return root;
}

node_t *add(node_t *root, char *str, int *comp)
{
    node_t *root2 = root, *root3 = NULL;
    node_t *tmp = malloc(sizeof(node_t));
    strcpy(tmp->word, str);
    tmp->key = 1;
    tmp->left = NULL;
    tmp->right = NULL;
    char loverstr[100] = "";
    strcat(loverstr, str);

    for (int i = 0; str[i]; i++)
        loverstr[i] = tolower(str[i]);

    while (root2 != NULL)
    {
        root3 = root2;
        char loverword[100] = "";
        strcat(loverword, root2->word);

        for (int i = 0; root2->word[i]; i++)
            loverword[i] = tolower(root2->word[i]);
        (*comp)++;
        if (strcmp(loverstr, loverword) < 0)
            root2 = root2->left;
        else if (strcmp(loverstr, loverword) > 0)
            root2 = root2->right;
        else
        {
            root2->key++;
            free(tmp);
            return root;
        }
    }

    tmp->parent = root3;

    char loverword[100] = "";
    strcat(loverword, root3->word);

    (*comp)++;
    for (int i = 0; root3->word[i]; i++)
        loverword[i] = tolower(root3->word[i]);

    if (strcmp(loverstr, loverword) < 0)
        root3->left = tmp;
    else
        root3->right = tmp;
    return root;
}

void free_tree(node_t *root)
{
    if (root->left != NULL)
        free_tree(root->left);

    if (root->right != NULL)
        free_tree(root->right);

    free(root);
}

node_t *search(node_t *root, char *str, int *comp)
{
    if (root == NULL)
        return NULL;

    char loverword[100] = "";
    strcat(loverword, root->word);

    for (int i = 0; root->word[i]; i++)
        loverword[i] = tolower(root->word[i]);

    char loverstr[100] = "";
    strcat(loverstr, str);

    for (int i = 0; str[i]; i++)
        loverstr[i] = tolower(str[i]);

    (*comp)++;
    if (strcmp(loverword, loverstr) == 0)
        return root;
    else if (strcmp(loverword, loverstr) < 0)
        return search(root->right, str, comp);
    else
        return search(root->left, str, comp);
}

node_t *min_node(node_t *node)
{
    if (node->left != NULL)
        return min_node(node->left);
    else
        return node;
}

void delete_node(node_t *node)
{
    if (node->left == NULL && node->right == NULL)
    {
        if (node->parent->left == node)
            node->parent->left = NULL;
        else
            node->parent->right = NULL;

        free(node);
        return;
    }

    if (node->left == NULL && node->right != NULL)
    {
        if (node->parent->left == node)
            node->parent->left = node->right;
        else
            node->parent->right = node->right;

        free(node);
        return;
    }

    if (node->right == NULL && node->left != NULL)
    {
        if (node->parent->left == node)
            node->parent->left = node->left;
        else
            node->parent->right = node->left;

        free(node);
        return;
    }

    node_t *temp = min_node(node->left);
    node->key = temp->key;
    strcpy(node->word, temp->word);
    delete_node(temp);
}

void print_line(node_t *root, FILE *f, int *nullcount)
{
    if (root->left != NULL)
    {
        // fprintf(f, "    \"%s\"->\"%s\";\n", root->word, root->left->word);
        fprintf(f, "    \"%s %d\"->\"%s %d\";\n", root->word, root->key, root->left->word, root->left->key);
        print_line(root->left, f, nullcount);
    }

    if (root->right != NULL)
    {
        // fprintf(f, "    \"%s\"->\"%s\";\n", root->word, root->right->word);
        fprintf(f, "    \"%s %d\"->\"%s %d\";\n", root->word, root->key, root->right->word, root->right->key);
        print_line(root->right, f, nullcount);
    }
}

void show_tree(node_t *root)
{
    FILE *f = fopen("temp.gv", "w");
    fprintf(f, "digraph BST {\n");

    int nullcount = 0;
    print_line(root, f, &nullcount);
    fprintf(f, "}\n");
    fclose(f);

    f = popen("dot -Tsvg temp.gv -ograph.svg", "r");
    pclose(f);
    f = popen("rm -rf temp.gv", "r");
    pclose(f);
    f = popen("xdg-open ./graph.svg", "r");
    pclose(f);
}
