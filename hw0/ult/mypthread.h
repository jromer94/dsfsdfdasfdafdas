#ifndef H_MYPTHREAD
#define H_MYPTHREAD
#include <ucontext.h>

// Types
typedef struct {
	void* retval;
        int* ret;
        void *(*start_routine) (void *);
        void *arg;
        int id;
} mypthread_t;

typedef struct {
	// Define any fields you might need inside here.
} mypthread_attr_t;

typedef struct node{
    struct node *next;
    ucontext_t *context;
    mypthread_t *thread;
} thread_context_node;

// Functions
int mypthread_create(mypthread_t *thread, const mypthread_attr_t *attr,
			void *(*start_routine) (void *), void *arg);

void mypthread_exit(void *retval);

int mypthread_yield(void);

int mypthread_join(mypthread_t thread, void **retval);

void add_to_front(thread_context_node *node);

void add_to_end(thread_context_node *node);

thread_context_node* pop(void);

/* Don't touch anything after this line.
 *
 * This is included just to make the mtsort.c program compatible
 * with both your ULT implementation as well as the system pthreads
 * implementation. The key idea is that mutexes are essentially
 * useless in a cooperative implementation, but are necessary in
 * a preemptive implementation.
 */

typedef int mypthread_mutex_t;
typedef int mypthread_mutexattr_t;

inline static int mypthread_mutex_init(mypthread_mutex_t *mutex,
			const mypthread_mutexattr_t *attr) { return 0; }

inline static int mypthread_mutex_destroy(mypthread_mutex_t *mutex) { return 0; }

inline static int mypthread_mutex_lock(mypthread_mutex_t *mutex) { return 0; }

inline static int mypthread_mutex_trylock(mypthread_mutex_t *mutex) { return 0; }

inline static int mypthread_mutex_unlock(mypthread_mutex_t *mutex) { return 0; }

#endif
