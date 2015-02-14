#include "mypthread.h"
#include <stdlib.h>
#include <stdio.h>

int id = 0;
thread_context_node *thread_queue = NULL;

int mypthread_create(mypthread_t *thread, const mypthread_attr_t *attr,
			void *(*start_routine) (void *), void *arg){
    char* thread_stack = malloc(sizeof(char) * 16000);
    thread->id = id; 
    thread->ret = (int*)malloc(sizeof(int));
    *(thread->ret) = 0;
    thread->retval = NULL;
    thread->arg = arg;
    thread->start_routine = start_routine;
    ucontext_t *main, *thread_context;
    thread_context = (ucontext_t*) malloc(sizeof(ucontext_t));
    thread_context_node *main_node, *thread_node;
    thread_node = (thread_context_node*) malloc(sizeof(thread_context_node));
    getcontext(thread_context);
    thread_context->uc_stack.ss_sp = thread_stack;
    thread_context->uc_stack.ss_size = 16000;
    thread_context->uc_link = NULL;
    makecontext(thread_context, (void*)start_routine, 1, arg);
    thread_node->next = NULL;
    thread_node->thread = thread;
    thread_node->context = thread_context;
    id++;
    add_to_end(thread_node);
    return 0;
}

void mypthread_exit(void *retval){
    thread_context_node *temp = pop();
    temp->thread->retval = retval;
    *(temp->thread->ret) = 1;
    free(temp->context->uc_stack.ss_sp);
    free(temp->context);
    free(temp);
    setcontext(thread_queue->context);
}

int mypthread_yield(void){
    //printf("\n yielded");
    thread_context_node *temp = pop();
    add_to_end(temp);
    swapcontext(temp->context, thread_queue->context);
    return 0;
}

int mypthread_join(mypthread_t thread, void **retval){
    //printf("\n entered join %d id", thread.id);
    ucontext_t *main_context;
    main_context = (ucontext_t*) malloc(sizeof(ucontext_t));
    thread_context_node *main = malloc(sizeof(thread_context_node));
    main->context = main_context;
    main->next = NULL;
    main->thread = NULL;
    add_to_front(main);
    while(*(thread.ret) == 0){
       //printf("\nentered join loop");
        mypthread_yield();
    }
    pop();
    free(main_context);
    free(main);
    //*retval = thread.retval;
    return 0;
}

thread_context_node* pop(void){
    thread_context_node *temp = thread_queue;
    thread_queue = thread_queue->next;
    return temp;
}

void add_to_front(thread_context_node *node){
    node->next = thread_queue;
    thread_queue = node;
}

void add_to_end(thread_context_node *node){
    if(thread_queue == NULL){
        thread_queue = node;
        return;
    }
    thread_context_node *temp = thread_queue;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = node;
    node->next = NULL;
}

void print_nodes(){
    thread_context_node *temp = thread_queue;
    while(temp != NULL){
        if(temp->thread != NULL)
        printf("\n %d id", temp->thread->id);
        temp = temp->next;
    }
}
