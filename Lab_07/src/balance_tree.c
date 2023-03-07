#include "../inc/balance_tree.h"

unsigned char height(node_t *p)
{
    return p ? p->height : 0;
}

void fixheight(node_t *p)
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

int bfactor(node_t *p)
{
    return height(p->right) - height(p->left);
}

node_t *rotateright(node_t *p) // правый поворот вокруг p
{
    node_t *q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node_t *rotateleft(node_t *q) // левый поворот вокруг q
{
    node_t *p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node_t *balance(node_t *p) // балансировка узла p
{
    fixheight(p);
    if (bfactor(p) == 2)
    {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2)
    {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}

static node_t *insert(node_t *p, char *word, int key, node_t *parent) // вставка ключа k в дерево с корнем p
{
    if (p == NULL)
    {
        node_t *tmp = malloc(sizeof(node_t));
        strcpy(tmp->word, word);
        tmp->key = key;
        tmp->left = NULL;
        tmp->right = NULL;
        tmp->parent = parent;
        tmp->height = 1;
        return tmp;
    }
    if (strcmp(word, p->word) < 0)
        p->left = insert(p->left, word, key, p);
    else
        p->right = insert(p->right, word, key, p);

    return balance(p);
}

node_t *init(node_t *root, node_t *balanced)
{
    if (root->left != NULL)
        balanced = init(root->left, balanced);

    if (root->right != NULL)
        balanced = init(root->right, balanced);

    balanced = insert(balanced, root->word, root->key, NULL);
    return balanced;
}
