/*
 * EBike Smart Controller
 *
 * Copyright (C) Jorge Pinto aka Casainho, 2012.
 *
 *   casainho [at] gmail [dot] com
 *     www.casainho.net
 *
 * Released under the GPL License, Version 3
 */

#include "lpc210x.h"
#include "system.h"
#include "isrsupport.h"
#include "timers.h"
#include "pwm.h"
#include "main.h"
#include "config.h"
#include "ios.h"
#include "adc.h"
#include "bldc_hall.h"
#include "motor.h"

void initialize (void)
{
  system_init (); // initialize the LPC2103 (clocks, flash memory, etc)
  ios_init (); // configure IO pins
  while (switch_is_set ()) ; // wait
  adc_init (CURRENT); // init the ADC for current measure
  adc_init (VOLTAGE); // init the ADC for current measure
  pwm_init (); // initialize PWM (uses timer1) (PWM output pins will be disable)
  timer0_capture_init (); // intialize Timer0, use it for capture the BEMF sensors signal time and BLDC control
  timer3_init (); // intialize timer3 (used for delay function)
  enableIRQ (); // enable interrupts
}

int main (void)
{
  static unsigned int duty_cycle = 500;
  static unsigned int sector = 1;
  static float current;

  initialize ();

  //motor_start (); // initialize the needed interrupt and sets the outpus as needed
  motor_set_current_max (3); // max average current of 3 amps

  while (1)
  {
    //motor_current_control (duty_cycle); // keep controlling the max current

    phase_a_full ();
    current = delay_with_current_control (100000, 8);

    // dead time
    commutation_disable ();
    delay_us (25);

    delay_us (333000);

    phase_b_full ();
    current = delay_with_current_control (100000, 8);

    // dead time
    commutation_disable ();
    delay_us (25);

    delay_us (333000);


    phase_c_full ();
    current = delay_with_current_control (100000, 8);

    // dead time
    commutation_disable ();
    delay_us (25);

    delay_us (333000);
  }
}

