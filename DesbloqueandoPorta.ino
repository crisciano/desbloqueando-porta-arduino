#####################################################################################
#  	Arquivo:            DesbloqueandoPorta.ino				                           																								#                                
#       Micro-processador:  Arduino UNO     																																		#
# 		Modulos: i2c, lcd 16x2, relay                                       																												#
#  	Linguagem:	    Wiring / C                                              																												#
#						                                   																																			#
#		Objetivo:  abrir uma porta com senha usando arduino                     																								#
#									            																																					#	  
#		Funcionamento:	 Quando o funcionario chegar na portaria, utilizando a senha        																		#
#                             		ele pode acessar a empresa 																															#
#                           						                                      																												#
#                                                                                   																														#
#                                                                                  																														#
#			                                                            																																	#
#                                      																																								#
#					                                          																																		#
#####################################################################################

// bibliotedas 

//biblioteca i2c
#include <Wire.h> 
// biblioteca da lcd 4X4
#include <LiquidCrystal_I2C.h>
// biblioteca keypad 4x4
#include <Keypad.h>

// set as linhas e as colunas
const byte LINHAS = 4;
const byte COLUNAS = 4;

int contador = 0;
char senha[] = {'1','7','2','8','3','9','\0'};
char palavra[] = {'0','0','0','0','0','0','\0'};

int fechadura = 11;

// matrix numerica 4X4
char matriz[LINHAS][COLUNAS] = 
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};

//define os pinos da linha
byte PinosLinhas[LINHAS] = {9,8,7,6};
//define os pinos das colunas
byte PinosColunas[COLUNAS] = {5,4,3,2}; 

// pinos de inicialização do display
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
//LiquidCrystal lcd(0, 1, 2, 3, 4, 5);


//inicializando o teclado 
Keypad kpd = Keypad(makeKeymap(matriz), PinosLinhas, PinosColunas, LINHAS,COLUNAS);


void setup() {
  digitalWrite(fechadura,LOW);
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("DEV crisciano");
  delay(2000);
  lcd.clear();
  lcd.print("Inicializando...");
  delay(2000);
  lcd.clear();
  lcd.print("Digite a senha: ");
  //delay(1000);
  //off_lcd();
  //delay(1000);
  //lcd.setBacklight(LOW);
}

void loop() {
  char key = kpd.getKey();

  if(key)
  {
    lcd.setCursor(0,0);
    lcd.print("Digite a senha: ");
    //delay(1000);
    //off_lcd();
    lcd.setCursor(contador, 1);
    lcd.print("*");
    //on_lcd();
    delay(500);
    palavra[contador] = key;
    contador++;
    if(contador == 6){
      palavra[contador] = '\0';
      if((palavra[0] == senha[0]) && (palavra[1] == senha[1]) && (palavra[3] == senha[3]) && (palavra[4] == senha[4]) && (palavra[5] == senha[5]) && (palavra[6] == senha[6])){
        lcd.clear();
        lcd.print("Senha correta!");
        delay(2000);
        contador = 0;
        lcd.clear();
        lcd.print("Digite a senha: ");
        digitalWrite(fechadura , HIGH);
        delay(1500);
        digitalWrite(fechadura, LOW); 
        }else{
          lcd.clear();
          lcd.print("Senha incorreta!");
          delay(2000);
          contador = 0;
          lcd.clear();
          lcd.print("Digite a senha: ");
          digitalWrite(fechadura, LOW);           
          }
      }
    }
}

void off_lcd(){
  delay(1000);
  lcd.setBacklight(LOW);
}
void on_lcd(){
  //delay(1000);
  lcd.setBacklight(HIGH);
  delay(5000);
  lcd.setBacklight(LOW);
}