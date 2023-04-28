#include <AmperkaServo.h>
#include "IRremote.h"
int irpin = 10;
int speed = 120;
int red1 = 3;
int red2 = 4;
int yellow1 = 5;
int yellow2 = 6;
int green1 = 11;
int green2 = 12;

IRrecv irrecv(irpin);
decode_results results;
AmperkaServo servol, servor;

bool LSERVOON = false;
bool RSERVOON = false;
bool LEDON = false;
bool TRAFFIC = false;
bool PATTERN = false;

void setup() {
  Serial.begin(9600);

  pinMode(red1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(green1, OUTPUT);
  pinMode(green2, OUTPUT);
  servol.attach(8);
  servor.attach(9);
  irrecv.enableIRIn();
}

void RedPhase() {
  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);
  delay(24000);
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  delay(500);
  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);
  delay(500);
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  delay(500);
  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);
  delay(500);
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  delay(500);
  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);
  delay(500);
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
}

void YellowPhase() {
  digitalWrite(yellow1, HIGH);
  digitalWrite(yellow2, HIGH);
  delay(3000);
  digitalWrite(yellow1, LOW);
  digitalWrite(yellow2, LOW);
}

void GreenPhase() {
  digitalWrite(green1, HIGH);
  digitalWrite(green2, HIGH);
  delay(21000);
  digitalWrite(green1, LOW);
  digitalWrite(green2 ,LOW);
  delay(500);
  digitalWrite(green1, HIGH);
  digitalWrite(green2, HIGH);
  delay(500);
  digitalWrite(green1, LOW);
  digitalWrite(green2, LOW);
  delay(500);
  digitalWrite(green1, HIGH);
  digitalWrite(green2, HIGH);
  delay(500);
  digitalWrite(green1, LOW);
  digitalWrite(green2, LOW);
  delay(500);
  digitalWrite(green1, HIGH);
  digitalWrite(green2, HIGH);
  delay(500);
  digitalWrite(green1, LOW);
  digitalWrite(green2, LOW);
}

// Режим светофора
void TrafficLightMode() {
  RedPhase();
  YellowPhase();
  GreenPhase();
  YellowPhase();
}

void TURN_OFF_LIGHTS() {
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  digitalWrite(yellow1, LOW);
  digitalWrite(yellow2, LOW);
  digitalWrite(green1, LOW);
  digitalWrite(green2, LOW);
}

void PatternsMode () {
  int i;
  for(i = 0; i < 5; i++) {
  digitalWrite(red1, HIGH);
  delay(100);
  digitalWrite(red2, HIGH);
  delay(100);
  digitalWrite(yellow1, HIGH);
  delay(100);
  digitalWrite(yellow2, HIGH);
  delay(100);
  digitalWrite(green1, HIGH);
  delay(100);
  digitalWrite(green2, HIGH);
  delay(100);

  digitalWrite(red1, LOW);
  delay(100);
  digitalWrite(red2, LOW);
  delay(100);
  digitalWrite(yellow1, LOW);
  delay(100);
  digitalWrite(yellow2, LOW);
  delay(100);
  digitalWrite(green1, LOW);
  delay(100);
  digitalWrite(green2, LOW);
  delay(100);
  }

  for(i = 0; i < 5; i++) {
  digitalWrite(yellow1, HIGH);
  digitalWrite(yellow2, HIGH);
  delay(100);
  digitalWrite(red2, HIGH);
  digitalWrite(green1, HIGH);
  delay(100);
  digitalWrite(red1, HIGH);
  digitalWrite(green2, HIGH);
  delay(100);

  digitalWrite(yellow1, LOW);
  digitalWrite(yellow2, LOW);
  delay(100);
  digitalWrite(red2, LOW);
  digitalWrite(green1, LOW);
  delay(100);
  digitalWrite(red1, LOW);
  digitalWrite(green2, LOW);
  delay(100);
  }

  for(i = 0; i < 5; i++) {
    digitalWrite(green2, HIGH);
    delay(100);
    digitalWrite(red1, HIGH);
    delay(100);
    digitalWrite(green1, HIGH);
    delay(100);
    digitalWrite(red2, HIGH);
    delay(100);
    digitalWrite(yellow2, HIGH);
    delay(100);
    digitalWrite(yellow1, HIGH);
    delay(100);
    
    digitalWrite(green2, LOW);
    delay(100);
    digitalWrite(red1, LOW);
    delay(100);
    digitalWrite(green1, LOW);
    delay(100);
    digitalWrite(red2, LOW);
    delay(100);
    digitalWrite(yellow2, LOW);
    delay(100);
    digitalWrite(yellow1, LOW);
    delay(100);
  }
}

