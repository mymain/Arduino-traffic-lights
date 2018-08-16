void setup() {
  // put your setup code here, to run once:
  pinMode(A1, OUTPUT);//red
  pinMode(A2, OUTPUT);//orange
  pinMode(A3, OUTPUT);//green
}

static unsigned long blinkingOrangeLastTime = 0;
static unsigned long orangeLightPhaseLastTime = 0;
static unsigned long greenOrRedPhaseLastTime = 0;

int phase = 0;

void loop() {
  //handle millis rollover
  unsigned long currentMillis = millis();

  //start with blinking orange light for 10 seconds
  if(phase == 0 && (unsigned long)(currentMillis - blinkingOrangeLastTime) >= 1000) {
      
      blinkingOrangeLastTime += 1000;
      
      digitalWrite(A2, !digitalRead(A2));
     
      //stop blinking after 10 seconds
      if(millis()/1000 > 10) {
        digitalWrite(A2, LOW);
        digitalWrite(A1, HIGH);
        phase = 1;//change phase
      }
  }

  //red and green light states
  if((unsigned long)(currentMillis - greenOrRedPhaseLastTime) >= 2000) {
    greenOrRedPhaseLastTime += 2000;
    switch(phase)
    {
      case 2://green light - go ahead
        digitalWrite(A1, LOW);//turn off red
        digitalWrite(A2, LOW);//turn off green
        digitalWrite(A3, HIGH);//turn on green
        phase = 3;
      break;
      case 4://red light - stop
        digitalWrite(A1, HIGH);//turn on red
        digitalWrite(A2, LOW);//turn off green
        digitalWrite(A3, LOW);//turn off green
        phase = 1;
      break;
    }
  }
  
  if((unsigned long)(currentMillis - orangeLightPhaseLastTime) >= 10000) {
    orangeLightPhaseLastTime += 10000;
    switch(phase)
    {
      case 1://red and yellow - prepare to start
        digitalWrite(A1, HIGH);
        digitalWrite(A2, HIGH);
        digitalWrite(A3, LOW);
        phase = 2;
      break;
      case 3://yellow only - prepare to stop
        digitalWrite(A1, LOW);
        digitalWrite(A2, HIGH);
        digitalWrite(A3, LOW);
        phase = 4;
      break;
    }
  }
}
