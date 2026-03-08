#ifndef __INTERVAL_LW_EFR32MG24_REGISTERS_H__
#define __INTERVAL_LW_EFR32MG24_REGISTERS_H__

// === constants ===

#define MG24_RADIO_BASE    (void *)(/* TODO */)
#define MG24_FLASH_BASE    (void *)(0x40030000)
#define MG24_CLOCK_BASE    (void *)(0x40008000)
#define MG24_HFRCO_BASE    (void *)(0x40010000)
#define MG24_LFRCO_BASE    (void *)(0x40024000)
#define MG24_FSRCO_BASE    (void *)(0x40018000)
#define MG24_SECURITY_BASE (void *)(0x44008000)
#define MG24_ENERGY_BASE   (void *)(0x40004000)
#define MG24_DCDC_BASE     (void *)(0x40094000)
#define MG24_GPCRC_BASE    (void *)(0x40088000)
#define MG24_LE_TIMER_BASE (void *)(0x49000000)
#define MG24_TIMER_0_BASE  (void *)(0x40048000)
#define MG24_TIMER_1_BASE  (void *)(0x4004C000)
#define MG24_TIMER_2_BASE  (void *)(0x40050000)
#define MG24_TIMER_3_BASE  (void *)(0x40054000)
#define MG24_TIMER_4_BASE  (void *)(0x40058000)
#define MG24_IADC_BASE     (void *)(0x49004000)
#define MG24_GPIO_BASE     (void *)(0x4003C000)
#define MG24_LDMA_BASE     (void *)(0x40040000)
#define MG24_WDOG_0_BASE   (void *)(0x4B004000)
#define MG24_WDOG_1_BASE   (void *)(0x4B008000)
#define MG24_PULSE_BASE    (void *)(0x49030000)
#define MG24_MATRIX_BASE   (void *)(0x4D000000)

enum : long {
    mg24_clock_ip_version          = 0x0000,
    mg24_clock_status              = 0x0008,
    mg24_clock_lock                = 0x0010,
    mg24_clock_wdog_lock           = 0x0014,
    mg24_clock_interrupt_flag      = 0x0020,
    mg24_clock_interrupt_enable    = 0x0024,
    mg24_clock_calibrate_command   = 0x0050,
    mg24_clock_calibrate_ctrl      = 0x0054,
    mg24_clock_calibrate_result    = 0x0058,
    mg24_clock_enable_l            = 0x0064,
    mg24_clock_enable_h            = 0x0068,
    mg24_clock_system_clock_ctrl   = 0x0070,
    mg24_clock_debug_clock_ctrl    = 0x0080,
    mg24_clock_export_clock_ctrl   = 0x0090,
    mg24_clock_dpll_clock_ctrl     = 0x0100,
    mg24_clock_em_0_1_group_a_ctrl = 0x0120,
    mg24_clock_em_0_1_group_c_ctrl = 0x0128,
    mg24_clock_em_2_3_group_a_ctrl = 0x0140,
    mg24_clock_em_4_group_a_ctrl   = 0x0160,
    mg24_clock_iadc_clock_ctrl     = 0x0180,
    mg24_clock_wdog_0_clock_ctrl   = 0x0200,
    mg24_clock_wdog_1_clock_ctrl   = 0x0208,
    mg24_clock_eusart_clock_ctrl   = 0x0220,
    mg24_clock_rt_clock_ctrl       = 0x0240,
    mg24_clock_vdac_0_clock_ctrl   = 0x0260,
    mg24_clock_pulse_clock_ctrl    = 0x0270,
    mg24_clock_radio_clock_ctrl    = 0x0280,
    mg24_clock_vdac_1_clock_ctrl   = 0x0294,
};

enum : long {
    mg24_hfrco_ip_version       = 0x0000,
    mg24_hfrco_ctrl             = 0x0004,
    mg24_hfrco_tuning           = 0x0008,
    mg24_hfrco_status           = 0x000C,
    mg24_hfrco_interrupt_flag   = 0x0010,
    mg24_hfrco_interrupt_enable = 0x0014,
    mg24_hfrco_lock             = 0x001C,
};

enum : long {
    mg24_lfrco_ip_version       = 0x0000,
    mg24_lfrco_ctrl             = 0x0004,
    mg24_lfrco_status           = 0x0008,
    mg24_lfrco_interrupt_flag   = 0x0014,
    mg24_lfrco_interrupt_enable = 0x0018,
    mg24_lfrco_lock             = 0x0020,
    mg24_lfrco_configuration    = 0x0024,
    mg24_lfrco_tuning           = 0x002C,
    mg24_lfrco_tuning_inverted  = 0x0030,
    mg24_lfrco_command          = 0x0034,
};

enum : long {
    mg24_fsrco_ip_version = 0x0000,
};

