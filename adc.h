/*
 * adc.h
 *
 *  Created on: Oct 2, 2024
 *      Author: samaa
 */

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023 	/* According to the number of bits of the chosen ADC */
#define ADC_REF_VOLT_VALUE   2.56		/* According to the chosen/applied reference volt */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Definition: This function shall initialize the adc driver with the required standards
 */
void ADC_init(void);

/*
 * Definition: This function shall read the analog data of the chosen channel of the ADC,
 * then return it's digital value that will be handled later.
 */
uint16 ADC_readChannel(uint8 ch_num);


#endif /* ADC_H_ */
