#include "../inc/tree.h"
#include "../inc/structs.h"
#include <ctype.h>

void printBT(char *prefix, const node_t *node, bool isLeft)
{
    if (node != NULL)
    {
        printf("%s", prefix);
        if (isLeft && node->parent->right != NULL)
            printf("%s", blue "├──" res);
        else
            printf("%s", blue "└──" res);

        printf("(%s, %d)\n", node->word, node->key);

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

node_t *add(node_t *root, char *str)
{
    node_t *root2 = root, *root3 = NULL;
    node_t *tmp = malloc(sizeof(node_t));
    strcpy(tmp->word, str);
    tmp->key = 1;
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
    tmp->left = NULL;
    tmp->right = NULL;

    char loverword[100] = "";
    strcat(loverword, root3->word);

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

node_t *search(node_t *root, char *str)
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

    if (strcmp(loverword, loverstr) == 0)
        return root;
    else if (strcmp(loverword, loverstr) < 0)
        return search(root->right, str);
    else
        return search(root->left, str);
}

int input_number(int *num)
{
    char line[1024];
    if (fgets(line, 1024, stdin) == NULL)
        return EXIT_FAILURE;

    if (line[strlen(line)] == '\n')
        line[strlen(line)] = '\0';

    if (atoi(line))
        *num = atoi(line);
    else if (strchr(line, 48) != NULL)
        *num = 0;
    else
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

void input_word(char *str, char *print)
{
    strcpy(str, "");
    printf("%s", print);

    if (fgets(str, 100, stdin) != str)
        puts(red "Couldn't scan the line" res);

    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
}

int count_in_file(FILE *src, char *str)
{
    int count = 0;
    rewind(src);
    char temp_str[100];
    while (fscanf(src, "%s", temp_str) == 1)
        if (strcmp(temp_str, str) == 0)
            count++;

    return count;
}

int shift_right(node_t *root)
{
    printf("cur: %s\n", root->word);

    printf("left: %s\n", root->left->word);
    printf("right: %s\n", root->right->word);
    if (root->left == NULL)
    {
        root->left = root->parent->right;
        return EXIT_SUCCESS;
    }
    if (root->left->right != NULL && root->left->left != NULL)
        shift_right(root->left);
    else if (root->left->right != NULL) {
        
    }

    root->left->right = root->right;
    return EXIT_SUCCESS;
}
