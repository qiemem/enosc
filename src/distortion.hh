#pragma once

#include "dsp.hh"
#include "dynamic_data.hh"
#include "bitfield.hh"

namespace Distortion {

  template<WarpMode> inline f warp(s1_15, f);
  template<TwistMode> inline u0_32 twist(u0_32, f);

  template<>
  inline u0_32 twist<FEEDBACK>(u0_32 phase, f amount) {
    return phase;
  }

  template<>
  inline u0_32 twist<PULSAR>(u0_32 phase, f amount) {
    // amount: 1..64
    u7_9 p = u7_9(amount);
    return u0_32::wrap((u0_16::narrow(phase) * p).min(1._u7_25));
  }

  template<>
  inline u0_32 twist<DECIMATE>(u0_32 phase, f amount) {
    u0_16 am = u0_16(amount);
    Bitfield<32> x {phase};
    x ^= Bitfield<32>(u0_16::narrow(phase)*am);
    x ^= Bitfield<32>(0.25_u0_16 * am);
    return u0_32::of_repr(x.repr());
  }

  template<>
  inline f warp<FOLD>(s1_15 x, f amount) {
    s1_31 sample = x * s1_15(amount);
    u0_32 phase = sample.to_unsigned_scale();
    f res = DynamicData::fold.interpolateDiff<f>(phase);
    res *= DynamicData::fold_max.interpolate(amount);
    return res;
  }

  template<>
  inline f warp<CHEBY>(s1_15 x, f amount) {
    constexpr f const fact = f(DynamicData::cheby.size() - 2);
    amount *= fact;
    auto [idx, frac] = amount.integral_fractional();
    u0_32 phase = u0_32(x.to_unsigned_scale());
    f s1 = DynamicData::cheby[idx].interpolate(phase);
    f s2 = DynamicData::cheby[idx+1].interpolate(phase);
    return Signal::crossfade(s1, s2, frac);
  }

  template<>
  inline f warp<CRUSH>(s1_15 x, f amount) {
    constexpr f const fact = f(Data::triangles.size() - 1);
    amount *= fact;
    auto [idx, frac] = amount.integral_fractional();
    u0_32 phase = u0_32(x.to_unsigned_scale());
    f s1 = Data::triangles[idx].interpolate(phase);
    f s2 = Data::triangles[idx+1].interpolate(phase);
    return Signal::crossfade(s1, s2, frac);
  }
};
