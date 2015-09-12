/* 
  MEA - Mini Estaçao Meteorologica
  
  Descriçao: Monitorar informaçoes a respeito da temperatura, umidade e
  luminosidade do local desejado.
  
  Este codigo pertence ao dominio publico. Use-o para seus proprios
  projetos e afins!
  
  Para informaçoes, updates e novidades sobre este projeto,
  acompanhe: http://www.hackerspacego.org/index.php?title=MEM_-_Mini_Esta%C3%A7%C3%A3o_Meteorol%C3%B3gica
  
  Modificado em: 11/09/2015
  
  Por: Milvo Gabriel P. Di Domenico
  
*/

#include "DHT.h" // Biblioteca do Sensor de Temperatura e Umidade
#include <LiquidCrystal.h> // Biblioteca do LCD

#define DHTPIN A1 // Pino analogico a qual o DHT esta conectado c
#define DHTTYPE DHT11 // Modelo de sensor DHT sendo utilizado

DHT dht (DHTPIN, DHTTYPE);

int sensorLuz = 0; //Pino analogico A0 a qual o sensor de luminosidade esta conectado
int valorSensorLuz = 0; //Variavel para realizar a leitura do sensor de luminosidade

LiquidCrystal lcd(9, 8, 5, 4, 3, 2); //Definiçao dos pinos digitais a qual o LCD esta conectado

//Array para simbolo do grau
byte grau[8] ={ B00001100,
                B00010010,
                B00010010,
                B00001100,
                B00000000,
                B00000000,
                B00000000,
                B00000000,};
void setup()
{
  lcd.begin(16,2); //Inicializa o LCD
  lcd.clear(); //Funçao para limpar caracteres no LCD
  lcd.createChar(0, grau); // Funçao para criar simbolo do grau
  dht.begin(); //Iniciliza o DHT
  
  /* Caso queira analisar os dados via serial, basta colocar esta parte abaixo em seu codigo!
  Serial.begin(9600);
  */
  
}

void loop()
{
  int valorSensorLuz = analogRead(sensorLuz); //Armazena o valor lido no sensor de luminosidade na variavel "valorSensorLuz"
  float valorUmidade = dht.readHumidity(); //Armazena o valor da umidade lida no DHT e armazena na variavel "valorUmidade"
  float valorTemperatura = dht.readTemperature(); // Armazena o valor da temperatura lida no DHT e armazena na variavel "valorTemperatura"

/* Caso queira analisar os dados via serial, basta colocar esta parte abaixo em seu codigo!

  // print representa a funçao para escrever algo no monitor serial
  
  Serial.print("Luminosidade: "); 
  Serial.println(valorSensorLuz);
  
  // Teste para verificar a possibilidade e funcionamento da leitura de valores do DHT
  
  if (isnan(valorTemperatura) || isnan(valorUmidade))
  {
    Serial.println("Nao foi possivel a leitura do DHT");
  }
  else
  {
    Serial.print("Umidade: ");
    Serial.print(valorUmidade);
    Serial.print(" %");
    Serial.print("Temperatura: ");
    Serial.print(valorTemperatura);
    Serial.print(" *C");
  }
  
*/

  lcd.setCursor(0,0); // Ponto de origem do LCD, coordenadas (x,y)
  lcd.print("Temp: "); // lcd.print tem a mesma funcao do Serial.print
  lcd.print(" ");
  lcd.setCursor(7,0);
  lcd.print(valorTemperatura, 1);
  lcd.setCursor(12,0);
  lcd.write((byte)0); //Simbolo do grau formado pelo array
  lcd.print("C");
  
  lcd.setCursor(0,1);
  lcd.print("Umid: ");
  lcd.print(" ");
  lcd.setCursor(7,1);
  lcd.print(valorUmidade, 1);
  lcd.setCursor(12,1);
  lcd.print("%");
  
  delay (2000); // Tempo antes de executar o restante do codigo abaixo (em ms)
  
  lcd.clear();
  
  lcd.setCursor(0,1);
  lcd.print("Luz: ");
  lcd.print(" ");
  lcd.setCursor(7,1);
  lcd.print(valorSensorLuz);
  
  delay(2000);  
}  
  
  
  
/* Referencias relacionadas a codigo, montagem e saneamento de duvidas:
http://blog.filipeflop.com/sensores/monitorando-temperatura-e-umidade-com-o-sensor-dht11.html
http://www.comofazerascoisas.com.br/projeto-arduino-sensor-de-luz-ldr-com-leds.html
http://www.comofazerascoisas.com.br/projeto-arduino-com-display-lcd-sensor-de-temperatura-e-sensor-de-luz.html
http://blog.filipeflop.com/display/mostrando-informacoes-de-temperatura-no-lcd-16x2-com-o-dht11.html
*/ 
