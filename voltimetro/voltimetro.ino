/***************************************************************************
            Importar bibliotecas
***************************************************************************/
#include <PCD8544.h>

/***************************************************************************
            definiciones - variables
***************************************************************************/
//Establece leds warning tension > 20V
#define WARNING_CH0 10
#define WARNING_CH1 11
#define WARNING_CH2 12
#define WARNING_CH3 13

//Lectura puertos analogicos canales CH0 CH1 CH2 CH3
int readCH0;
int readCH1;
int readCH2;
int readCH3;
// calculo tensiones canales
float voltajeCH0;
float voltajeCH1;
float voltajeCH2;
float voltajeCH3;

/***************************************************************************
            Display PCD8544 definiciones - variables
***************************************************************************/

#define switchDisplay 8 // Switch encendido apagado pantalla
PCD8544 lcd;
// The dimensions of the LCD (in pixels)...
static const byte LCD_WIDTH = 84;
static const byte LCD_HEIGHT = 48;
// A custom "degrees" symbol...
static const byte DEGREES_CHAR = 1;
static const byte degrees_glyph[] = { 0x00, 0x07, 0x05, 0x07, 0x00 };

int switchDisplay_read;  // Almacena estado on/off pantalla


/***************************************************************************
            Display PCD8544 funciones
***************************************************************************/

// Despliega datos en pantalla
void displaylcd(){
   switchDisplay_read = digitalRead(switchDisplay);
 
    lcd.clear();

    if(switchDisplay_read==HIGH){
      lcd.setPower(1);  
      // Imprime tensión canal 0
      lcd.setCursor(0, 0);
      lcd.print("CH0 ");
      lcd.print(voltajeCH0);
      // Imprime tensión canal 1
      lcd.setCursor(0, 1);
      lcd.print("CH1 ");
      lcd.print(voltajeCH1);
      // Imprime tensión canal 2
      lcd.setCursor(0, 2);
      lcd.print("CH2 ");
      lcd.print(voltajeCH2);
      // Imprime tensión canal 3
      lcd.setCursor(0, 3);
      lcd.print("CH3 ");
      lcd.print(voltajeCH3);
    }
    else{
      lcd.setPower(0);
    }        
    delay(3000);
} 

/***************************************************************************
            Warnings funciones
***************************************************************************/
// Enciende los leds en caso de superar los 20V en los canales
void warningsleds(){
  while(voltajeCH0 > 20){
    digitalWrite(WARNING_CH0, HIGH); 
    break;
  }
  while(voltajeCH0 < 20){
    digitalWrite(WARNING_CH0, LOW); 
    break;
  }
  while(voltajeCH1 > 20){
    digitalWrite(WARNING_CH1, HIGH); 
    break;
  }
  while(voltajeCH1 < 20){
    digitalWrite(WARNING_CH1, LOW); 
    break;
  }
  while(voltajeCH2 > 20){
    digitalWrite(WARNING_CH2, HIGH); 
    break;
  }
  while(voltajeCH2 < 20){
    digitalWrite(WARNING_CH2, LOW); 
    break;
  }
  while(voltajeCH3 > 20){
    digitalWrite(WARNING_CH3, HIGH); 
    break;
  }
  while(voltajeCH3 < 20){
    digitalWrite(WARNING_CH3, LOW); 
    break;
  }
}


/***************************************************************************
            SETUP
***************************************************************************/
void setup(void){
  Serial.begin(9600);
  // Configura pantalla     
    pinMode(switchDisplay, INPUT);     
    lcd.begin(LCD_WIDTH, LCD_HEIGHT);  
    // Register the custom symbol...
    lcd.createChar(DEGREES_CHAR, degrees_glyph);
    lcd.clear();
  
  pinMode(WARNING_CH0, OUTPUT);
  pinMode(WARNING_CH1, OUTPUT);
  pinMode(WARNING_CH2, OUTPUT);
  pinMode(WARNING_CH3, OUTPUT); 

}

/***************************************************************************
            LOOP
***************************************************************************/
void loop(void){

  readCH0 = analogRead(A0);
  voltajeCH0 = readCH0 * (5.0 / 1023.0);
  voltajeCH0 = voltajeCH0 * 100;
  readCH1 = analogRead(A1);
  voltajeCH1 = readCH1 * (5.0 / 1023.0);
  voltajeCH1 = voltajeCH1 * 100; 
  readCH2 = analogRead(A2);
  voltajeCH2 = readCH2 * (5.0 / 1023.0);
  voltajeCH2 = voltajeCH2 * 100; 
  readCH3 = analogRead(A3);
  voltajeCH3 = readCH3 * (5.0 / 1023.0);
  voltajeCH3 = voltajeCH3 * 100; 

  warningsleds(); 

  displaylcd();
  delay(1000);  // 1 segundo en milisegundos   
}
