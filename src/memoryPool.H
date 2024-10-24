#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

namespace Foam
{

template<size_t I>
struct memPool{
    static unsigned short capacity_;
    static void** pointers_;
    static unsigned short freePos_;
    static void * alloc() {
      if(freePos_ == 0) //empty
        return alligned alloc(512, 1UL<<I);
      freePos_--;
      return pointers_[freePos_];
    }
    static void dealloc(void * ptr) {
      if(freePos_ == capacity_) //full
      {
        capacity_ = capacity_ == 0 ? 1 : 2*capacity_;
        pointers_ = static_cast<void**>(realloc(pointers_,capacity_*sizeof(void*)));
      }
      pointers_[freePos_] = ptr;
      freePos_++;
    }
};

#define MP_ALLOC(N) case N: return memPool<N>::alloc();
#define MP_DEALLOC(N) case N: return memPool<N>::dealloc(ptr);
template<size_t I>
inline unsigned short memPool<I>::capacity_=0;

template<size_t I>
inline void** memPool<I>::pointers_=nullptr;

template<size_t I>
inline unsigned short memPool<I>::freePos_ = 0;

class memoryManager
{
public:
    static void* alloc(size_t size)
    {
        if(size<1)
          return nullptr;
          
        size_t pos = ceil(log2(size));
        
        switch(pos) {
        MP_ALLOC(1)
        MP_ALLOC(2)
        MP_ALLOC(3)
        MP_ALLOC(4)
        MP_ALLOC(5)
        MP_ALLOC(6)
        MP_ALLOC(7)
        MP_ALLOC(8)
        MP_ALLOC(9)
        MP_ALLOC(10)
        MP_ALLOC(11)
        MP_ALLOC(12)
        MP_ALLOC(13)
        MP_ALLOC(14)
        MP_ALLOC(15)
        MP_ALLOC(16)
        MP_ALLOC(17)
        MP_ALLOC(18)
        MP_ALLOC(19)
        MP_ALLOC(20)
        MP_ALLOC(21)
        MP_ALLOC(22)
        MP_ALLOC(23)
        MP_ALLOC(24)
        MP_ALLOC(25)
        MP_ALLOC(26)
        MP_ALLOC(27)
        MP_ALLOC(28)
        MP_ALLOC(29)
        MP_ALLOC(30)
        default:
        return nullptr;
        }
    }
    static void dealloc(void* ptr, size_t size)
    {
        if(size<1)
          return;
          
        size_t pos = ceil(log2(size));
        switch(pos) {
        MP_DEALLOC(1)
        MP_DEALLOC(2)
        MP_DEALLOC(3)
        MP_DEALLOC(4)
        MP_DEALLOC(5)
        MP_DEALLOC(6)
        MP_DEALLOC(7)
        MP_DEALLOC(8)
        MP_DEALLOC(9)
        MP_DEALLOC(10)
        MP_DEALLOC(11)
        MP_DEALLOC(12)
        MP_DEALLOC(13)
        MP_DEALLOC(14)
        MP_DEALLOC(15)
        MP_DEALLOC(16)
        MP_DEALLOC(17)
        MP_DEALLOC(18)
        MP_DEALLOC(19)
        MP_DEALLOC(20)
        MP_DEALLOC(21)
        MP_DEALLOC(22)
        MP_DEALLOC(23)
        MP_DEALLOC(24)
        MP_DEALLOC(25)
        MP_DEALLOC(26)
        MP_DEALLOC(27)
        MP_DEALLOC(28)
        MP_DEALLOC(29)
        MP_DEALLOC(30)
        }
    }
};

#undef MP_ALLOC
#undef MP_DEALLOC


///////////////////////////////////////////////////////////////////////////////

#define MEMORY_POOL_MACRO(Type)                                                 \
    template<> inline Foam::List<Foam:: Type>::~List()                                     \
    {                                                                         \
            memoryManager::dealloc(this->v_, this->size_*sizeof(Type));       \
    }                                                                         \
    template<> inline void Foam::List<Foam:: Type>::alloc()                                \
    {                                                                         \
        if (this->size_ > 0) {                                         \
            this->v_ = static_cast<Type*>                                     \
            (                                                                 \
                memoryManager::alloc(this->size_*sizeof(Type))                \
            );                                                                \
        }                                                                     \
    }                                                                         \
    template<> inline void Foam::List<Foam:: Type>::clear()                                \
    {               \
        if (this->v_) {               \
            memoryManager::dealloc(this->v_, this->size_*sizeof(Type));               \
        }               \
        this->v_ = nullptr;               \
        this->size_ = 0;               \
    }               \
    template<> inline void Foam::List<Foam:: Type>::setSize(const label newSize)           \
    {               \
        if (newSize == this->size_) {               \
            return;               \
        }               \
        if (newSize <= 0) {               \
            clear();               \
            return;               \
        }            \
		\
		if(this->size_ > 0)\
        {\
              if(ceil(log2(this->size_*sizeof(Type))) == ceil(log2(newSize*sizeof(Type))))\
              {\
                  this->size_=newSize;\
                  return;\
              }\
              Type* nv = static_cast<Type*>(memoryManager::alloc(newSize*sizeof(Type)));               \
              label toMove = min(this->size_, newSize);               \
              for (int i = 0; i < toMove; i++) {               \
                  nv[i] = std::move(this->v_[i]);               \
              }               \
              clear();               \
              this->size_ = newSize;               \
              this->v_ = nv;               \
              return;\
		}\
		Type* nv = static_cast<Type*>(memoryManager::alloc(newSize*sizeof(Type)));               \
		this->size_ = newSize;               \
		this->v_ = nv;               \
	\
    }\
	template<> inline void Foam::List<Foam:: Type>::reAlloc(const label s)\
    {\
      if(s <= 0) return clear();\
      if(this->size_==s) return;\
      if(this->size_>0) {\
        if(ceil(log2(this->size_*sizeof(Type))) == ceil(log2(s*sizeof(Type))))\
        {\
            this->size_=s;\
            return;\
        }\
        if (this->v_) {               \
            memoryManager::dealloc(this->v_, this->size_*sizeof(Type));               \
        }               \
      }\
      this->v_ = static_cast<Type*>(memoryManager::alloc(s*sizeof(Type)));               \
      this->size_ = s;               \
    }

} // End namespace Foam


#endif

// ************************************************************************* //
