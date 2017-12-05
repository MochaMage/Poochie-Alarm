/**
 * @example TCPServer.ino
 * @brief The TCPServer demo of library WeeESP8266. 
 * @author Wu Pengfei<pengfei.wu@itead.cc> 
 * @date 2015.02
 * 
 * @par Copyright:
 * Copyright (c) 2015 ITEAD Intelligent Systems Co., Ltd. \n\n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version. \n\n
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "ESP8266.h"
#include <SoftwareSerial.h>

#define SSID        "" // Define please
#define PASSWORD    "" // Define please
#define SPEAKER_PIN 4

SoftwareSerial mySerial(3,2);
ESP8266 wifi(mySerial);

void setup(void)
{
    Serial.begin(9600);
    Serial.println("setup begin");

    delay(5000);
    
    Serial.print("FW Version:");
    Serial.println(wifi.getVersion().c_str());
    
    if (wifi.setOprToStation()) 
    {Serial.println("to station ok");} 
    else 
    {Serial.println("to station err");}
        
 
    if (wifi.joinAP(SSID, PASSWORD)) 
    {
        Serial.println("Join AP success");
        Serial.print("IP: ");
        Serial.println(wifi.getLocalIP().c_str());    
    } 
    else 
    {Serial.println("Join AP failure");}
    
    if (wifi.enableMUX()) 
    {Serial.println("multiple ok");} 
    else 
    {Serial.println("multiple err");}
    
    if (wifi.startTCPServer(80)) 
    {Serial.println("start tcp server ok");} 
    else 
    {Serial.println("start tcp server err");}
    
    if (wifi.setTCPServerTimeout(10)) 
    { Serial.println("set tcp server timout 10 seconds");} 
    else 
    {Serial.println("set tcp server timout err");}
    
    Serial.println("setup end");
}
 
void loop(void)
{
    uint8_t buffer[128] = {0};
    uint8_t mux_id;
    uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 100);
    if (len > 0) 
    {
        Serial.println("Get off the couch, poochie!");
        for(uint32_t j = 0; j < 4; j++)
        {
          // play a note on pin 6 for 200 ms:
          noTone(SPEAKER_PIN);
          tone(SPEAKER_PIN, 1660, 500);
          delay(500);
          noTone(SPEAKER_PIN);
        }
        
        Serial.println("Status:[");
        Serial.print(wifi.getIPStatus().c_str());
        Serial.println("]");
        
        Serial.print("Received from :");
        Serial.println(mux_id);
        
        Serial.println("[");
        for(uint32_t i = 0; i < len; i++) 
        {Serial.print((char)buffer[i]);}
        Serial.println("]");
        
        if(wifi.send(mux_id, buffer, len)) 
        {Serial.println("send back ok");} 
        else 
        {Serial.println("send back err");}
        
        if (wifi.releaseTCP(mux_id)) 
        {
            Serial.print("release tcp ");
            Serial.print(mux_id);
            Serial.println(" ok");
        } 
        else 
        {
            Serial.print("release tcp");
            Serial.print(mux_id);
            Serial.println(" err");
        }
        
        Serial.println("Status:[");
        Serial.print(wifi.getIPStatus().c_str());
        Serial.println("]");
    }
}
        
