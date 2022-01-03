/**********************************************
 * Menu jednopoziomowe (single level menu)
 **********************************************/
#include <LCD16x2.h>
#include <Wire.h>
LCD16x2 lcd;

/***************************************************************************************/
//number of menu options (size of menu table)
#define menuoptions 4
//length of menu LCD line (left/right side is occupied by menu line pointer, so 
//length of menu line should be calculated as menuitemlen = number_of_LCD_columns - 1, because
//we need one more character to store end of string (chr(0))
#define menuitemlen 15
//number of LCD lines (how many lines you can see on the LCD screen)
#define lcd_lines 2

//menu item structure (single recorod of menu)
//  menu_message = message displayed on the screen
//  whereisptr = offset for pointer location (subtracted from actual menu position)
//  y0 = location of marker if the line is displayed/pointed
typedef struct menuitem
{
    char menu_message[menuitemlen];
    char whereisptr;
    char y0;
};

//menu definition
const menuitem menu_lines[menuoptions]=
 {{"First menu lin", 0, 1},
  {"Second menu li", 0, lcd_lines},
  {"Third menu lin", 1, lcd_lines},
  {"Fourth menu li", 2, lcd_lines}};

//pointer to the menu lines
menuitem *menu_lines_ptr;
//actual menu position
signed char menu_position;
//user choice of menu
char user_choice;
//variable to store byte of button's status and number of pressed button 
int pressed;


/************************************************
 clear left/right marks
 ************************************************/
void Clear_Marks()
{
  menu_lines_ptr = &menu_lines[0];            //pointer to the beginning of the menu table
  menu_lines_ptr = menu_lines_ptr + menu_position;
  lcd.lcdGoToXY(1, menu_lines_ptr->y0);       //left marker clear
  lcd.lcdWrite(" ");
  lcd.lcdGoToXY(menuitemlen+1, menu_lines_ptr->y0);  //right marker clear
  lcd.lcdWrite(" ");
}


/************************************************
 menu display
 ************************************************/
void Display_Menu()
{
  char i;
  menuitem *ptrtemp;
  
  menu_lines_ptr = &menu_lines[0];      //pointer to the beginning of the menu table
  ptrtemp = menu_lines_ptr + menu_position;
  menu_lines_ptr = menu_lines_ptr + (ptrtemp->whereisptr);
  for (i = 0; i < lcd_lines; i++)
  {
    lcd.lcdGoToXY(2, i+1);
    lcd.lcdWrite((menu_lines_ptr+i)->menu_message);
  }
  lcd.lcdGoToXY(1, ptrtemp->y0);  //left marker display
  lcd.lcdWrite(">");
  lcd.lcdGoToXY(menuitemlen+1, ptrtemp->y0);  //right marker display
  lcd.lcdWrite("<");
}


/************************************************
 user menu
   1, 2 - moves the marker
   3 - returns 0
   4 - returns actual menu position
 ************************************************/
char User_Menu(int key_number)
{
  switch (key_number)
  {
    case 0:
      break;
    case 1:
      Clear_Marks();  //clear markers in actual place
      menu_position++;  //increment menu position
      if (menu_position >= menuoptions) menu_position=0;  //if menu position > menu lines, than 0
      Display_Menu(); //display menu lines, markers will be displayed further
      break;
    case 2:
      Clear_Marks();  //clear markers in actual place
      menu_position--;  //decrement menu position
      if (menu_position < 0) menu_position = menuoptions-1; //if menu position < 0,than change to display 2 lines from the end of menu table
      Display_Menu(); //display menu lines, markers will be displayed further
      break;
    case 3:
      return(0);    //left pressed = return 0
      break;
    case 4:         //right pressed = return actual position
      return(menu_position+1);
      break;
  }
  return(0);
}


/************************************************
 number of button pressed
 ************************************************/
int Number_of_Button()
{
  int key_byte;
  
  //read the status of the buttons
  //corresponding bit is cleared, if buttons is pressed
  key_byte = lcd.readButtons();
  //one's complement (variable negqation)
  //after this operation corresponding bit is set, when button is pressed
  key_byte = ~key_byte;
  //which button is pressed?
  if (key_byte & 0x01) return(1);
    else if (key_byte & 0x02) return(2);
      else if (key_byte & 0x04) return(3);
        else if (key_byte & 0x08) return(4);
          else return(0);
}

/************************************************
 initialization
 ************************************************/
void setup()
{
  Wire.begin();     //TWI interface init
  lcd.lcdClear();   //LCD screen clear
  lcd.lcdSetBlacklight(255);  //maximum backlight on
  menu_position = 0;  //start menu position
  Display_Menu();   //display menu from begining
}


/************************************************
 main loop
 ************************************************/
void loop()
{
  //read key
  pressed = Number_of_Button();
  //enter menu if key is pressed
  if (pressed > 0) user_choice = User_Menu(pressed);
  //action depending on user choice
  //here, for example and to show it works perfect, is changing of backlight intensity
  switch (user_choice)
  {
    case 1:
      lcd.lcdSetBlacklight(255);
      break;
    case 2:
      lcd.lcdSetBlacklight(50);
      break;
    case 3:
      lcd.lcdSetBlacklight(10);
      break;
    case 4:
      lcd.lcdSetBlacklight(0);
      break;
  }
}
