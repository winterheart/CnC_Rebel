/*
**	Command & Conquer Renegade(tm)
**	Copyright 2025 Electronic Arts Inc.
**	Copyright 2025 CnC Rebel Developers.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "FastAllocator.h"

static FastAllocatorGeneral *generalAllocator; // This general allocator will do all allocations for us.

FastAllocatorGeneral *FastAllocatorGeneral::Get_Allocator() {
  if (!generalAllocator) {
    generalAllocator = reinterpret_cast<FastAllocatorGeneral *>(::malloc(sizeof(FastAllocatorGeneral)));

    new (generalAllocator) FastAllocatorGeneral();
  }
  return generalAllocator;
}

FastAllocatorGeneral::FastAllocatorGeneral()
    : MemoryLeakLogEnabled(false), AllocatedWithMalloc(0), AllocatedWithMallocCount(0), ActualMemoryUsage(0) {
  int alloc_size = ALLOC_STEP;
  for (auto & allocator : allocators) {
    allocator.Init(alloc_size);
    alloc_size += ALLOC_STEP;
  }
}

template <class T>
T *FastSTLAllocator<T>::allocate(size_type n, const void *) {
  return n != 0 ? static_cast<T *>(generalAllocator->Alloc(n * sizeof(T))) : nullptr;
}

template <class T>
void FastSTLAllocator<T>::deallocate(pointer p, size_type /* n */) { generalAllocator->Free(p); }
