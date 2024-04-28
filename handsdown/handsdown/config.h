#include "keydefinitions.h"

// my layers

#define l_any   -1
#define l_alpha 0
#define qwerty_alpha   1
#define l_akG   2
#define l_akM   3
#define l_akX   4
#define l_akT   5
#define l_akC   6
#define l_akK   7
#define l_akD   8
#define l_akW   9
#define l_akF   10
#define l_akP   11
#define l_akB   12
#define l_akV   13
#define l_akJ   14
#define l_akA   15
#define l_akU   16
#define l_akE   17
#define l_akO   18
#define l_akI   19
#define l_akDot 20
#define l_sym   21
#define l_num   22
#define l_fun   23
#define l_nav   24
#define l_cfg   25
#define LOWER  26
#define MAGIC 27
#define FACTORY_TEST 28

#define my_tapping_term 170
#define my_quick_tapping_term 112
#define my_ak_delay 40

/* Create a ZMK Behavior without having to specify the name three times */
#define ZMK_BEHAVIOR(NAME, ...) \
    / { \
        behaviors { \
            NAME: NAME { \
                __VA_ARGS__ \
            }; \
        }; \
    };

/* Hold-Tap helper */
#define HOLD_TAP(NAME, ...) \
    ZMK_BEHAVIOR(NAME, \
        compatible = "zmk,behavior-hold-tap"; \
        #binding-cells = <2>; \
        __VA_ARGS__ \
    )

#define MOD_MORPH(NAME, STANDARD, MORPHED, MODS, ...) \
    ZMK_BEHAVIOR(NAME, \
        compatible = "zmk,behavior-mod-morph"; \
        #binding-cells = <0>; \
        bindings = <STANDARD>, <MORPHED>; \
        mods = <(MODS)>; \
        __VA_ARGS__ \
    )

/* Autoshift Behavior using defined timer */
#define AUTOSHIFT_TAPPING_TERM_MS 200

#define SHIFT_MORPH(NAME, LOWER, UPPER) \
    MOD_MORPH(NAME, LOWER, UPPER, MOD_LSFT|MOD_RSFT)

#define AUTOSHIFT(NAME, HOLD, TAP) \
    HOLD_TAP(NAME, \
        flavor = "tap-preferred"; \
        tapping-term-ms = <AUTOSHIFT_TAPPING_TERM_MS>;  /* Hold for Shift */ \
        bindings = <HOLD>, <TAP>; \
    )

AUTOSHIFT(as, &kp, &kp)  /* Main Autoshift Behavior */

/* Autoshifting Mod-Morph Behavior that sends another key when Shift is held */
#define AUTOSHIFT_MORPH(NAME, LOWER, UPPER) \
    SHIFT_MORPH(NAME, &as UPPER LOWER, &kp UPPER)

AUTOSHIFT_MORPH(as_f9_f10, F9, F10)
AUTOSHIFT_MORPH(as_f11_f12, F11, F12)
/* Autoshift Behavior using defined timer */

&mt {
    tapping-term-ms = <my_tapping_term>;
};
&sl {
    release-after-ms = <my_tapping_term>;
};
&caps_word {
    continue-list = <UNDER MINUS BSPC DEL LEFT RIGHT>;
};


// #define EN_PRONOUN_COMBOS //  (I, I'm, I've I'd I'll etc)