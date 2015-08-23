#include <SoftwareSerial.h>
#include "RGB_Char_LCD_Backpack.h"
#include <SPI.h>
#include <Nordic_nRF8001.h>
#include <RBL_nRF8001.h>
#include "iShield.h"

char myPassword[] = { '1', '2', '3', '4', '5', '\0' }; //This is the password of the device
char passwordTyped[6] = {'\0'}; //here we are going to save the typed password
char currentChar;
iShield myiShield;
int cont = 0;
bool matchPass;

void setup() {
  
  lcd_begin();
  lcd_setContrast(200);
  lcd_setBrightness(255);
  lcd_setCursorAtBeginning();
  lcd_clear();
  lcd_print("Type password:  ");
  lcd_setColor(0, 0, 150);
  lcd_blinkCursorOn();
  ble_begin();
  Serial.begin(9600);
  
}

void loop() {
  	
  myiShield.getInbox();
  currentChar = myiShield.getKeypadData();

  if(currentChar != 'i' && currentChar != '/' && currentChar != 'e' && cont < 5){ //Reading the password
    passwordTyped[cont] = currentChar;
    cont++;
    Serial.println("Incoming Data:");
    Serial.println(currentChar);
    Serial.println(passwordTyped);
    lcd_print("*");
    
  }else if (currentChar == 'i'){ //Intro key pressed, check if password is correct
    
    Serial.println(passwordTyped);
    
     matchPass = true;
     
    for(int i = 0; i < 5; i++){
      if(passwordTyped[i] != myPassword[i]){
        matchPass = false;
      }
    }
    
    if(matchPass == false){
      Serial.println("Wrong password");
      lcd_clear();
      lcd_print("Wrong password");
      lcd_setColor(150, 0, 0);
      delay(2000);
    }else{
      Serial.println("Correct           password");
      lcd_clear();
      lcd_print("Correct         password");
      lcd_setColor(0, 150, 0);
      delay(2000);
    }
    
      //delete passwordTyped;
      passwordTyped[0] = '\0';
      cont = 0;
      lcd_clear();
      lcd_print("Type password:  ");
      lcd_setColor(0, 0, 150);
      Serial.println("Out correct");
    
  }else if (currentChar == 'e'){ //Delete button pressed 
    
    passwordTyped[cont] = '\0';
    Serial.println("After delete:");
    Serial.println(passwordTyped);
    cont--;

    lcd_cursorBackward();
      
  }
  
}
