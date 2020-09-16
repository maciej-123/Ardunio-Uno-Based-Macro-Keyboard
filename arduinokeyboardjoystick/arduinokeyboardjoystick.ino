//joystick
int JX = A2;
int JY = A1;
int BTN = A0;

//keys
int B1_ = 2;
int B2_ = 3;
int B3_ = 4;
int B4_ = 5;
int B5_ = 6;
int B6_ = 7;
int B7_ = 8;
int B8_ = 9;
int B9_ = 10;

void setup() {
  // put your setup code here, to run once:
  
  //joystick
  pinMode(JX, INPUT);
  pinMode(JY, INPUT);
  pinMode(BTN, INPUT);

  //keys
  pinMode(B1_, INPUT);
  pinMode(B2_, INPUT);
  pinMode(B3_, INPUT);
  pinMode(B4_, INPUT);
  pinMode(B5_, INPUT);
  pinMode(B6_, INPUT);
  pinMode(B7_, INPUT);
  pinMode(B8_, INPUT);
  pinMode(B9_, INPUT);
  Serial.begin(38400);
}

//joystick
int xval = 0;
int yval = 0;
int bval = 0;

//keys
int b1 = 0;
int b2 = 0;
int b3 = 0;
int b4 = 0;
int b5 = 0;
int b6 = 0;
int b7 = 0;
int b8 = 0;
int b9 = 0;

void read_values();
void size_correction();
void print_values();

void loop() {

  String info;
  info = Serial.readStringUntil('\n');
  
  read_values();
  size_correction();
  print_values();
  
}


void read_values()
{
    //joystick
  xval = analogRead(JX);
  yval = analogRead(JY);
  bval = analogRead(BTN);

  //keys
  b1 = digitalRead(B1_);
  b2 = digitalRead(B2_);
  b3 = digitalRead(B3_);
  b4 = digitalRead(B4_);
  b5 = digitalRead(B5_);
  b6 = digitalRead(B6_);
  b7 = digitalRead(B7_);
  b8 = digitalRead(B8_);
  b9 = digitalRead(B9_);   
}

void size_correction()
{
  //zero pos adjust
  xval-=524;
  yval-=495;

  //max limit adjust
  if(xval > 495)
  {
    xval = 495;
  }
  if(xval < -495)
  {
    xval = -495;
  }
  if(yval > 495)
  {
    yval = 495;
  }
  if(yval < -495)
  {
    yval = -495;
  }

  //stable stop at rest position(cutout random fluctuations
  if(xval > -35 && xval < 35)
  {
    xval = 0;
  }
  if(yval > -35 && yval < 35)
  {
    yval = 0;
  } 

  //button adjust
  if(bval == 0)
  {
    bval = 1;
  }
  else
  {
    bval = 0;
  }

}

void print_values()
{    
  //joystick
  Serial.print("BJ:");
  Serial.println(bval);

  Serial.print("XJ:");
  if(xval >= 0){Serial.print("+");}
  if(xval < 0){xval *= -1; Serial.print("-");}
  if(xval < 10){Serial.print("0");}
  if(xval < 100){Serial.print("0");}
  Serial.println(xval);

  Serial.print("YJ:");
  if(yval >= 0){Serial.print("+");}
  if(yval < 0){yval *= -1; Serial.print("-");}
  if(yval < 10){Serial.print("0");}
  if(yval < 100){Serial.print("0");}
  Serial.println(yval);
 
  //keys
  Serial.print("B1:");
  Serial.println(b1);
  Serial.print("B2:");
  Serial.println(b2);
  Serial.print("B3:");
  Serial.println(b3);
  Serial.print("B4:");
  Serial.println(b4);
  Serial.print("B5:");
  Serial.println(b5);
  Serial.print("B6:");
  Serial.println(b6);
  Serial.print("B7:");
  Serial.println(b7);
  Serial.print("B8:");
  Serial.println(b8);
  Serial.print("B9:");
  Serial.println(b9);
}
