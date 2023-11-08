#include "main.h"

/* Prototypes of helper functions */
static void display_time(uint32_t time);
static void display_message(String s);
static void display_clear(void);
static void do_beep(void);

/* Prototypes of state handlers */
static event_status_t protimer_state_handler_IDLE(protimer_t *const mobj, event_t const *const e);
static event_status_t protimer_state_handler_TIME_SET(protimer_t *const mobj, event_t const *const e);

void protimer_init(protimer_t *mobj) {
    mobj->active_state = IDLE;
    mobj->pro_time = 0;
}

static event_status_t protimer_state_machine(protimer_t * const mobj, event_t const *const e) {
    switch (mobj->active_state)
    {
    case IDLE:
        return protimer_state_handler_IDLE(mobj, e);    
    case TIME_SET:
        return protimer_state_handler_TIME_SET(mobj, e);

    }
}

/****************************** State Handlers *******************************/

static event_status_t protimer_state_handler_IDLE(protimer_t *const mobj, event_t const *const e) {
    switch (e->sig)
    {
        case ENTRY:
            mobj->curr_time = 0;
            mobj->elapsed_time = 0;
            display_time(0);
            display_message("Set time");
            return EVENT_HANDLED;

        case EXIT:
            display_clear();
            return EVENT_HANDLED;

        case INC_TIME:
            mobj->curr_time += 60;
            mobj->active_state = TIME_SET;
            return EVENT_TRANSITION;


        case START_PAUSE:
            mobj->active_state = STAT;
            return EVENT_TRANSITION;

        case TIME_TICK:
            if (((protimer_tick_event_t *)(e))->ss == 5) {
                do_beep();
                return EVENT_HANDLED;
            }
            else {
                return EVENT_IGNORED;
            }
    } /* End of switch */

    /* Event ignored by default */
    return EVENT_IGNORED;
}

static event_status_t protimer_state_handler_TIME_SET(protimer_t *const mobj, event_t const *const e) {
    /* Event ignored by default */
    return EVENT_IGNORED;
}

/****************************** Helper Functions *****************************/

static void display_time(uint32_t time) {
    char buf[7];
    String time_msg;

    uint16_t m = time / 60;
    uint8_t s = time % 60;
    sprintf(buf, "%03d:%02d", m, s);

    time_msg = (String)buf;
    //lcd_set_cursor(5, 0);
    //lcd_print_string(time_msg);
}

static void display_message(String s) {
}

static void display_clear(void) {
    //lcd_clear();
}

static void do_beep(void) {
    //tone(PIN_BUZZER, 4000, 25);
}