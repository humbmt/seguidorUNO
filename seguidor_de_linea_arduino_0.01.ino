
#include <Wire.h>

#define MotorSpeedSet             0x82
#define PWMFrequenceSet           0x84
#define DirectionSet              0xaa
#define MotorSetA                 0xa1
#define MotorSetB                 0xa5
#define Nothing                   0x01
#define EnableStepper             0x1a
#define UnenableStepper           0x1b
#define Stepernu                  0x1c
#define I2CMotorDriverAdd         0x0f  

// Set the address of the I2CMotorDriver
// set the steps you want, if 255, the stepper will rotate continuely;
void SteperStepset(unsigned char stepnu)
{
  Wire.beginTransmission(I2CMotorDriverAdd); // transmit to device I2CMotorDriverAdd
  Wire.write(Stepernu);          // Send the stepernu command
  Wire.write(stepnu);            // send the steps
  Wire.write(Nothing);           // send nothing
  Wire.endTransmission();        // stop transmitting
}

void StepperMotorEnable(unsigned char Direction, unsigned char motorspeed)
{
  Wire.beginTransmission(I2CMotorDriverAdd); // transmit to device I2CMotorDriverAdd
  Wire.write(EnableStepper);        // set pwm header
  Wire.write(Direction);              // send pwma
  Wire.write(motorspeed);              // send pwmb
  Wire.endTransmission();    // stop transmitting
}
//function to uneanble i2C motor drive to drive the stepper.
void StepperMotorUnenable()
{
  Wire.beginTransmission(I2CMotorDriverAdd); // transmit to device I2CMotorDriverAdd
  Wire.write(UnenableStepper);        // set unenable commmand
  Wire.write(Nothing);
  Wire.write(Nothing);
  Wire.endTransmission();    // stop transmitting
}

void MotorSpeedSetAB(unsigned char MotorSpeedA , unsigned char MotorSpeedB)  {
  MotorSpeedA = map(MotorSpeedA, 0, 100, 0, 255);
  MotorSpeedB = map(MotorSpeedB, 0, 100, 0, 255);
  Wire.beginTransmission(I2CMotorDriverAdd); // transmit to device I2CMotorDriverAdd
  Wire.write(MotorSpeedSet);        // set pwm header
  Wire.write(MotorSpeedA);              // send pwma
  Wire.write(MotorSpeedB);              // send pwmb
  Wire.endTransmission();    // stop transmitting
}
//set the prescale frequency of PWM, 0x03 default;
void MotorPWMFrequenceSet(unsigned char Frequence)  {
  Wire.beginTransmission(I2CMotorDriverAdd); // transmit to device I2CMotorDriverAdd
  Wire.write(PWMFrequenceSet);        // set frequence header
  Wire.write(Frequence);              //  send frequence
  Wire.write(Nothing);              //  need to send this byte as the third byte(no meaning)
  Wire.endTransmission();    // stop transmitting
}
//set the direction of DC motor.
void MotorDirectionSet(unsigned char Direction)  {     //  Adjust the direction of the motors 0b0000 I4 I3 I2 I1
  Wire.beginTransmission(I2CMotorDriverAdd); // transmit to device I2CMotorDriverAdd
  Wire.write(DirectionSet);        // Direction control header
  Wire.write(Direction);              // send direction control information
  Wire.write(Nothing);              // need to send this byte as the third byte(no meaning)
  Wire.endTransmission();    // stop transmitting
}

void MotorDriectionAndSpeedSet(unsigned char Direction, unsigned char MotorSpeedA, unsigned char MotorSpeedB)  { //you can adjust the driection and speed together
  MotorDirectionSet(Direction);
  MotorSpeedSetAB(MotorSpeedA, MotorSpeedB);
}
void setup()  {
  Wire.begin(); // join i2c bus (address optional for master)
  delayMicroseconds(10000);
  Serial.begin(9600);
  Serial.println("setup begin");
}

void loop()  {
  // the following code sent commands to motor driver to drive DC motor
  while (1)  {
    Serial.println("sent DC speed 100");
    MotorSpeedSetAB(20, 20); //defines the speed of motor 1 and motor 2;
    delay(10000); //this delay needed
    MotorDirectionSet(0b1010);  //"0b1010" defines the output polarity, "10" means the M+ is "positive" while the M- is "negtive"
    // make sure M+ and M- is different polatity when driving DC motors.
    delay(5000);
    MotorSpeedSetAB(0,0);
    MotorDirectionSet(0b0101);  //0b0101  Rotating in the opposite direction
    delay(5000);
    
  }

}
