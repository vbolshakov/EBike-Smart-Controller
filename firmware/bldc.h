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

void commutation_disable (void);
void commutation_sector (unsigned int sector);
unsigned int rotor_find_position_sector (void);
float delay_with_current_control (unsigned long us, float current_max);
