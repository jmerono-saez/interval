#ifndef __INTERVAL_LW_EFR32MG24_REGISTERS_H__
#define __INTERVAL_LW_EFR32MG24_REGISTERS_H__

// === constants ===

enum : long {
    mg24_cmu_ip_version          = 0x0000,
    mg24_cmu_status              = 0x0008,
    mg24_cmu_lock                = 0x0010,
    mg24_cmu_wdog_lock           = 0x0014,
    mg24_cmu_interrupt_flag      = 0x0020,
    mg24_cmu_interrupt_enable    = 0x0024,
    mg24_cmu_calibrate_command   = 0x0050,
    mg24_cmu_calibrate_ctrl      = 0x0054,
    mg24_cmu_calibrate_result    = 0x0058,
    mg24_cmu_clock_enable_0      = 0x0064,
    mg24_cmu_clock_enable_1      = 0x0068,
    mg24_cmu_system_clock_ctrl   = 0x0070,
    mg24_cmu_debug_clock_ctrl    = 0x0080,
    mg24_cmu_export_clock_ctrl   = 0x0090,
    mg24_cmu_dpll_clock_ctrl     = 0x0100,
    mg24_cmu_em_0_1_group_a_ctrl = 0x0120,
    mg24_cmu_em_0_1_group_c_ctrl = 0x0128,
    mg24_cmu_em_2_3_group_a_ctrl = 0x0140,
    mg24_cmu_em_4_group_a_ctrl   = 0x0160,
    mg24_cmu_iadc_clock_ctrl     = 0x0180,
    mg24_cmu_wdog_0_clock_ctrl   = 0x0200,
    mg24_cmu_wdog_1_clock_ctrl   = 0x0208,
    mg24_cmu_eusart_clock_ctrl   = 0x0220,
    mg24_cmu_rtc_clock_ctrl      = 0x0240,
    mg24_cmu_vdac_0_clock_ctrl   = 0x0260,
    mg24_cmu_pulse_clock_ctrl    = 0x0270,
    mg24_cmu_radio_clock_ctrl    = 0x0280,
    mg24_cmu_vdac_1_clock_ctrl   = 0x0294,
};

// === functions ===

void mg24_write();
void mg24_toggle();

unsigned long mg24_read();

#endif
