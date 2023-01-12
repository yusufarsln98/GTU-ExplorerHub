const int buttonPin = 2;    // the number of the pushbutton pin
const int secondButtonPin = 3; // // the number of the check button pin
const int ledPin =  8;      // the number of the LED pin

int number = 0;
// variables will change:
int buttonState = 0;
int secondButtonState = 0;         
int count_value = 0;
int prestate = 0;

void setup() 
{
  pinMode(ledPin,OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(secondButtonPin, INPUT);
  Serial.begin(9600);
  
}

void loop() 
{
    char Operation = '0'; 
    
    if( Serial.available())
    {
      Operation=Serial.read();     
    
      switch (Operation)
      {
        case '1':
        {        
            digitalWrite(ledPin,HIGH);  
            break;              
        }
        
        case '2':
        {     
          digitalWrite(ledPin,LOW);
          break;
        }  
    
        case '3':
        {
          for(int i=0;i<3;i++)
          {        
            digitalWrite(ledPin,HIGH);    
            delay(500);
            digitalWrite(ledPin,LOW);    
            delay(500);
          }   
          break;    
            
        }
        case '4':
        { 
          square_of_number();
          delay (500);
          break;       
        }
        case '5':
        {
          button();
          break;
        }
  
      }
    }
}     

void square_of_number()
{
  
  for (int i = 0; i < 99999; i++)
  {
    
    if(Serial.available())
    {       
      delay(500);         
      String incomingByte = Serial.readString(); 
                    
      delay(500);
      number = sq(incomingByte.toInt());       

      if (number != ' ' && number > 0)
      {
        Serial.println(number); 
        break;
      }
          
    }
  }
}

void button()
{
  for (int i = 0; i < 99999; i++)
    {
      if(Serial.available())
      {
        buttonState = digitalRead(buttonPin);
        secondButtonState = digitalRead(secondButtonPin);
        if (secondButtonState == HIGH)
        {
          Serial.println('Q');
          delay (500);
          break;
        }
        else if (buttonState == HIGH && prestate == 0 && secondButtonState == LOW) 
        {
          count_value++;
          Serial.println(count_value);
          prestate = 1;
          delay (500);
        } 
        else if (buttonState == LOW) 
        {
          prestate = 0;
        }

      }
    } 

}
