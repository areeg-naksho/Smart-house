#include <ESP8266WiFi.h>

const char* ssid = "Arduino";
const char* password = "arduinoarduino";
//int people = 0;

const float trigPin1 = D0;
const float echoPin1 = D1;
const float led = D2;
const float firesensor = D3;
const float button = D4;
const float corridorleds = D7;
const float watermotor = D6 ;

const float fan = D8;
const float buzzer = 10;
int people=0;
WiFiServer server(80);
void setup() {
  Serial.begin(9600);
  pinMode(trigPin1 , OUTPUT);
  pinMode(echoPin1 , INPUT);
  pinMode(led , OUTPUT);
  pinMode(firesensor, INPUT);
  pinMode(button , INPUT);
  pinMode(watermotor, OUTPUT);
  


  pinMode(fan , OUTPUT);
  pinMode(buzzer , OUTPUT);


  Serial.begin(9600);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to "); // print
  Serial.println(ssid); // print wifi name

  WiFi.begin(ssid, password); // to start wifi

  while (WiFi.status() != WL_CONNECTED) {   
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");


  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());  // print IP

  Serial.println("/");
  // people = 0;
}
void loop() {

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request

  int value = LOW;
  

  if (request.indexOf("/ledon") != -1) {
    digitalWrite(led , HIGH);
  }
  if (request.indexOf("/ledoff") != -1) {
    digitalWrite(led , LOW);
  }

  if (request.indexOf("/Corridor") != -1)
  {
  digitalWrite(button,HIGH);
  }

  if (request.indexOf("/fire") != -1)
  {
    int x = digitalRead(firesensor);
    Serial.println(x);
    if (x == 0)
    {
      digitalWrite(buzzer, LOW);
    }
    else
    { digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
    }
  }

  if (request.indexOf("/pumpon") != -1)
  {
    digitalWrite(watermotor, HIGH); 
  }
  if (request.indexOf("/pumpoff") != -1)
  {
    digitalWrite(watermotor, LOW);

  }
  if (request.indexOf("/fanon") != -1)
  {

    digitalWrite(fan , HIGH);

  }

  if (request.indexOf("/fanoff") != -1) {
    digitalWrite(fan , LOW);
  }
  

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.print("<h1 style='FONT-SIZE:50px;background-color:yellow;text-align:center;'>Control Your Home</h1>");

  client.println("<br><br>");
  client.println("<a href=\"/ledon\"\"><button style='FONT-SIZE:50px; HEIGHT:200px;WIDTH:300px; 126px;Z-INDEX:0;TOP:200px;'>Led on</button></a>");
  client.println("<a href=\"/ledoff\"\"><button style='FONT-SIZE:50px; HEIGHT:200px;WIDTH:300px; 126px;Z-INDEX:0;TOP:200px;'>Led off</button></a><br />");
  client.println("<br><br>");

  client.println("<br><br>");
  client.println("<a href=\"/pumpon\"\"><button style='FONT-SIZE:50px; HEIGHT:200px;WIDTH:300px; 126px;Z-INDEX:0;TOP:200px;'>Pump on</button></a>");
  client.println("<a href=\"/pumpoff\"\"><button style='FONT-SIZE:50px; HEIGHT:200px;WIDTH:300px; 126px;Z-INDEX:0;TOP:200px;'>Pump off</button></a><br />");
  client.println("<br><br>");
  
  client.println("<br><br>");

  client.println("<a href=\"/Corridor\"\"><button style='FONT-SIZE:50px; HEIGHT:200px;WIDTH:300px; 126px;Z-INDEX:0;TOP:200px;'>Corridor</button></a>");
  client.println("<a href=\"/fire\"\"><button style='FONT-SIZE:50px; HEIGHT:200px;WIDTH:300px; 126px;Z-INDEX:0;TOP:200px;'>fire</button></a>");
  int x = digitalRead(firesensor);
  if (x == 1) {
    client.println("<h1 style='FONT-SIZE:50px;background-color:red;text-align:center;'>");
    client.println("thier is a fire");
    client.println("</h1>");
  }
  else {
    client.println("<h1 style='FONT-SIZE:50px;background-color:green;text-align:center;'>");
    client.println("their isn't a fire");
    client.println("</h1>");
  }
  //************************

  client.println("");
  

   client.println("<br><br>");
  client.println("<a href=\"/fanon\"\"><button style='FONT-SIZE:50px; HEIGHT:200px;WIDTH:300px; 126px;Z-INDEX:0;TOP:200px;'>fan on</button></a>");
  client.println("<a href=\"/fanoff\"\"><button style='FONT-SIZE:50px; HEIGHT:200px;WIDTH:300px; 126px;Z-INDEX:0;TOP:200px;'>fan off</button></a><br />");
  client.println("<br><br>");

  client.print("<h1 style='FONT-SIZE:50px;background-color:yellow;text-align:center;'>");
 long distance1 = Ultrasonic1 ();
  client.println("Is there a visitor??");
  if (distance1 <= 10)
    client.print("Someone on door");
  else
    client.print("thier is no one");
  client.print("/<h1>");

  //************************
}

long Ultrasonic1 ()
{
  //*****************ultra sonic********//
  long duration1, distance1;
  digitalWrite(trigPin1, HIGH);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin1, LOW);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  duration1 = pulseIn(echoPin1, HIGH);

  distance1 = (duration1 / 2) / 29.1;

  Serial.println(distance1);
  return distance1;
  //delay(2000);
  //*****************ultra sonic********//

}

void fire()
{
  int x = digitalRead(firesensor);
  Serial.println(x);
  if (x == 0)
  {
    digitalWrite(buzzer, LOW);
  }
  else
  { digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
  }


}


