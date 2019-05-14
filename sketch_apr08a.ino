#include <WiFi.h>

const char* wifi_name = "Connectify-Lhabib"; // Your Wifi network name here
const char* wifi_pass = "Lhabib1992";    // Your Wifi network password here
WiFiServer server(80);    // Server will be at port 80

int relay_pin = 2;
int relay_pin12 = 16;
int relay_pin13 = 17;


void setup() 
{
  Serial.begin (115200);
  pinMode (relay_pin, OUTPUT);

  Serial.print ("Connecting to ");
  Serial.print (wifi_name);
  WiFi.begin (wifi_name, wifi_pass);     // Connecting to the wifi network

  while (WiFi.status() != WL_CONNECTED) // Waiting for the response of wifi network
  {
    delay (500);
    Serial.print (".");
  }
  Serial.println("");
  Serial.println("Connection Successful");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());           // Getting the IP address
   
   

  server.begin();                           // Starting the server
} 

void loop() 
{
  WiFiClient client = server.available();     //Checking if any client request is available or not
  if (client)
  {
    boolean currentLineIsBlank = true;
    String buffer = "";  
    while (client.connected())
    {
      if (client.available())                    // if there is some client data available
      {
        char c = client.read(); 
        buffer+=c;                              // read a byte
        if (c == '\n' && currentLineIsBlank)    // check for newline character, 
        {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();    
          client.print("<HTML><title>Steckdose</title>");
          client.print("<body><h1> intelligente Steckdose </h1>");
          client.print("Relay Control 1</p>");
          client.print("<a href=\"/?relayon\"\"><button>AN</button></a>");
          client.print("<a href=\"/?relayoff\"\"><button>Aus</button></a>");
          client.print("<p>Relay Control 2</p>");
          client.print("<a href=\"/?relayon1\"\"><button>An</button></a>");
          client.print("<a href=\"/?relayoff1\"\"><button>Aus</button></a>");
          client.print("<p>Relay Control 3</p>");
          client.print("<a href=\"/?relayon3\"\"><button>An</button></a>");
          client.print("<a href=\"/?relayoff3\"\"><button>Aus</button></a>");
          
          
          client.print("</body></HTML>");
          break;        // break out of the while loop:
        }
        if (c == '\n') { 
          currentLineIsBlank = true;
          buffer="";       
        } 
        else 
          if (c == '\r') {     
          if(buffer.indexOf("GET /?relayon")>=0){
            digitalWrite(relay_pin13, LOW);
            }
          if(buffer.indexOf("GET /?relayoff")>=0)
            digitalWrite(relay_pin13, HIGH);  
           if(buffer.indexOf("GET /?relayon1")>=0)
            digitalWrite(relay_pin12, LOW);
          if(buffer.indexOf("GET /?relayoff1")>=0)
            digitalWrite(relay_pin12, HIGH);   
           if(buffer.indexOf("GET /?relayon3")>=0)
            digitalWrite(relay_pin, LOW);
          if(buffer.indexOf("GET /?relayoff3")>=0)
            digitalWrite(relay_pin, HIGH); 
          
        }
        else {
          currentLineIsBlank = false;
        }  
      }
    }
    client.stop();
  }
}
