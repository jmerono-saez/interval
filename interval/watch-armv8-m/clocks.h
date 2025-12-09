#ifndef __INTERVAL_WATCH_ARMV8_M_CLOCKS_H__
#define __INTERVAL_WATCH_ARMV8_M_CLOCKS_H__

#include <stdint.h>

// all oscillators should be configured to be enabled on-demand, as it
// takes some work off of the kernel.

// === constants ===

#define MG24_HFXO_UNLOCK  0x580E
#define MG24_HFRCO_UNLOCK 0x8195
#define MG24_DPLL_UNLOCK  0x7102
#define MG24_LFXO_UNLOCK  0x1A20
#define MG24_LFRCO_UNLOCK 0x0F93

#define MG24_CM_UNIT_UNLOCK 0x0000

#define MG24_WATCHDOG_UNLOCK 0x0000

// === types ===

typedef struct mg24_hfxo_t mg24_hfxo_t;

struct mg24_hfxo_t {
    uint32_t ip_revision;      // 0x0000
    uint32_t __pad_0004[0x03]; // 0x0004
    uint32_t xtal_config;      // 0x0010
    uint32_t __pad_0014[0x01]; // 0x0014
    uint32_t xtal_ctrl;        // 0x0018
    uint32_t xtal_bufout_ctrl; // 0x001C
    uint32_t config;           // 0x0020
    uint32_t __pad_0024[0x01]; // 0x0024
    uint32_t ctrl;             // 0x0028
    uint32_t __pad_002c[0x05]; // 0x002C
    uint32_t bufout_trim;      // 0x0040
    uint32_t bufout_ctrl;      // 0x0044
    uint32_t __pad_0048[0x02]; // 0x0048
    uint32_t command;          // 0x0050
    uint32_t __pad_0054[0x01]; // 0x0054
    uint32_t status;           // 0x0058
    uint32_t __pad_005c[0x05]; // 0x005C
    uint32_t interrupt_flags;  // 0x0070
    uint32_t interrupt_mask;   // 0x0074
    uint32_t __pad_0078[0x02]; // 0x0078
    uint32_t lock;             // 0x0080
};

typedef struct mg24_hfrco_t mg24_hfrco_t;

struct mg24_hfrco_t {
    uint32_t ip_revision;      // 0x0000
    uint32_t ctrl;             // 0x0004
    uint32_t fine;             // 0x0008
    uint32_t status;           // 0x000C
    uint32_t interrupt_flags;  // 0x0010
    uint32_t interrupt_mask;   // 0x0014
    uint32_t __pad_0018[0x01]; // 0x0018
    uint32_t lock;             // 0x001C
};

typedef struct mg24_dpll_t mg24_dpll_t;

struct mg24_dpll_t {
    uint32_t ip_revision;      // 0x0000
    uint32_t enable;           // 0x0004
    uint32_t config;           // 0x0008
    uint32_t freq_params;      // 0x000C
    uint32_t interrupt_flags;  // 0x0010
    uint32_t interrupt_mask;   // 0x0014
    uint32_t status;           // 0x0018
    uint32_t __pad_001c[0x02]; // 0x001C
    uint32_t lock;             // 0x0024
};

typedef struct mg24_lfxo_t mg24_lfxo_t;

struct mg24_lfxo_t {
    uint32_t ip_revision;      // 0x0000
    uint32_t ctrl;             // 0x0004
    uint32_t config;           // 0x0008
    uint32_t __pad_000c[0x01]; // 0x000C
    uint32_t status;           // 0x0010
    uint32_t fine;             // 0x0014
    uint32_t interrupt_flags;  // 0x0018
    uint32_t interrupt_mask;   // 0x001C
    uint32_t sync_busy;        // 0x0020
    uint32_t lock;             // 0x0024
};

typedef struct mg24_lfrco_t mg24_lfrco_t;

