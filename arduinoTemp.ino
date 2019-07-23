// Voltage is read between the NTC and another resistor of known resistance
int ThermistorPin[3] = {A0,A1,A2};
float V1;

// Input to the voltage divider; known from the Arduino 5V pin
float Vin = 5.0;

// Known resistance for voltage divider
float R0 = 10000.;

float logR1, R1;
float R01 = 10980.;
float c2 = 295.95;
float T[3];
float c1 = 298.15, b1=3070., b2 = 3380.;

void setup() {
Serial.begin(9600);
}
void gettemp(){
    // analogRead gives a scaled value between 0 and 1023
    V1=(5./1023.0)*analogRead(ThermistorPin[0]);
    R1 = R0 * (Vin/V1 - 1.0);
    logR1 = log(R1/R0);
    T[0] = (1.0 / (1/c1 + ((1/3435.)*logR1)))-273.15;
    
    V1=(5./1023.0)*analogRead(ThermistorPin[1]);
    R1 = R0 * (Vin/V1 - 1.0);
    logR1 = log(R1/R0);
    T[1] = (1.0 / (1/c1 + ((1/b1)*logR1)))-273.15;
    
    //V1=(5./1023.0)*analogRead(ThermistorPin[2]);
    //R1 = R0 * (Vin/V1 - 1.0);
    //logR1 = log(R1/R0);
    //T[2] = (1.0 /(1/c1 + ((1/b2)*logR1))) - 273.15;
}

void loop() {
  gettemp();
  Serial.print(T[0]);
  Serial.print(" ");
  Serial.print(T[1]);
  Serial.print("\n");
  delay(100);
}

