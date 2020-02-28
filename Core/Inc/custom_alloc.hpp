/*
 * custom_alloc.hpp
 *
 *  Created on: 10 фев. 2020 г.
 *      Author: ALScode
 * All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CUSTOM_ALLOC_HPP_
#define CUSTOM_ALLOC_HPP_


/*******************************************************************************
*  Includes
*******************************************************************************/
#pragma once
#include "FreeRTOS.h"
#include "tlsf.h"

namespace app {
/*******************************************************************************
*  Defines
*******************************************************************************/
#define ALLOCATOR(alloc, type, name)		\
			alloc aa;						\
			CustomAllocator<type>name(aa)
/*******************************************************************************
*  Constants and variables
*******************************************************************************/

/*******************************************************************************
*  Enums
*******************************************************************************/

/*******************************************************************************
*  Typedefs
*******************************************************************************/

/*******************************************************************************
*  Struct / Classes
*******************************************************************************/
//struct AppAllocator{
//	typedef size_t size_type;
//	typedef void* pointer;
//
//	size_type max_size() const noexcept{
//		return xPortGetFreeHeapSize();
//	}
//
//	pointer allocate(size_type size){
//		return pvPortMalloc(size);
//	}
//
//	void deallocate(pointer ptr){
//		vPortFree(ptr);
//	}
//};


struct AppAllocator{
	typedef size_t size_type;
	typedef void* pointer;

	AppAllocator (pointer pool_, size_type size_) : pool(pool_), size(size_){
		init_memory_pool(size, pool);
	}
	~AppAllocator(){
		destroy_memory_pool(pool);
	}
	size_type max_size() const noexcept{
		return sizeof pool;
	}

	pointer allocate(size_type size){
		return tlsf_malloc(size);
	}

	void deallocate(pointer ptr){
		tlsf_free(ptr);
	}

private:
	pointer pool;
	size_type size;
};

template<typename T>
class CustomAllocator{
public:
	CustomAllocator()noexcept : alloc(nullptr){}
	explicit CustomAllocator(AppAllocator& alloc_)noexcept : alloc(&alloc_){}
	template<class U>
	CustomAllocator(const CustomAllocator<U>& other)noexcept : alloc(other.alloc){}

	~CustomAllocator() noexcept{};

	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;

	size_type max_size() const noexcept{
		return alloc->max_size();
	}

	pointer allocate(size_type count, const void *ptr = 0) noexcept{
		size_t size = count * sizeof(T);
		return static_cast<pointer>(alloc->allocate(size));
	}

	void deallocate(pointer ptr, size_type size) noexcept{
		(void)size;
		void *p = static_cast<void*>(ptr);
		alloc->deallocate(p);
	}

	AppAllocator *alloc;
};

template<class T, class U>
bool operator==(const CustomAllocator<T>& lhs, const CustomAllocator<U>& rhs) {
	return lhs.alloc == rhs.alloc;
}

template<class T, class U>
bool operator!=(const CustomAllocator<T>& lhs, const CustomAllocator<U>& rhs) {
	return !(lhs.alloc == rhs.alloc);
}
/*----------------------------------------------------------------------------*/
typedef CustomAllocator<uint8_t> alloc_type8;
typedef CustomAllocator<uint16_t> alloc_type16;
typedef CustomAllocator<uint32_t> alloc_type32;
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*******************************************************************************
*  Template class methods
*******************************************************************************/

/*******************************************************************************
*  Public functions declarations
*******************************************************************************/
AppAllocator& allocator(void);
} // End of ... namespace


#endif /* CUSTOM_ALLOC_HPP_ */
