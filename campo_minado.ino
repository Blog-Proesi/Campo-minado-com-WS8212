#include <Adafruit_NeoPixel.h>
 
#define PIN 7
#define NUMLED 16
#define botao1 A0
#define botao2 A1
#define enter A4
 
Adafruit_NeoPixel pixels(NUMLED, PIN, NEO_GRB + NEO_KHZ800);

int ponteiro = 1, bomba = 2,proximo = 0, anterior = 0, confirmado[16],
ok = 0, termina = 0, x = 0;  // Cria Variaveis
int alfa[49] =
{0,  0,  0,  0, 200, 200,   0,  0,  200,  200,  0,  0,   0,   0,  0,  0,
 1,  1,  1,  1, 1,   50,  50,   1,    1,   50,  50, 1,   1,   1,  1,  1,
 50, 50,  50,  50, 50,  50,  2, 2,   50,   50,  2,  2,  50, 50, 50, 50, 50};

int beta[49] = 
{5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  350,
 5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  100,  5,  5,  350,
 5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 5000};

void animacao()
{
  ponteiro = 0;
  bomba = random(16);
  x = 0;
  pixels.clear();

  for(int b =0; b < 16; b++)
  {
    confirmado[b] = LOW;
  }

  for(int A = 0; A < 49; A++)
  {
   x++;
   if(x == 17)
   {
    x = 0; 
   }
   else if(x == 33)
   {
    x = 0;
   }
    
    pixels.setPixelColor(x, pixels.Color(alfa[A],0,0));
    pixels.show();
    delay(beta[A]);
  }
}
void setup() 
{
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
  pinMode(enter, INPUT_PULLUP);  
  
  termina = LOW;
  pixels.begin();       //Inicia comunicação com os LED
  bomba = random (16);
  delay(200); 
}
 
void loop() 
{
  anterior = digitalRead(botao2);
  proximo = digitalRead(botao1);
  ok = digitalRead(enter);
    
  if(ponteiro >= 16)
  {
    ponteiro = 0;
  }
  else if(0 > ponteiro)
  {
    ponteiro = 15;
  }
  else if(anterior == LOW)
  {
    delay(200);
    ponteiro--; 
  }
  else if(proximo == LOW)
  {
    delay(200);
    ponteiro++;
  }
  else if(ok == LOW)
  {
    if(ponteiro == bomba)
    {
       animacao();
    }
    else
    {
      delay(200);
      confirmado[ponteiro] = HIGH; 
    }
  }
  
   for(int i=0; i<16; i++)
  { 
    
    if(i == ponteiro)
    {
      pixels.setPixelColor(i, pixels.Color(0, 5, 0));
      pixels.show();
    }
    else if(confirmado[i] == HIGH)
    {
      pixels.setPixelColor(i, pixels.Color(0, 0, 1));
      pixels.show();
    }
    else
    {
      pixels.setPixelColor(i, pixels.Color(1, 1, 1));
      pixels.show();
    }
    delay(10);
  }
  
}
