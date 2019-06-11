/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    /* Remember to handle the case if malloc returned NULL */
    queue_t *q = malloc(sizeof(queue_t));
    if(q==NULL) return NULL;
    q->head = NULL;
    q->tail = NULL;
	q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* Remember to free the queue structue and list elements */
    if(q==NULL) return;
    if(q->size>0){
    	list_ele_t *cur = q->head, *second;
    	/*
    	list_ele_t *cur = p->head;
    	list_ele_t *second = p->head->next;
    	*/
    	while(cur!=NULL){
    		second = cur->next;
    		free(cur);
    		cur = second;
    	}
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    /* What should you do if the q is NULL? */
    if(q==NULL) return false;
    /* What if malloc returned NULL? */
    list_ele_t *newHead = malloc(sizeof(list_ele_t));
    if(newHead == NULL) return false;
	newHead->value = v;
	newHead->next = q->head;
	q->head = newHead;
	if(q->size==0){
		q->tail = newHead;
	}
	q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    /* Remember: It should operate in O(1) time */
    if(q==NULL) return false;
    
    if(q->size==0){return q_insert_head(q,v);}
    
    list_ele_t *newTail = malloc(sizeof(list_ele_t));
    if(newTail==NULL) return false;
    newTail->value = v;
	newTail->next = NULL;
    q->tail->next = newTail;
    q->tail = newTail;
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
	if(q==NULL||q->size==0) return false;
	int v = q->head->value;
	
	list_ele_t *temp = q->head;
	if(q->size==1){
		q->head = NULL;
		q->tail = NULL;
	} else{
		q->head = q->head->next;
	}
	q->size--;
	free(temp);
	if(vp!=NULL) *vp = v;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* Remember: It should operate in O(1) time */
    if(q==NULL) return 0;
    return q->size;
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
	if(q==NULL||q->size<2) return;
	list_ele_t *newHead = q->tail, *newTail = q->head;
	list_ele_t *first = q->head, *second = q->head->next, *third;
	while(second!=NULL){
		third = second->next;
		second->next = first;
		first = second;
		second = third;
	}
	q->head = newHead;
	q->tail = newTail;
	q->tail->next = NULL;
}

