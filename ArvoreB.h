#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 2

extern struct BTreeNode *root;

struct BTreeNode {
  char *val[MAX + 1];
  int count;
  int RRN[MAX + 1];
  struct BTreeNode *link[MAX + 1];
};

struct BTreeNode *createNode(char *val, struct BTreeNode *child) ;

void insertNode(char *val, int pos, struct BTreeNode *node,struct BTreeNode *child);

void splitNode(char *val, char **pval, int pos, struct BTreeNode *node,struct BTreeNode *child, struct BTreeNode **newNode);

int setValue(char *val, char **pval,struct BTreeNode *node, struct BTreeNode **child) ;

void insert(char *val);

void search(char *val, int *pos, struct BTreeNode *myNode);

void traversal(struct BTreeNode *myNode) ;