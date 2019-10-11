#pragma once

#include "numtypes.hh"

constexpr struct Frame {
  s9_23 l = 0._s9_23;
  s9_23 r = 0._s9_23;
} zero;

constexpr int kUiUpdateRate = 200; // Hz
constexpr int kSampleRate = 48000; // Hz
constexpr int kBlockSize = 8;
constexpr int kMaxNumOsc = 16;

enum TwistMode { FEEDBACK, PULSAR, CRUSH };
enum WarpMode { FOLD, CHEBY, SEGMENT };
enum ScaleMode { TWELVE, OCTAVE, FREE };
enum ModulationMode { ONE, TWO, THREE };

enum SplitMode { ALTERNATE, LOW_HIGH, LOWEST_REST };

struct Parameters {
  f balance;                        // -1..1
  f root;                        // semitones
  f pitch;                       // midi note
  f spread;                      // semitones
  f detune;                      // semitones

  struct Modulation {
    ModulationMode mode;
    f value;                 // 0..1
  } modulation;

  struct Scale {
    ScaleMode mode;
    int value;                     // 0..9
  } scale;

  struct Twist {
    TwistMode mode;
    f value;                    // 0..1
  } twist;

  struct Warp {
    WarpMode mode;
    f value;                    // 0..1
  } warp;

  struct AltParameters {
    int numOsc;// = kMaxNumOsc;      // 0..kMaxNumOsc
    SplitMode stereo_mode;// = ALTERNATE;
    SplitMode freeze_mode;// = LOW_HIGH;
    f crossfade_factor;// = 0.125_f;
    bool validate() {
      return
        numOsc <= kMaxNumOsc &&
        numOsc > 0 &&
        ( stereo_mode == ALTERNATE ||
          stereo_mode == LOW_HIGH ||
          stereo_mode == LOWEST_REST ) &&
        ( freeze_mode == ALTERNATE ||
          freeze_mode == LOW_HIGH ||
          freeze_mode == LOWEST_REST ) &&
        crossfade_factor <= 1_f &&
        crossfade_factor >= 0_f;
    }
  };
  AltParameters alt;
  AltParameters default_alt = {kMaxNumOsc, ALTERNATE, LOW_HIGH, 0.125_f};

  f new_note, fine_tune;
};

enum EventType {
  ButtonPush,
  ButtonRelease,
  ButtonTimeout,
  GateOn,
  GateOff,
  SwitchScale,
  SwitchMod,
  SwitchTwist,
  SwitchWarp,
  PotMove,
  NewNote,
  ScaleChange,
  AltParamChange,
  StartCatchup,
  EndOfCatchup,
};

struct Event {
  EventType type;
  int data;
};
