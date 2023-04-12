/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "cc_os_hash.h"


#include "cc_os.h"


bool cc_startup_hash()
{ return true; }

void cc_shutdown_hash()
{/*Intentionally empty.*/}


size_t cc_hash_p(void* v)
{ return (size_t)(uintptr_t)v; }

size_t cc_hash_i8(int8_t v)
{ return (size_t)v; }

size_t cc_hash_i16(int16_t v)
{ return (size_t)v; }

size_t cc_hash_i32(int32_t v)
{ return (size_t)v; }

size_t cc_hash_i64(int64_t v)
{ return (size_t)v; }

size_t cc_hash_u8(uint8_t v)
{ return (size_t)v; }

size_t cc_hash_u16(uint16_t v)
{ return (size_t)v; }

size_t cc_hash_u32(uint32_t v)
{ return (size_t)v; }

size_t cc_hash_u64(uint64_t v)
{ return (size_t)v; }

size_t cc_hash_sz(size_t v)
{ return v; }

size_t cc_hash_a(const char* p, size_t n)
{
  // Bob Jenkins "One At A Time" hash function.
  if (!p)
  {
    cc_set_status(CC_EINVAL);
    return 0;
  }

  size_t hash = 0;

  for (size_t i = 0; i < n; ++i)
  {
    hash += p[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }

  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);

  return hash;
}
