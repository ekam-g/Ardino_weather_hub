#include <xCore.h>
#include <xSL01.h>
#include <xSW01.h>


xSW01 SW01;
xSL01 SL01;
float low_pa = 100000000000000000000;

void setup() {
	// Start the Serial Monitor
	Serial.begin(115200);
	
	// Set the I2C Pins for CW01
	#ifdef ESP8266
	  Wire.pins(2, 14);
	  Wire.setClockStretchLimit(15000);
	#endif
	
	Wire.begin();
	SW01.begin();                   
	SL01.begin();

	delay(1000);
	
	Serial.println("================================");
	Serial.println(" Started  ");
	Serial.println("================================"); 
}

void loop() {
	float uv;
	uv = 0;
  float ub;
  ub = 0;
  

	SL01.poll();
  delay(2000);
  SW01.poll();                   
  
	uv = SL01.getUVA();
	Display("UVA Intersity(uW/m^2): " , String(uv));

	uv = SL01.getUVB();
	Display("UV Index: " , String(uv));

	ub = SL01.getUVIndex();
	Display("UVB Index: " , String(ub));

  float vals = SW01.getPressure();
  lowest(vals);
  Display("Pressure(pa)" , String(vals));
	delay(500);
}

void lowest(int cool) {
  if (cool < low_pa) {
    low_pa = cool;
  }
  Display("Lowest Pressure(pa)" , String(low_pa));
}


void Display( String title , String what){
  Serial.println(title);
  Serial.print(what);
}

 