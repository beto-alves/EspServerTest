#include <Arduino.h>
#include <WiFiServer.h>
#include <WiFi.h>

WiFiServer wifiServer(5000);
WiFiClient wifiClient;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  WiFi.softAP("SSID_NAME", "PASS", 2, 0, 5);
  
  wifiServer.begin();
}

void tcp()
{
    if (wifiClient.connected()) //Cliente conectado
    {
        if (wifiClient.available() > 0) //Tem dados para leitura
        {
            String req = "";
            while (wifiClient.available() > 0)
            {
                char z = wifiClient.read();
                req += z;
            }

            //Exibe a mensagem recebida na serial
            Serial.print("\nMensagem recebida");
            Serial.print("\n...Mensagem: " + req + "\n");
            //Envia uma resposta para o cliente
            
            //
            wifiClient.print("OK");
      
        }
    } else {
        wifiClient = wifiServer.available();
        delay(1);
    }
}

void loop() {
  tcp();
}
