// Copyright 1995  Michael E. Stillman

#ifndef _ringelem_hh_
#define _ringelem_hh_

#include <gmp.h>
#include <mpfr.h>
#include "newdelete.hpp"

struct Nterm;

typedef Nterm *tpoly;

union ring_elem
{

  int    int_val;
  Nterm * poly_val;
 private:			// move this line up to the top eventually
  mpz_ptr  mpz_val;

 public:
  ring_elem() : poly_val(0) {}
  //explicit ring_elem(int a) : int_val(a) {} // really want this version...
  ring_elem(int a) : int_val(a) {}
  ring_elem(Nterm *a) : poly_val(a) {}
  ring_elem(mpz_ptr a) : mpz_val(a) {}

  operator int() const { return int_val; }
  operator tpoly() const { return poly_val; }

  int     get_int() const { return int_val; }
  Nterm * get_poly() const { return poly_val; }
  mpz_ptr get_mpz() const { return mpz_val; }

#if 0
  ring_elem &operator=(int a) { int_val = a; return *this; }
  ring_elem &operator=(Nterm *a) { poly_val = a; return *this; }
  // ring_elem &operator=(mpz_t a) { mpz_val = a; return *this; }
#endif

};

struct Nterm
{
  Nterm *    next;
  ring_elem coeff;
  int       monom[1];
};

typedef struct vecterm *vec;
struct vecterm : public our_new_delete
{
  vec       next;
  int       comp;
  ring_elem coeff;
};

// #define MPZ_VAL(f) (reinterpret_cast<mpz_ptr>((f).poly_val))
// #define MPZ_RINGELEM(a) (ring_elem(reinterpret_cast<Nterm *>(a)))

#define MPQ_VAL(f) (reinterpret_cast<gmp_QQ>((f).poly_val))
#define MPQ_RINGELEM(a) (ring_elem(reinterpret_cast<Nterm *>(a)))

#define CCELEM_VAL(f) (reinterpret_cast<gmp_CC>((f).poly_val))
#define CC_RINGELEM(a) (ring_elem(reinterpret_cast<Nterm *>(a)))
#define CC_IM(f) ((CCELEM_VAL(f))->im)
#define CC_RE(f) ((CCELEM_VAL(f))->re)
#define CC_NORM(f) (sqrt(CC_RE(f)*CC_RE(f) + CC_IM(f)*CC_IM(f)))

#define MPF_VAL(f) (reinterpret_cast<mpfr_ptr>((f).poly_val))
#define MPF_RINGELEM(a) (ring_elem(reinterpret_cast<Nterm *>(a)))

#define BIGCC_VAL(f) (reinterpret_cast<gmp_CC>((f).poly_val))
#define BIGCC_RINGELEM(a) (ring_elem(reinterpret_cast<Nterm *>(a)))
#define BIGCC_RE(f) (BIGCC_VAL(f)->re)  // returns actual value, not copy
#define BIGCC_IM(f) (BIGCC_VAL(f)->im)

#define TOWER_VAL(f) (reinterpret_cast<poly>((f).poly_val))
#define TOWER_RINGELEM(a) (ring_elem(reinterpret_cast<Nterm *>(a)))

#endif

// Local Variables:
// compile-command: "make -C $M2BUILDDIR/Macaulay2/e "
// End: