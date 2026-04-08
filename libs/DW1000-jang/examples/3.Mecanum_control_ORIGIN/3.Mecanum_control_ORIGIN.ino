int LEFT_FRONT_PWM = 5; // motor 1 speed (0~255) -- LEFT FRONT WHEEL
int LEFT_FRONT_DIR = 4; // motor 1 direction (0 or 1)

int RIGHT_FRONT_PWM = 6; // motor 2 speed (0~255) -- RIGHT FRONT WHEEL
int RIGHT_FRONT_DIR = A1; // motor 2 direction (0 or 1)

int RIGHT_BACK_PWM = 9; // motor 3 speed (0~255) -- RIGHT BACK WHEEL
int RIGHT_BACK_DIR = 8; // motor 3 direction (0 or 1)

int LEFT_BACK_PWM = 3; // motor 4 speed (0~255) -- LEFT BACK WHEEL
int LEFT_BACK_DIR = A2; // motor 4 direction (0 or 1)


void setup() {

  pinMode(LEFT_FRONT_DIR, OUTPUT);
  pinMode(RIGHT_FRONT_DIR, OUTPUT);
  pinMode(RIGHT_BACK_DIR, OUTPUT);
  pinMode(LEFT_BACK_DIR, OUTPUT);

  pinMode(LEFT_FRONT_PWM, OUTPUT);
  pinMode(RIGHT_FRONT_PWM, OUTPUT);
  pinMode(RIGHT_BACK_PWM, OUTPUT);
  pinMode(LEFT_BACK_PWM, OUTPUT);

}

void North() 
{
  analogWrite(LEFT_FRONT_PWM, 40);  
  digitalWrite(LEFT_FRONT_DIR, HIGH);

  analogWrite(RIGHT_FRONT_PWM, 40);  
  digitalWrite(RIGHT_FRONT_DIR, LOW);

  analogWrite(RIGHT_BACK_PWM, 40);  
  digitalWrite(RIGHT_BACK_DIR, HIGH);

  analogWrite(LEFT_BACK_PWM, 40);  
  digitalWrite(LEFT_BACK_DIR, LOW);

}

void South() // HIGH IS FORWOARD
{
  analogWrite(LEFT_FRONT_PWM, 40);  
  digitalWrite(LEFT_FRONT_DIR, LOW);

  analogWrite(RIGHT_FRONT_PWM, 40);  
  digitalWrite(RIGHT_FRONT_DIR, HIGH);

  analogWrite(RIGHT_BACK_PWM, 40);  
  digitalWrite(RIGHT_BACK_DIR, LOW);

  analogWrite(LEFT_BACK_PWM, 40);  
  digitalWrite(LEFT_BACK_DIR, HIGH);
}

void East() // 좌측 앞바퀴, 우측 뒷바퀴 정방향, 우측 앞바퀴, 좌측 뒷바퀴 역방향
{
  analogWrite(LEFT_FRONT_PWM, 40);  
  digitalWrite(LEFT_FRONT_DIR, HIGH);

  analogWrite(RIGHT_FRONT_PWM, 40);  
  digitalWrite(RIGHT_FRONT_DIR, HIGH);

  analogWrite(RIGHT_BACK_PWM, 40);  
  digitalWrite(RIGHT_BACK_DIR, HIGH);

  analogWrite(LEFT_BACK_PWM, 40);  
  digitalWrite(LEFT_BACK_DIR, HIGH);
  
}

void West() // 좌측 앞바퀴, 우측 뒷바퀴 역방향, 우측 앞바퀴, 좌측 뒷바퀴 정방향
{
  analogWrite(LEFT_FRONT_PWM, 40);  
  digitalWrite(LEFT_FRONT_DIR, LOW);

  analogWrite(RIGHT_FRONT_PWM, 40);  
  digitalWrite(RIGHT_FRONT_DIR, LOW);

  analogWrite(RIGHT_BACK_PWM, 40);  
  digitalWrite(RIGHT_BACK_DIR, LOW);

  analogWrite(LEFT_BACK_PWM, 40);  
  digitalWrite(LEFT_BACK_DIR, LOW);
  
}
void NorthWest() // 우측 앞바퀴, 좌측 뒷바퀴 구동, 북서쪽
{
  analogWrite(LEFT_FRONT_PWM, 0);  

  analogWrite(RIGHT_FRONT_PWM, 40);  
  digitalWrite(RIGHT_FRONT_DIR, HIGH);

  analogWrite(RIGHT_BACK_PWM, 0);  

  analogWrite(LEFT_BACK_PWM, 40);  
  digitalWrite(LEFT_BACK_DIR, HIGH);

}

void SouthEast() // 우측 앞바퀴, 좌측 뒷바퀴 역방향 구동, 남동쪽 
{
  analogWrite(LEFT_FRONT_PWM, 0);  

  analogWrite(RIGHT_FRONT_PWM, 40);  
  digitalWrite(RIGHT_FRONT_DIR, LOW);

  analogWrite(RIGHT_BACK_PWM, 0);  

  analogWrite(LEFT_BACK_PWM, 40);  
  digitalWrite(LEFT_BACK_DIR, LOW);

}

void NorthEast() // 좌측 앞바퀴, 우측 뒷바퀴 구동, 북동쪽
{
  analogWrite(LEFT_FRONT_PWM, 40);  
  digitalWrite(LEFT_FRONT_DIR, HIGH);

  analogWrite(RIGHT_FRONT_PWM, 0);  

  analogWrite(RIGHT_BACK_PWM, 40);  
  digitalWrite(RIGHT_BACK_DIR, HIGH);

  analogWrite(LEFT_BACK_PWM, 0);  

}

void SouthWest() // 좌측 앞바퀴, 우측 뒷바퀴 역방향 구동, 남서쪽
{
  analogWrite(LEFT_FRONT_PWM, 40);  
  digitalWrite(LEFT_FRONT_DIR, LOW);

  analogWrite(RIGHT_FRONT_PWM, 0);  

  analogWrite(RIGHT_BACK_PWM, 40);  
  digitalWrite(RIGHT_BACK_DIR, LOW);

  analogWrite(LEFT_BACK_PWM, 0);  

}

void Stop()
{
  analogWrite(RIGHT_FRONT_PWM, 0);  
  analogWrite(RIGHT_BACK_PWM, 0);  
  analogWrite(LEFT_BACK_PWM, 0);  
  analogWrite(LEFT_FRONT_PWM, 0);  

}

void loop() {
  East();
  delay(1000);

  North();
  delay(1000);

  West();
  delay(1000);

  South();
  delay(1000);

  NorthEast();
  delay(1000);

  SouthWest();
  delay(1000);

  NorthWest();
  delay(1000);

  SouthEast();
  delay(1000);
}
