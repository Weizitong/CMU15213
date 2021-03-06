/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)
    {
      return NULL;
    }

    q->size = 0;
    q->head = NULL;
    q->tail = NULL;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL)
    {
      return;
    }

    list_ele_t *ptr = q->head;

    while (ptr != NULL)
    {
      list_ele_t *cur = ptr;
      list_ele_t *next = cur->next;
      free(cur->value);
      cur->value = NULL;
      free(cur);
      cur = NULL;
      ptr = next;
    }

    free(q);
    q = NULL;
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL)
    {
      return false;
    }

    list_ele_t *newh = create_new_elem(s);

    if (newh == NULL)
    {
      return false;
    }

    newh->next = q->head;

    // If the tail point to NULL, then we need to assign the value for tail.
    //
    if (q->head == NULL)
    {
      q->tail = newh;
      q->tail->next = NULL;
    }

    q->head = newh;
    q->size++;
    return true;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL)
    {
      return false;
    }

    list_ele_t *newh = create_new_elem(s);

    if (newh == NULL)
    {
      return false;
    }

    if (q->tail == NULL)
    {
      q->tail = q->head = newh;
    }
    else
    {
      q->tail->next = newh;
      q->tail = newh;
      q->tail->next = NULL;
    }

    q->size++;
    return true;
}

list_ele_t *create_new_elem(char *str)
{
    /* What should you do if the q is NULL? */
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */

    list_ele_t *newh = malloc(sizeof(list_ele_t));

    if (newh == NULL)
    {
      return NULL;
    }
    
    newh->value = malloc(sizeof(char) * (strlen(str) + 1));
    
    // If we cannot malloc value for newh->value, then we should free newh as well.
    //
    if (newh->value == NULL)
    {
      free(newh);
      newh = NULL;
      return NULL;
    }

    strcpy(newh->value, str);
    return newh;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL || q->head == NULL)
    {
      return false;
    }

    if (sp != NULL)
    {
      int min = bufsize - 1 < strlen(q->head->value) ? bufsize - 1 : strlen(q->head->value);
      strncpy(sp, q->head->value, min);
      sp[min] = '\0';
    }

    list_ele_t *next = q->head->next;
    list_ele_t *cur = q->head;
    q->head = next;
    free(cur->value);
    cur->value = NULL;
    free(cur);
    cur = NULL;

    if (q->head == NULL)
    {
      q->tail = NULL;
    }

    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->head == NULL)
    {
      return;
    }

    list_ele_t *old_head;
    list_ele_t *next;
    old_head = q->head;
    next = q->head->next;
    q->head->next = NULL;
    while (next != NULL)
    {
      list_ele_t *next_next = next->next;
      next->next = q->head;
      q->head = next;
      next = next_next;
    }

    q->tail = old_head;
}

