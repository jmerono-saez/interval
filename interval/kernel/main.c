#include <interval/kernel/main.h>

#include <interval/kernel/logger.h>
#include <interval/kernel/page.h>

[[noreturn]]
void main(const boot_params_t * params) {
    l_print(params->putc, "Hello from %s()!\n", __func__);
    while (true);
}
