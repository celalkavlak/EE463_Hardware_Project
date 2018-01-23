  int spd_desired=127,output;
  int spd,err;
  int errpre;
  int spd_integr=0;
  int spd_deriv;
  int Kp=0,Kd=0,Ki=0;
  
  void setup() {
  pinMode(9,OUTPUT);
  pinMode(A5,INPUT);
  
  digitalWrite(9,LOW);
  setPwmFrequency(9,1024);
  spd=analogRead(A5);
  err = spd_desired - spd;
}

void loop() {

  if(digitalRead(3))
  {
    time1=micros();
    time2=time1;
    period=time1-time2;
      errpre = err;  
  spd=analogRead(A5);
  err = spd_desired - spd;
  spd_deriv = err - errpre;
  spd_integr += err;
  
  output = Ki*spd_integr + Kd*spd_deriv + Kp*err;
}



void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
        TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
