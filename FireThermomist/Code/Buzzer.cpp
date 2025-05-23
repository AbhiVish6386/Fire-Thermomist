#include "Buzzer.h"
Buzzer::Buzzer(int pin){
    buzzerPin=pin;
    pinMode(buzzerPin,OUTPUT);
}
//fucntion definition
void Buzzer::on(){
    digitalWrite(buzzerPin,HIGH);
}
void Buzzer::off(){
    digitalWrite(buzzerPin,LOW);
}
void Buzzer::beep(int duration){
    on();
    delay(duration);
    off();
}