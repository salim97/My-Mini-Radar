#include <ESP8266WebServer.h>
#include <IPAddress.h>
#include <WiFiUDP.h>
#include <ESP8266WiFi.h>


//---------------------------------------------------------
// UDP packet handler
//---------------------------------------------------------
IPAddress ipBroadCast;
String localIP, remoteIP ;
unsigned int udpPort = 5551 ;
unsigned int tcpPort = 5544;  // port input data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
WiFiUDP  udp; // udp broadcast client
WiFiClient client; // tcp client
String tcpBuffer, udpBuffer ;


/*---------------*/
// wifi config
/*----------------*/
char* ssid = "r2" ; //"DJAWEB_1CE0" ; //"DJAWEB_1CE0";
char* password = "qt2016c++" ;// "123412341234" ;



bool mynetwork_init()
{
  //start connecting to wifi....
  WiFi.begin(ssid,password);
  // wait untill esp8266 connected to wifi...
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  // debuging ...
   Serial.println("");
   Serial.print("IP Address: ");
   Serial.println(WiFi.localIP()); // todo: config ip broadcast

  ipBroadCast = WiFi.localIP() ;
  ipBroadCast[3] = 255;
  udp.begin(udpPort); // set udp port for listen...
  localIP +=       String(WiFi.localIP()[0]) ;
  localIP += +"."+ String(WiFi.localIP()[1]) ;
  localIP += +"."+ String(WiFi.localIP()[2]) ;
  localIP += +"."+ String(WiFi.localIP()[3]) ;

  return true ;
}

String mynetwork_localIP()
{
  return  localIP;
}

String readAllUDP()
{
  int packetSize = udp.parsePacket();
  udpBuffer = "";
  if(packetSize)
  {
    // read the packet into packetBufffer
    udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
    udpBuffer = String(packetBuffer) ;

    for (int i =0; i < packetSize; i++)
    packetBuffer[i]= 0;
    // Serial.println("readAllUDP: "+udpBuffer) ;
  }

  return udpBuffer ;
}

String readAllTCP()
{
  tcpBuffer = "" ;
  if (client.connected())
  {
    if(client.available())
    {
      while(client.available())
      {
        char c = client.read();
        tcpBuffer += c ;

      }

      // Serial.println("readAllTCP: "+tcpBuffer) ;
    }
  }

  return tcpBuffer ;
}

bool connectToHost(String ip)
{
  if( ip == remoteIP )
    if(client.connected())
      return true ;

  remoteIP= ip ;
  byte parts[4] = {0, 0, 0, 0};
  int part = 0 ;
  for ( int i = 0 ; i < ip.length() ; i++)
  {
    char c = ip[i];
    if ( c == '.' )
    {
      part++;
      continue ;
    }
    parts[part] *= 10 ;
    parts[part] += c - '0';
  }

  client.stop();
  return client.connect(parts, tcpPort) ;
}
String ipToString(IPAddress ip)
{
    return String(ip[0])+"."+String(ip[1])+"."+String(ip[2])+"."+String(ip[3]) ;
}
bool isConnected()
{
  return client.connected();
}

void sendUDP(String msg)
{
  if(msg.length() == 0 ) return ;

  msg += " " ;
  // convert string to char array
  int UDP_PACKET_SIZE = msg.length();
  char tmpBuffer[UDP_PACKET_SIZE-1] ;
  msg.toCharArray(tmpBuffer, UDP_PACKET_SIZE) ;

  // send msg broadcast to port destinie
  udp.beginPacket(ipBroadCast, udpPort);
  udp.write(tmpBuffer, sizeof(tmpBuffer));
  udp.endPacket();
  // Serial.println("sendUDP: "+msg) ;
}

// it should be bool and not void because TCP ....
void sendTCP(String msg)
{
  if(msg.length() == 0 ) return ;
  if(isConnected())
    client.print(msg);

  // Serial.println("sendTCP: "+msg) ;
}
