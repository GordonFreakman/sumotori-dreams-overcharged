#ifndef SUMO_DECOMP_H
#define SUMO_DECOMP_H

#define DECOMP_STATIC_ASSERT_VALUE2(value, line) \
  typedef int decomp_static_assert_##line[(value) ? 1 : -1]
#define DECOMP_STATIC_ASSERT_VALUE(value, line) DECOMP_STATIC_ASSERT_VALUE2(value, line)
#define DECOMP_STATIC_ASSERT(value) DECOMP_STATIC_ASSERT_VALUE(value, __LINE__)
#define DECOMP_SIZE_ASSERT(type, size) DECOMP_STATIC_ASSERT(sizeof(type) == (size))

#endif
