// GLOBAL VARIABLES

// LOCATION OF ANALOG PIN USED 
//================================================

int voltSensorPin = A0;

// SETTED EMPTY VARIABLES USED FOR CODING
//================================================

float adcVoltage = 0.00;
float inMilliVolt = 0.00;
float inMilliAmp = 1.00;
int adcValue = 0;

// REFERENCE VALUES
//================================================

// Resistors Values in sensor 
float R1 = 30000.00;
float R2 = 7500.00;
//[] 
// Voltage reference for computing
float refVoltage = 5.00;

// mVolt/mAmp consumed by LED LightBulb
float millivoltPerMilliampArray[2][48]= 
  { 
    {
     7500.00,
     7600.00,
     7800.00,
     7900.00,
     8000.00,
     8100.00,
     8200.00,
     8300.00,
     8400.00,
     8500.00,
     8600.00,
     8700.00,
     8800.00,
     8900.00,
     9000.00,
     9100.00,
     9200.00,
     9000.00,
     9100.00,
     9200.00,
     9300.00,
     9400.00,
     9500.00,
     9600.00,
     9700.00,
     9800.00,
     9900.00,
     10000.00,
     10100.00,
     10200.00,
     10300.00,
     10400.00,
     10500.00,
     10600.00,
     10700.00,
     10800.00,
     10900.00,
     11000.00,
     11100.00,
     11200.00,
     11300.00,
     11400.00,
     11500.00,
     11600.00,
     11700.00,
     11800.00,
     11900.00,
     12000.00
    },
    { 
     0.65,
     0.80,
     1.30,
     1.65,
     2.80,
     5.75,
     8.80,
     11.60,
     14.70,
     20.70,
     22.60,
     33.00,
     40.00,
     52.90,
     60.60,
     70.00,
     79.00,
     60.60,
     70.00,
     79.00,
     93.00,
     109.00,
     127.00,
     131.00,
     158.00,
     173.00,
     186.00,
     245.00,
     260.00,
     270.00,
     270.00,
     270.00,
     270.00,
     270.00,
     270.00,
     270.00,
     270.00,
     250.00,
     250.00,
     250.00,
     250.00,
     235.00,
     235.00,
     220.00,
     220.00,
     220.00,
     220.00,
     200.00}
   };


// SETUP ARDUINO
//================================================

void setup() {
  Serial.begin(9600);
  

}

// LOOP ARDUINO
//================================================

void loop() {

  adcVoltage = getAdcAverageVoltage();
  inMilliVolt = (adcVoltage/(R2 /( R1 + R2)))*1000;

  if(inMilliVolt < millivoltPerMilliampArray[0][0]){
    inMilliAmp = 0.00;
  }else{
    
    for(int i = 0; i < 48 ; i++){
      if(inMilliVolt >= millivoltPerMilliampArray[0][i] && inMilliVolt < millivoltPerMilliampArray[0][i+1]){
        inMilliAmp = millivoltPerMilliampArray[1][i];
        break;
      }else{
        inMilliAmp = millivoltPerMilliampArray[1][47];
      };
    };  
    
  };
 

  Serial.print("mV : ");
  Serial.println(inMilliVolt);
  Serial.print("mAmp : ");
  Serial.println(inMilliAmp);
  Serial.println(" ");

  delay(500);

}


// FUNCTION USED TO CREATE ADC AVERAGE FOR 1/2sec5
//================================================


float getAdcAverageVoltage(){
  float result;
  float digitalSignal;            
  float maxValue = 0;             
  float minValue = 1024;          
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 500) //sample for 1/2 Sec
   {
       digitalSignal = analogRead(voltSensorPin);
       // see if you have a new maxValue
       if (digitalSignal > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = digitalSignal;

       }
       if (digitalSignal < minValue) 
       {
           /*record the minimum sensor value*/
           minValue = digitalSignal;
       }
   }
   
   // adc voltage average
   result = (((maxValue - minValue)) * refVoltage)/1024.00;
      
   return result;
 };
