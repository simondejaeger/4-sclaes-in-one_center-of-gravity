

//                          Simon De Jaeger 28/10/2020
//                          ---------------------------    
//  
//
//                  PROGRAMME ARDUINO POUR Balance à 4 pesons aux coins d'un rectangle. (4x HX711)
//
//        balance 1=   clk:D2  dat:D3  lm35:A1   coefcalib=-440 (dans mon cas, à calibrer un à un)   
//        balance 2=   clk:D4  dat:D5  lm35:A2   coefcalib=-425 (dans mon cas, à calibrer un à un)     
//        balance 3=   clk:D6  dat:D7  lm35:A3   coefcalib=-425 (dans mon cas, à calibrer un à un)     
//        balance 4=   clk:D8  dat:D9  lm35:A3   coefcalib=-425 (dans mon cas, à calibrer un à un)     
//
//        baudrate 960
//        Affichage dans moniteur: B1 B2 B3 B4 SOMME    X Y 
//
//        origine du repère B4, puis dans le sens horloger, B1,B2,B3:
//
//                    
//
//        B1---------------------B2
//        |                       |
//        |   x                   |
//        |-------O               |
//        |       |  y            |
//        |       |               |
//        B4------|--------------B3
//                           
//                       ----------------------------------

#include "HX711.h"

HX711 scaleA;
HX711 scaleB;
HX711 scaleC;
HX711 scaleD;

int calibration_factor1 = 425;         //calibf1
int calibration_factor2 = 425;         //calibf2
int calibration_factor3 = 425;         //calibf3
int calibration_factor4 = 425;         //calibf4

void setup() 

              {
  
  Serial.begin(9600);
  
  scaleA.begin(3, 2);    // (DOUT;CLK)  balance 1
  scaleB.begin(5, 4);    // (DOUT;CLK)  balance 3   
  scaleC.begin(7, 6);    // (DOUT;CLK)  balance 2
  scaleD.begin(9, 8);    // (DOUT;CLK)  balance 4
  
  scaleA.set_scale();
  scaleB.set_scale();
  scaleC.set_scale();
  scaleD.set_scale();
  
  scaleA.tare();
  scaleB.tare(); 
  scaleC.tare(); 
  scaleD.tare();
  
  int zero_factorA = scaleA.read_average(); 
  int zero_factorB = scaleB.read_average();
  int zero_factorC = scaleC.read_average();
  int zero_factorD = scaleD.read_average();

              }

void loop()   

              {

  int clk=100;                    //fréquence de prise de mesures en ms
  
  scaleA.set_scale(calibration_factor1); 
  scaleB.set_scale(calibration_factor2);   
  scaleC.set_scale(calibration_factor3); 
  scaleD.set_scale(calibration_factor4); 

  Serial.print(scaleA.get_units(), 1);       
  Serial.print("  ");
  Serial.print(scaleB.get_units(), 1);    
  Serial.print("  ");
  Serial.print(scaleC.get_units(), 1);      
  Serial.print("  ");
  Serial.print(scaleD.get_units(), 1);    
  Serial.print("  ");

    int BA = scaleA.get_units(); 
    int BB = scaleB.get_units();
    int BC = scaleC.get_units();
    int BD = scaleD.get_units();
    
    int sP = BA+BB+BC+BD;
      Serial.print(sP);
      Serial.print("        ");
      
    int x=258*(BB+BC)/sP;                   //258=xMAX
    int y=222*(BA+BB)/sP;                   //222=yMAX
      Serial.print(x);
      Serial.print("    ");
      Serial.print(y);

  Serial.println("");
  
      delay(clk);

                }
