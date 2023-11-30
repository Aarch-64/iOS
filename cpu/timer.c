#include <timer.h>
#include <isr.h>
#include <io.h>

uint32_t tick = 0;
volatile unsigned long wait_ticks = 0;

#define UNUSED(x) (void)(x)

static void timer_callback(registers_t *regs) {
    tick++;
    wait_ticks++;
    UNUSED(regs);
}

void timer_wait(int ticks)
{
    wait_ticks = 0;
    while(wait_ticks <= ticks);
}

void init_timer(uint32_t freq) {
    /* Install the function we just wrote */
    register_interrupt_handler(IRQ0, timer_callback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    uint32_t divisor = 1193180 / freq;
    uint8_t low  = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)( (divisor >> 8) & 0xFF);
    /* Send the command */
    outb(0x43, 0x36); /* Command port */
    outb(0x40, low);
    outb(0x40, high);
}