void loop() {
  
  // управление с пульта
  if (irrecv.decode( & results )) {
    Serial.println(results.value, HEX);
    
    
    // Вперед
    if(results.value == 0xFF18E7) {
      if(!LSERVOON) {
        servol.writeSpeed(+speed);
        servor.writeSpeed(-speed);
        LSERVOON = true;
        RSERVOON = true;
      }
      else if(LSERVOON) {
        servol.writeSpeed(0);
        servor.writeSpeed(0);
        LSERVOON = false;
        RSERVOON = false;
      }
    }

    // Назад
    else if(results.value == 0xFF4AB5) {
      if(!LSERVOON) {
        servol.writeSpeed(-speed);
        servor.writeSpeed(+speed);
        LSERVOON = true;
        RSERVOON = true;
      }
      else if(LSERVOON) {
        servol.writeSpeed(0);
        servor.writeSpeed(0);
        LSERVOON = false;
        RSERVOON = false;
      }
    }

    // Влево
    if(results.value == 0xFF10EF) {
      if(!LSERVOON) {
        servol.writeSpeed(+speed);
        servor.writeSpeed(+speed);
        LSERVOON = true;
        RSERVOON = true;
      }
      else if(LSERVOON) {
        servol.writeSpeed(0);
        servor.writeSpeed(0);
        LSERVOON = false;
        RSERVOON = false;
      }
    }

    // Вправо
    if(results.value == 0xFF5AA5) {
      if(!LSERVOON) {
        servol.writeSpeed(-speed);
        servor.writeSpeed(-speed);
        LSERVOON = true;
        RSERVOON = true;
      }
      else if(LSERVOON) {
        servol.writeSpeed(0);
        servor.writeSpeed(0);
        LSERVOON = false;
        RSERVOON = false;
      }
    }

  }
  PatternsMode();
  irrecv.resume();

}
void yield() {
  // управление с пульта
  if (irrecv.decode( & results )) {
    Serial.println(results.value, HEX);
    
    
    // Вперед
    if(results.value == 0xFF18E7) {
      if(!LSERVOON) {
        servol.writeSpeed(+speed);
        servor.writeSpeed(-speed);
        LSERVOON = true;
        RSERVOON = true;
      }
      else if(LSERVOON) {
        servol.writeSpeed(0);
        servor.writeSpeed(0);
        LSERVOON = false;
        RSERVOON = false;
      }
    }

    // Назад
    else if(results.value == 0xFF4AB5) {
      if(!LSERVOON) {
        servol.writeSpeed(-speed);
        servor.writeSpeed(+speed);
        LSERVOON = true;
        RSERVOON = true;
      }
      else if(LSERVOON) {
        servol.writeSpeed(0);
        servor.writeSpeed(0);
        LSERVOON = false;
        RSERVOON = false;
      }
    }

    // Влево
    if(results.value == 0xFF10EF) {
      if(!LSERVOON) {
        servol.writeSpeed(+speed);
        servor.writeSpeed(+speed);
        LSERVOON = true;
        RSERVOON = true;
      }
      else if(LSERVOON) {
        servol.writeSpeed(0);
        servor.writeSpeed(0);
        LSERVOON = false;
        RSERVOON = false;
      }
    }

    // Вправо
    if(results.value == 0xFF5AA5) {
      if(!LSERVOON) {
        servol.writeSpeed(-speed);
        servor.writeSpeed(-speed);
        LSERVOON = true;
        RSERVOON = true;
      }
      else if(LSERVOON) {
        servol.writeSpeed(0);
        servor.writeSpeed(0);
        LSERVOON = false;
        RSERVOON = false;
      }
    }


  irrecv.resume();
  }

}

