#include <stdlib.h>

extern "C" {

  size_t init_memory_pool(size_t, void *);
  void destroy_memory_pool(void *);
  void * tlsf_malloc (size_t);
  void   tlsf_free (void *);
  size_t tlsf_get_object_size (void *);
  void   tlsf_lock (void);
  void   tlsf_unlock (void);

  size_t xxinit_memory_pool(size_t size, void *ptr){
	  return init_memory_pool(size, ptr);
  }

  void xxdestroy_memory_pool(void *ptr){
	  destroy_memory_pool(ptr);
  }

  void * xxmalloc (size_t sz) {
    return tlsf_malloc (sz);
  }
  
  void xxfree (void * ptr) {
    tlsf_free (ptr);
  }
  
  size_t xxmalloc_usable_size (void * ptr) {
    return tlsf_get_object_size (ptr);
  }
  
  void xxmalloc_lock() {
    tlsf_lock();
  }
  
  void xxmalloc_unlock() {
    tlsf_unlock();
  }
}


