// Custom QMK code layered on top of the Oryx export.
// Oryx never generates this file, so Oryx merges cannot conflict with it.
#include QMK_KEYBOARD_H

#ifdef FLOW_TAP_TERM
static bool is_mod_tap_with(uint16_t keycode, uint8_t mods) {
    return IS_QK_MOD_TAP(keycode) && QK_MOD_TAP_GET_MODS(keycode) == mods;
}

// Flow Tap settles a tap-hold key as tapped when it is pressed within
// FLOW_TAP_TERM of a previous letter key; this removes home row mod misfires
// during fast typing. Keys that are legitimately held mid-word are exempt:
// - layer-taps (Space -> symbols, Backspace -> navigation),
// - Right Alt mod-taps (V, M): AltGr for Polish letters,
// - Shift mod-taps (D, K): capitals right after a space.
uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
    if (IS_QK_LAYER_TAP(keycode)) {
        return 0;
    }
    if (is_mod_tap_with(keycode, MOD_RALT) || is_mod_tap_with(keycode, MOD_LSFT) || is_mod_tap_with(keycode, MOD_RSFT)) {
        return 0;
    }
    if (is_flow_tap_key(keycode) && is_flow_tap_key(prev_keycode)) {
        return FLOW_TAP_TERM;
    }
    return 0;
}
#endif
