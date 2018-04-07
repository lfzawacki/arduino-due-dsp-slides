// Licensed under a Creative Commons Attribution 3.0 Unported License.
// Based on rcarduino.blogspot.com previous work.
// www.electrosmash.com/pedalshield
 
/*chorus_vibrato.ino creates a chorus guitar effect by delaying the signal and
modulating this delay with a triangular waveform.*/
 
int in_ADC0, in_ADC1, out_DAC0, out_DAC1;  //variables for 2 ADCs values (ADC0, ADC1)
int POT0, POT1, POT2; //variables for 3 pots (ADC8, ADC9, ADC10)
int LED = 3;
int FOOTSWITCH = 7; 
int TOGGLE = 2; 
#define MAX_DELAY 500
#define MIN_DELAY 200

uint16_t sDelayBuffer0[MAX_DELAY+500];
uint16_t sDelayBuffer1[MAX_DELAY+500];
unsigned int DelayCounter = 0;
unsigned int Delay_Depth = 300;
unsigned int count_up=1;
int p;

unsigned int depth = 0;

int depthSum = 1;

unsigned int updateCounter = 0;
 
void setup()
{
  //turn on the timer clock in the power management controller
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(ID_TC4);
 
  //we want wavesel 01 with RC 
  TC_Configure(TC1,1, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK2);
  TC_SetRC(TC1, 1, 109); // sets <> 44.1 Khz interrupt rate
  TC_Start(TC1, 1);
 
  // enable timer interrupts on the timer
  TC1->TC_CHANNEL[1].TC_IER=TC_IER_CPCS;
  TC1->TC_CHANNEL[1].TC_IDR=~TC_IER_CPCS;
 
  //Enable the interrupt in the nested vector interrupt controller 
  //TC4_IRQn where 4 is the timer number * timer channels (3) + the channel number 
  //(=(1*3)+1) for timer1 channel1 
  NVIC_EnableIRQ(TC4_IRQn);
 
  //ADC Configuration
  ADC->ADC_MR |= 0x80;   // DAC in free running mode.
  ADC->ADC_CR=2;         // Starts ADC conversion.
  ADC->ADC_CHER=0x1CC0;  // Enable ADC channels 0,1,8,9 and 10  
 
  //DAC Configuration
  analogWrite(DAC0,0);  // Enables DAC0
}
 
void loop()
{
  //Read the ADCs
  while((ADC->ADC_ISR & 0x1CC0)!=0x1CC0);// wait for ADC 0, 1, 8, 9, 10 conversion complete.
  in_ADC0=ADC->ADC_CDR[7];               // read data from ADC0
}
 
//Interrupt at 44.1KHz rate (every 22.6us)
void TC4_Handler()
{
  //Clear status allowing the interrupt to be fired again.
  TC_GetStatus(TC1, 1);
 
  //Store current readings  
  sDelayBuffer0[DelayCounter] = in_ADC0;
 
  updateCounter++;

  if (updateCounter % (44100/400) == 0) {
    depth += depthSum;
  }

  if (depth > 1024) {
    depthSum = -1;
  }

  if (depth <= 0) {
    depthSum = 1;
  }

  //Adjust Delay Depth based in pot0 position.
  POT0=map(POT0>>2,0,1024,1,25); //25 empirically chosen
 
  DelayCounter++;
  if(DelayCounter >= Delay_Depth) 
  {
    DelayCounter = 0; 
    if(count_up)
    {
       digitalWrite(LED, HIGH);
       for(p=0;p<POT0+1;p++) 
       sDelayBuffer0[Delay_Depth+p]=sDelayBuffer0[Delay_Depth-1]; 
       Delay_Depth=Delay_Depth+POT0;
       if (Delay_Depth>=MAX_DELAY)count_up=0;
    }
    else
    {
       digitalWrite(LED, LOW); 
       Delay_Depth=Delay_Depth-POT0;
       if (Delay_Depth<=MIN_DELAY)count_up=1;
    }
  }
 
  out_DAC0 = sDelayBuffer0[DelayCounter];
 
  //Add volume control based in POT2
  out_DAC0=map(out_DAC0,900,1400,1,2000);
 
  //Write the DACs
  dacc_set_channel_selection(DACC_INTERFACE, 0);       //select DAC channel 0
  dacc_write_conversion_data(DACC_INTERFACE, min(out_DAC0, 4095));//write on DAC
}