struct mg24_lfrco_t {
    uint32_t ip_revision;      // 0x0000
    uint32_t ctrl;             // 0x0004
    uint32_t status;           // 0x0008
    uint32_t __pad_000c[0x02]; // 0x000C
    uint32_t interrupt_flags;  // 0x0014
    uint32_t interrupt_mask;   // 0x0018
    uint32_t __pad_001c[0x01]; // 0x001C
    uint32_t lock;             // 0x0020
    uint32_t config;           // 0x0024
    uint32_t __pad_0028[0x01]; // 0x0028
    uint32_t fine;             // 0x002C
    uint32_t fine_inverted;    // 0x0030
    uint32_t command;          // 0x0034
};

typedef struct mg24_cm_unit_t mg24_cm_unit_t;

struct mg24_cm_unit_t {
    uint32_t ip_revision;      // 0x0000
    uint32_t __pad_0004[0x01]; // 0x0004
    uint32_t status;           // 0x0008
    uint32_t __pad_000c[0x01]; // 0x000C
    uint32_t lock;             // 0x0010
    uint32_t watchdog_lock;    // 0x0014
    uint32_t __pad_0018[0x02]; // 0x0018
    uint32_t interrupt_flags;  // 0x0020
    uint32_t interrupt_mask;   // 0x0024
    uint32_t __pad_0028[0x0A]; // 0x0028
    uint32_t fine_command;     // 0x0050
    uint32_t fine_ctrl;        // 0x0054
    uint32_t fine_result;      // 0x0058
    uint32_t __pad_005c[0x02]; // 0x005C
    uint32_t clocks_0_mask;    // 0x0064
    uint32_t clocks_1_mask;    // 0x0068
    uint32_t __pad_006c[0x01]; // 0x006C
    uint32_t system_ctrl;      // 0x0070
    uint32_t __pad_0074[0x03]; // 0x0074
    uint32_t trace_ctrl;       // 0x0080
    uint32_t __pad_0084[0x03]; // 0x0084
    uint32_t export_ctrl;      // 0x0090
    uint32_t __pad_0094[0x1B]; // 0x0094
    uint32_t dpll_ctrl;        // 0x0100
    uint32_t __pad_0104[0x07]; // 0x0104
    uint32_t em01_a_ctrl;      // 0x0120
    uint32_t __pad_0124[0x01]; // 0x0124
    uint32_t em01_c_ctrl;      // 0x0128
    uint32_t __pad_012c[0x05]; // 0x012C
    uint32_t em23_a_ctrl;      // 0x0140
    uint32_t __pad_0144[0x07]; // 0x0144
    uint32_t em4x_a_ctrl;      // 0x0160
    uint32_t __pad_0164[0x07]; // 0x0164
    uint32_t iadc_ctrl;        // 0x0180
    uint32_t __pad_0184[0x1F]; // 0x0184
    uint32_t watchdog_0_ctrl;  // 0x0200
    uint32_t __pad_0204[0x01]; // 0x0204
    uint32_t watchdog_1_ctrl;  // 0x0208
    uint32_t __pad_020c[0x05]; // 0x020C
    uint32_t eusart_ctrl;      // 0x0220
    uint32_t __pad_0224[0x07]; // 0x0224
    uint32_t sysrtc_ctrl;      // 0x0240
    uint32_t __pad_0244[0x07]; // 0x0244
    uint32_t vdac_0_ctrl;      // 0x0260
    uint32_t __pad_0264[0x03]; // 0x0264
    uint32_t pcnt_ctrl;        // 0x0270
    uint32_t __pad_0274[0x03]; // 0x0274
    uint32_t radio_ctrl;       // 0x0280
    uint32_t __pad_0284[0x04]; // 0x0284
    uint32_t vdac_1_ctrl;      // 0x0294
};

// === globals

extern volatile mg24_hfxo_t  * const mg24_hfxo;
extern volatile mg24_hfrco_t * const mg24_hfrco;
extern volatile mg24_dpll_t  * const mg24_dpll;
extern volatile mg24_lfxo_t  * const mg24_lfxo;
extern volatile mg24_lfrco_t * const mg24_lfrco;

extern volatile mg24_cm_unit_t * const mg24_cm_unit;

// === functions ===

void mg24_clocks_init(void);

#endif
