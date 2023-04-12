#if !defined(CC_ASCII_H_INCLUDED)
#define CC_ASCII_H_INCLUDED

static inline void
cc_ascii_replace
  (
    char *p,
    size_t n,
    char old,
    char new
  )
{
  for (size_t i = 0; i < n; ++i)
  {
    if (p[i] == old)
    {
      p[i] = new;
    } 
  }
}

static inline void
cc_ascii_to_lower
  (
    char *p,
    size_t n
  )
{
  for (size_t i = 0; i < n; ++i)
  {
    if ('A' <= p[i] && p[i] <= 'Z')
    {
      p[i] = p[i] + 32;
    } 
  }
}

static inline void
cc_ascii_to_upper
  (
    char *p,
    size_t n
  )
{
  for (size_t i = 0; i < n; ++i)
  {
    if ('a' <= p[i] && p[i] <= 'z')
    {
      p[i] = p[i] - 32;
    } 
  }
}

#endif // CC_ASCII_H_INCLUDED
