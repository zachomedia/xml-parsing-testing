/*
   The MIT License (MIT)

   Copyright (c) 2014 Zachary Seguin

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#include "queue.h"

#include <stdlib.h>
#include <assert.h>

struct llnode
{
   void *item;
   struct llnode *next;
};

struct _queue
{
   FreeFunction free_func;

   struct llnode *front;
   struct llnode *back;
   int length;
};

// See header for details
Queue create_queue(FreeFunction free_func)
{
   Queue q = malloc(sizeof(struct _queue));
   if (!q) return NULL;

   q->free_func = free_func;
   q->front = NULL;
   q->back = NULL;
   q->length = 0;

   return q;
}// End of create_queue method

// See header for details
void destroy_queue(Queue q)
{
   while (!queue_empty(q))
   {
      void *itm = queue_dequeue(q);
      q->free_func(itm);
   }// End of while

   free(q);
}// End of destroy_queue function

// See header for details
bool queue_empty(Queue q)
{
   assert(q);

   return queue_length(q) == 0;
}// End of queue_empty method

// See header for details
void queue_queue(Queue q, void *item)
{
   assert(q);

   struct llnode *node = malloc(sizeof(struct llnode));
   if (!node) return;

   node->item = item;
   node->next = NULL;

   if (!q->front)
      q->front = node;

   if (q->back)
      q->back->next = node;

   q->back = node;

   q->length += 1;
}// End of queue_queue function

// See header for details
void *queue_front(Queue q)
{
   assert(q);
   assert(queue_length(q) > 0);

   return q->front->item;
}// End of queue_front method

// See header for details
void *queue_dequeue(Queue q)
{
   assert(q);
   assert(queue_length(q) > 0);

   struct llnode *node = q->front;
   void *value = node->item;

   q->front = node->next;
   q->length -= 1;

   if (!q->front)
      q->back = NULL;

   free(node);
   return value;
}// End of queue_dequeue method

// See header for details
int queue_length(Queue q)
{
   assert(q);

   return q->length;
}// End of queue_length method
