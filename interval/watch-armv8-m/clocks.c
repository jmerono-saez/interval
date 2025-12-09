#include <interval/watch-armv8-m/clocks.h>

#include <stdint.h>

volatile mg24_hfxo_t  * const mg24_hfxo  = (void *)(0x4A004000);
volatile mg24_hfrco_t * const mg24_hfrco = (void *)(0x40010000);
volatile mg24_dpll_t  * const mg24_dpll  = (void *)(0x4001C000);
volatile mg24_lfxo_t  * const mg24_lfxo  = (void *)(0x40020000);
volatile mg24_lfrco_t * const mg24_lfrco = (void *)(0x40024000);

volatile mg24_cm_unit_t * const mg24_cm_unit = (void *)(0x40008000);

void mg24_clocks_init(void) {
    // === oscillators ===
    
    // 1. disable HFXO.
    // 2. disable HFRCO.
    // 3. disable DPLL.
    // 4. disable LFXO.
    // 5. setup LFRCO as on-demand and low-precision.
    
    // note that FSRCO and ULFRCO do not need any setup.
    
    mg24_hfxo->lock = MG24_HFXO_UNLOCK;
    mg24_hfxo->ctrl = 0b00000111000000000000000001000000;
    
    mg24_hfrco->lock = MG24_HFRCO_UNLOCK;
    mg24_hfrco->ctrl = 0b00000010;
    
    mg24_dpll->lock = MG24_DPLL_UNLOCK;
    mg24_dpll->enable = 0;
    
    mg24_lfxo->lock = MG24_LFXO_UNLOCK;
    mg24_lfxo->ctrl = 0b00000010;
    
    mg24_lfrco->lock = MG24_LFRCO_UNLOCK;
    mg24_lfrco->ctrl = 0b00000000;
    
    // === cm_unit ===
    
    // 1. (...).
}
