//Главная программа

#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library

LCDWIKI_KBV display(ILI9486,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset

int analogPin = A10; // пин вывода данных с ЭКГ модуля

void setup() 
{
  Serial.begin(9600); // связь с плоттер портом
  pinMode(analogPin, INPUT); // настраиваем A10  на получение сигнала
  float vlotage = 0.0;
  display.Init_LCD(); 
  display.Fill_Screen(0x0);  
  display.Set_Rotation(1);

}

void loop() 
{
  Show_text(); //header на экране

  Show_BPM(); //footer  на экране

  float voltage = 0.0; //значение с аналогова выхода в вольтах
  int myWidth = display.Get_Display_Width() - 150; //получаю ширину пространства под ЭКГ на LCD
  int myHeigth = display.Get_Display_Height(); //получаю высоту всего LCD
  int differ = 50; // коэфициент отличия показаний датчика ЭКГ

  display.Set_Draw_color(38,216,26);

  for(int i=0; i<myWidth; i++)
  {
      int pinA10 = analogRead(analogPin);
      voltage = (pinA10 * 3.3) / 1024.0;
      Serial.println(voltage);
      display.Draw_Line(i, (myHeigth - voltage * 72) / 2, i+2, (myHeigth - voltage * 72) / 2); // * 22 это пока заглушка для увеличения кривой
      delay(40); // скорость 40 ms
  }
  display.Fill_Screen(0, 0, 0); //когда линия дойдет до края экрана обновить экран
}


// void calculateBPM () 
// {  
//   int beat_new = millis();    // get the current millisecond
//   int diff = beat_new - beat_old;    // find the time between the last two beats
//   float currentBPM = 60000 / diff;    // convert to beats per minute
//   beats[beatIndex] = currentBPM;  // store to array to convert the average
//   float total = 0.0;
//   for (int i = 0; i < 500; i++){
//     total += beats[i];
//   }
//   BPM = int(total / 500);
//   beat_old = beat_new;
//   beatIndex = (beatIndex + 1) % 500;  // cycle through the array instead of using FIFO queue
//   }

    //display main surface
  unsigned long Show_text(void){
    display.Set_Draw_color(32, 0,255);
    display.Fill_Rectangle(0, 0, display.Get_Display_Width()-1, 20);
    display.Set_Text_colour(0, 255, 0);   
    display.Set_Text_Size(2);
    display.Set_Text_Mode(1);
    display.Print_String("* ECG test module *", CENTER, 5);

    display.Set_Draw_color(128, 128, 128);
    display.Fill_Rectangle(0, display.Get_Display_Height()-15, display.Get_Display_Width()-1, display.Get_Display_Height()-1);
    display.Set_Text_colour(255, 255, 255);   
    display.Set_Text_Size(2);
    display.Set_Text_Mode(1);
    display.Print_String("DaJe techical", CENTER, display.Get_Display_Height()-18);

    display.Set_Draw_color(255, 0, 0); 
    display.Draw_Rectangle(0, 15, display.Get_Display_Width()-1, display.Get_Display_Height()-16);  
  }


     //display main surface
  unsigned long Show_BPM(void){
    display.Set_Draw_color(32, 0,255);
    display.Fill_Rectangle(340, 200, display.Get_Display_Width()-1, 20);
    display.Set_Text_colour(0, 255, 0);   
    display.Set_Text_Size(2);
    display.Set_Text_Mode(1);
    display.Print_String("Puls", RIGHT, 30);
    display.Print_String("testing...", RIGHT, 70);


    display.Set_Draw_color(128, 128, 128);
    display.Fill_Rectangle(340, display.Get_Display_Height()-15, display.Get_Display_Width()-1, display.Get_Display_Height()-1);
    display.Set_Text_colour(255, 255, 255);   
    display.Set_Text_Size(2);
    display.Set_Text_Mode(1);
    display.Print_String("DaJe techical", CENTER, display.Get_Display_Height()-18);

    display.Set_Draw_color(255, 0, 0); 
    display.Draw_Rectangle(0, 15, display.Get_Display_Width()-1, display.Get_Display_Height()-16);  
  }

  
      //тестовые строки-------------------------------------------------
      // Serial.println(data); //343 это будет 0
      // float voltage = data * 3.3 / 1024;
      // String voltVal = String(voltage);
      
      // display.Set_Text_Size(2);
      // display.Set_Text_Mode(1);
      // display.Print_String( voltVal , CENTER, 5);
      // delay(1000);
      //вверху тестовые строки-------------------------------------------
                                      