enum : long {
    mg24_security_ip_version           = 0x0000,
    mg24_security_status               = 0x0004,
    mg24_security_lock                 = 0x0008,
    mg24_security_interrupt_flag       = 0x000C,
    mg24_security_interrupt_enable     = 0x0010,
    mg24_security_cortex_m33_ctrl      = 0x0020,
    mg24_security_pp_privileged_mode_l = 0x0040,
    mg24_security_pp_privileged_mode_h = 0x0044,
    mg24_security_pp_secure_mode_l     = 0x0060,
    mg24_security_pp_secure_mode_h     = 0x0064,
    mg24_security_pp_fault_status      = 0x0140,
    mg24_security_bm_privileged_mode   = 0x0150,
    mg24_security_bm_secure_mode       = 0x0170,
    mg24_security_bm_fault_status      = 0x0250,
    mg24_security_bm_fault_address     = 0x0254,
    mg24_security_region_type_l        = 0x0260,
    mg24_security_region_type_h        = 0x0264,
    mg24_security_boundary_0_1_address = 0x0270,
    mg24_security_boundary_1_2_address = 0x0274,
    mg24_security_boundary_4_5_address = 0x0280,
    mg24_security_boundary_5_6_address = 0x0284,
};

enum : long {
    mg24_le_timer_ip_version       = 0x0000,
    mg24_le_timer_enable           = 0x0004,
    mg24_le_timer_reset            = 0x0008,
    mg24_le_timer_ctrl             = 0x000C,
    mg24_le_timer_command          = 0x0010,
    mg24_le_timer_status           = 0x0014,
    mg24_le_timer_count            = 0x0018,
    mg24_le_timer_compare_0        = 0x001C,
    mg24_le_timer_compare_1        = 0x0020,
    mg24_le_timer_maximum          = 0x0024,
    mg24_le_timer_maximum_buffered = 0x0028,
    mg24_le_timer_repeats_0        = 0x002C,
    mg24_le_timer_repeats_1        = 0x0030,
    mg24_le_timer_interrupt_flag   = 0x0034,
    mg24_le_timer_interrupt_enable = 0x0038,
    mg24_le_timer_lock             = 0x003C,
    mg24_le_timer_sync_busy        = 0x0040,
    mg24_le_timer_reflex_mode      = 0x0050,
};

enum : long {
    mg24_gpio_ip_version           = 0x0000,
    mg24_gpio_port_a_ctrl          = 0x0030,
    mg24_gpio_port_a_mode_l        = 0x0034,
    mg24_gpio_port_a_mode_h        = 0x003C,
    mg24_gpio_port_a_output        = 0x0040,
    mg24_gpio_port_a_input         = 0x0044,
    mg24_gpio_port_b_ctrl          = 0x0060,
    mg24_gpio_port_b_mode_l        = 0x0064,
    mg24_gpio_port_b_mode_h        = 0x006C,
    mg24_gpio_port_b_output        = 0x0070,
    mg24_gpio_port_b_input         = 0x0074,
    mg24_gpio_port_c_ctrl          = 0x0090,
    mg24_gpio_port_c_mode_l        = 0x0094,
    mg24_gpio_port_c_mode_h        = 0x009C,
    mg24_gpio_port_c_output        = 0x00A0,
    mg24_gpio_port_c_input         = 0x00A4,
    mg24_gpio_port_d_ctrl          = 0x00C0,
    mg24_gpio_port_d_mode_l        = 0x00C4,
    mg24_gpio_port_d_mode_h        = 0x00CC,
    mg24_gpio_port_d_output        = 0x00D0,
    mg24_gpio_port_d_input         = 0x00D4,
    mg24_gpio_lock                 = 0x0300,
    mg24_gpio_locked_status        = 0x0310,
    mg24_gpio_bs_a_alloc           = 0x0320,
    mg24_gpio_bs_b_alloc           = 0x0324,
    mg24_gpio_bs_c_d_alloc         = 0x0328,
    mg24_gpio_external_port_l      = 0x0400,
    mg24_gpio_external_port_h      = 0x0404,
    mg24_gpio_external_wire_l      = 0x0408,
    mg24_gpio_external_wire_h      = 0x040C,
    mg24_gpio_external_rise        = 0x0410,
    mg24_gpio_external_fall        = 0x0414,
    mg24_gpio_interrupt_flag       = 0x0420,
    mg24_gpio_interrupt_enable     = 0x0424,
    mg24_gpio_em_4_wakeup_enable   = 0x042C,
    mg24_gpio_em_4_wakeup_polarity = 0x0430,
};

// === functions ===

void mg24_write(void * base, long offset, unsigned long ul);
void mg24_raise(void * base, long offset, unsigned long ul);
void mg24_lower(void * base, long offset, unsigned long ul);
void mg24_flip(void * base, long offset, unsigned long ul);

unsigned long mg24_read(void * base, long offset);

#endif
