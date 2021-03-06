// Copyright 2005-2017 Michael E. Stillman.

#include "res-gausser.hpp"
#include "res-gausser-ZZp.hpp"
#include "res-gausser-QQ.hpp"
#include "res-gausser-QQ-hybrid.hpp"

ResGausser* ResGausser::newResGausser(const Ring* K1)
{
  if (K1->isFinitePrimeField())
    {
      auto p = K1->characteristic();
      if (p > 32767)
        {
          ERROR(
              "currently, res(...,FastNonminimal=>true) requires finite prime "
              "fields with p < 32767");
          return nullptr;
        }
      return new ResGausserZZp(K1);
    }
  if (K1->is_QQ())
    {
      // return new ResGausserQQHybrid(K1, 1000, 32003, 32009);
      //      return new ResGausserQQHybrid(K1, 1000, 1073741891, 1073741909);
      return new ResGausserQQHybrid(K1, 1000, 32003, 1073741909);
    }
  if (K1->is_QQ())
    {
      return new ResGausserQQ(K1, 32003);
    }
  ERROR(
      "currently, res(...,FastNonminimal=>true) requires finite prime fields "
      "or funny QQ");
  return nullptr;
}

// Local Variables:
// compile-command: "make -C $M2BUILDDIR/Macaulay2/e "
// indent-tabs-mode: nil
// End:
