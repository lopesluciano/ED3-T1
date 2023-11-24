#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreB.h"

#define MAX 3
#define MIN 2


struct BTreeNode *root;

// ... Rest of your functions ...

// Create a node
struct BTreeNode *createNode(char *val, struct BTreeNode *child) {
  struct BTreeNode *newNode;
  newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
  newNode->val[1] = strdup(val); // Use strdup to duplicate strings
  newNode->count = 1;
  newNode->link[0] = root;
  newNode->link[1] = child;
  return newNode;
}

// Insert node
void insertNode(char *val, int pos, struct BTreeNode *node,
        struct BTreeNode *child) {
  int j = node->count;
  while (j > pos) {
    node->val[j + 1] = node->val[j];
    node->link[j + 1] = node->link[j];
    j--;
  }
  node->val[j + 1] = strdup(val);
  node->link[j + 1] = child;
  node->count++;
}

// Split node
void splitNode(char *val, char **pval, int pos, struct BTreeNode *node,
         struct BTreeNode *child, struct BTreeNode **newNode) {
  int median, j;

  if (pos > MIN)
    median = MIN + 1;
  else
    median = MIN;

  *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
  j = median + 1;
  while (j <= MAX) {
    (*newNode)->val[j - median] = node->val[j];
    (*newNode)->link[j - median] = node->link[j];
    j++;
  }
  node->count = median;
  (*newNode)->count = MAX - median;

  if (pos <= MIN) {
    insertNode(val, pos, node, child);
  } else {
    insertNode(val, pos - median, *newNode, child);
  }
  *pval = node->val[node->count];
  (*newNode)->link[0] = node->link[node->count];
  node->count--;
}

// Set the value
int setValue(char *val, char **pval,
           struct BTreeNode *node, struct BTreeNode **child) {
  int pos;
  if (!node) {
    *pval = val;
    *child = NULL;
    return 1;
  }

  if (strcmp(val, node->val[1]) < 0) {
    pos = 0;
  } else {
    for (pos = node->count;
       (strcmp(val, node->val[pos]) < 0 && pos > 1); pos--)
      ;
    if (strcmp(val, node->val[pos]) == 0) {
      printf("Duplicates are not permitted\n");
      return 0;
    }
  }
  if (setValue(val, pval, node->link[pos], child)) {
    if (node->count < MAX) {
      insertNode(*pval, pos, node, *child);
    } else {
      splitNode(*pval, pval, pos, node, *child, child);
      return 1;
    }
  }
  return 0;
}

// Insert the value
void insert(char *val) {
  int flag;
  char *i;
  struct BTreeNode *child;

  flag = setValue(val, &i, root, &child);
  if (flag)
    root = createNode(i, child);
}

// Search node
void search(char *val, int *pos, struct BTreeNode *myNode) {
  if (!myNode) {
    return;
  }

  if (strcmp(val, myNode->val[1]) < 0) {
    *pos = 0;
  } else {
    for (*pos = myNode->count;
       (strcmp(val, myNode->val[*pos]) < 0 && *pos > 1); (*pos)--)
      ;
    if (strcmp(val, myNode->val[*pos]) == 0) {
      printf("%s is found", val);
      return;
    }
  }
  search(val, pos, myNode->link[*pos]);

  return;
}

// Traverse the nodes
void traversal(struct BTreeNode *myNode) {
  int i;
  if (myNode) {
    for (i = 0; i < myNode->count; i++) {
      traversal(myNode->link[i]);
      printf("%s ", myNode->val[i + 1]);
    }
    traversal(myNode->link[i]);
  }
}
