#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
#    if defined(ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS) || defined(ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS)

#        ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
RGB_MATRIX_EFFECT(SOLID_REACTIVE_NEXUS)
#        endif

#        ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
RGB_MATRIX_EFFECT(SOLID_REACTIVE_MULTINEXUS)
#        endif

#        ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV SOLID_REACTIVE_NEXUS_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = tick - dist;
    uint16_t nexusHue = 127;
    if (effect > 255) effect = 255;
    if (dist > 72) effect = 255;
    if(effect!=255) dprintf("%u\n", effect);
    if ((dx > 8 || dx < -8) && (dy > 8 || dy < -8)) effect = 255;
#            ifdef RGB_MATRIX_SOLID_REACTIVE_GRADIENT_MODE
    hsv.h = scale16by8(g_rgb_timer, add8(rgb_matrix_config.speed, 1) >> 6);
#            endif
    hsv.v = qadd8(hsv.v, 255 - effect);
    //hsv.h = qsub8(hsv.h, (255 - effect)/2);
    if(hsv.h>nexusHue) {
        hsv.h = qsub8(hsv.h, scale8((hsv.h-nexusHue),255-effect));
    } else {
        hsv.h = qadd8(hsv.h, scale8((nexusHue-hsv.h),255-effect));
    }

    //if (effect < 255) hsv.h = 127; //rgb_matrix_config.hsv.h + dy / 4;
    return hsv;
}

#            ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
bool SOLID_REACTIVE_NEXUS(effect_params_t* params) {
    return effect_runner_reactive_splash(qsub8(g_last_hit_tracker.count, 1), params, &SOLID_REACTIVE_NEXUS_math);
}
#            endif

#            ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
bool SOLID_REACTIVE_MULTINEXUS(effect_params_t* params) {
    return effect_runner_reactive_splash(0, params, &SOLID_REACTIVE_NEXUS_math);
}
#            endif

#        endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#    endif     // !defined(ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS) || !defined(ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS)
#endif         // RGB_MATRIX_KEYREACTIVE_ENABLED
