#include <stdio.h>
#include <assert.h>

#include "bst.h"
#include "bst.c"
int main()
{
  Node *a, *b;
  a = insertNode(NULL, 42);
  insertNode(a, 5);
  insertNode(a, 50);
  insertNode(a, 45);
  insertNode(a, 47);
  insertNode(a, 44);
  insertNode(a,55 );
  
  deleteNode(a,50);
  printSubtree(a);

  deleteSubtree(a,42);


  
  
  return 0;
}
