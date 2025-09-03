#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

//Création objet pour la gestion du tactile
#define YP A2
#define XM A3
#define YM 8 
#define XP 9
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

//Création de l'objet pour la mise en page de l'écran
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

//Création des bontons
Elegoo_GFX_Button buttonHpmePage[5];
Elegoo_GFX_Button button[2];

//Variable pour indiquer la page
int interface = 0;
int draw = 0;

//GESTION DE LA PRESSION
#define MINPRESSURE 10
#define MAXPRESSURE 1000
#define TS_MINX 120
#define TS_MAXX 945
#define TS_MINY 110
#define TS_MAXY 920

//GUI
#define backgroundColor 0xFFFF
#define textcolor 0x0000
#define textSize 3
#define withButton 175
#define highButton 35
#define xButton 158
#define yfirstButton 50
#define yButton 40
#define textSizeButton 2.5
#define textColorButton 0x0000
#define fillColorButton 0xFFFF
#define outlineColorButton 0x0000

void setup(void)
{
  //Mise en marche de l'écran
  tft.begin(0x9341);

  //GUI général
  tft.setRotation(1);
  tft.setTextColor(textcolor);
  tft.setTextSize(textSize);
  tft.fillScreen(backgroundColor);

  //Création des boutons
  buttonHpmePage[0].initButton(&tft, xButton, yfirstButton, withButton, highButton, outlineColorButton, fillColorButton, textColorButton, "Nouveau Object", textSizeButton);
  buttonHpmePage[1].initButton(&tft, xButton, yfirstButton+yButton, withButton, highButton, outlineColorButton, fillColorButton, textColorButton, "Bluetooth", textSizeButton);
  buttonHpmePage[2].initButton(&tft, xButton, yfirstButton+yButton*2, withButton, highButton, outlineColorButton, fillColorButton, textColorButton, "ChromeCast", textSizeButton);
  buttonHpmePage[3].initButton(&tft, xButton, yfirstButton+yButton*3, withButton, highButton, outlineColorButton, fillColorButton, textColorButton, "Retrouver Objet", textSizeButton);
  buttonHpmePage[4].initButton(&tft, xButton, yfirstButton+yButton*4, withButton, highButton, outlineColorButton, fillColorButton, textColorButton, "Parametre", textSizeButton);

pinMode(13, OUTPUT);
}

void loop(void) 
{

 //Configurtation  pin pour le tactile
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);
  pinMode(XM, OUTPUT);

  //Mettre les donnée en 0 - 1023 en pixel
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    p.x =  map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y =  map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
  }

  //Gestion de l'interface
  //tft.setCursor(3, 3);
  if(interface == 0) //page d'accueil
  {
    //Affichage de l'interface
    if(draw == 0)
    {
      tft.println("Accueil");
      for(int i=0; i<=4; i++)
        buttonHpmePage[i].drawButton();
        draw++;
        tft.setCursor(50, 50);
    }

    //Gestion du tactile
      if (buttonHpmePage[0].contains(p.x, p.y)) 
      {
        buttonHpmePage[0].drawButton(true); 
      }
  }
}
