#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

/* Signals of the application */
typedef enum {
    INC_TIME,
    DEC_TIME,
    TIME_TICK,
    START_PAUSE,
    ABRT,
    /* Internal activity signals */
    ENTRY,
    EXIT
} protimer_signal_t;

/* States of the application */
typedef enum {
    IDLE,
    TIME_SET,
    COUNTDOWN,
    PAUSE,
    STAT
} protimer_state_t;

/* Main application structure */
typedef struct {
    uint32_t curr_time;
    uint32_t elapsed_time;
    uint32_t pro_time;
    protimer_state_t active_state;
} protimer_t;

/* Generic (supter) event structure */
typedef struct {
    uint8_t sig;
} event_t;

/* User generated events */
typedef struct {
    event_t super;
} protimer_user_event_t;

/* Tick event */
typedef struct {
    event_t super;
    uint8_t ss;     /* Sub-seconds */
} protimer_tick_event_t;

/* Function prototyes */
void protimer_init(protimer_t *mobj);

#endif /* MAIN_H */
