// Menu
int16_t x, y;
//while (!watch->getTouch(x, y)) {}
x = 0;
y = 0;
delay(500);
Serial.println("");
Serial.println("Affichage du menu");
watch->tft->fillScreen(TFT_BLACK); // fond
watch->tft->setTextColor(TFT_DARKGREEN); // Vert foncé
watch->tft->setTextSize(1);

watch->tft->fillScreen(TFT_BLACK); // fond
watch->tft->fillRect(0, 0, 240, 24, TFT_DARKGREY); // Rectangle gris pr titre (posX coin ht gauche, posY coin ht gauche, largeur, hauteur, couleur)
watch->tft->drawFastHLine(0,25,240,TFT_WHITE); // dessine une ligne horizontale
// Icône 1
watch->tft->drawRoundRect(40, 30, 60, 60, 6, TFT_BLACK); // Tour noir
watch->tft->drawRoundRect(41, 31, 58, 58, 6, TFT_LIGHTGREY); // Tour gris clair
watch->tft->fillRoundRect(42, 32, 56, 56, 6, TFT_OLIVE); // Intérieur
//watch->tft->drawFastVLine(41,56,47,TFT_DARKGREY); // Ligne verticale en TFT_DARKGREY
#include "reveil_img.h" // script de l'img calc
watch->tft->drawXBitmap(52, 44, reveil_img_bits, reveil_img_width, reveil_img_height, TFT_GOLD, TFT_OLIVE); // Affichage icone reveil (appli alarme)

// Icône 2
watch->tft->drawRoundRect(140, 30, 60, 60, 6, TFT_BLACK); // Tour noir
watch->tft->drawRoundRect(141, 31, 58, 58, 6, TFT_LIGHTGREY); // Tour gris clair
watch->tft->fillRoundRect(142, 32, 56, 56, 6, TFT_PURPLE); // Intérieur
//watch->tft->drawFastVLine(141,56,47,TFT_DARKGREY); // Ligne verticale en TFT_DARKGREY
#include "chrono_img.h" // script de l'img chrono
watch->tft->drawXBitmap(152, 45, chrono_img_bits, chrono_img_width, chrono_img_height, TFT_MAGENTA, TFT_PURPLE); // Affichage icone chrono

// Icône 3
watch->tft->drawRoundRect(40, 100, 60, 60, 6, TFT_BLACK); // Tour noir
watch->tft->drawRoundRect(41, 101, 58, 58, 6, TFT_LIGHTGREY); // Tour gris clair
watch->tft->fillRoundRect(42, 102, 56, 56, 6, TFT_MAROON); // Intérieur
#include "jeux_img.h" // script de l'img jeux
watch->tft->drawXBitmap(51, 110, jeux_img_bits, jeux_img_width, jeux_img_height, TFT_ORANGE, TFT_MAROON); // Affichage icone jeux

// Icône 4
watch->tft->drawRoundRect(140, 100, 60, 60, 6, TFT_BLACK); // Tour noir
watch->tft->drawRoundRect(141, 101, 58, 58, 6, TFT_LIGHTGREY); // Tour gris clair
watch->tft->fillRoundRect(142, 102, 56, 56, 6, TFT_DARKCYAN); // Intérieur
#include "calc_img.h" // script de l'img calc
watch->tft->drawXBitmap(154, 110, calc_img_bits, calc_img_width, calc_img_height, TFT_RED, TFT_DARKCYAN); // Affichage icone calculatrice

// Icône 5
watch->tft->drawRoundRect(40, 170, 60, 60, 6, TFT_BLACK); // Tour noir
watch->tft->drawRoundRect(41, 171, 58, 58, 6, TFT_LIGHTGREY); // Tour gris clair
watch->tft->fillRoundRect(42, 172, 56, 56, 6, TFT_DARKGREEN); // Intérieur
#include "lampe_img.h" // script de l'img lampe
watch->tft->drawXBitmap(55, 183, lampe_img_bits, lampe_img_width, lampe_img_height, TFT_BLACK, TFT_DARKGREEN); // Affichage icone lampe

// Icône 6
watch->tft->drawRoundRect(140, 170, 60, 60, 6, TFT_BLACK); // Tour noir
watch->tft->drawRoundRect(141, 171, 58, 58, 6, TFT_LIGHTGREY); // Tour gris clair
watch->tft->fillRoundRect(142, 172, 56, 56, 6, TFT_NAVY); // Intérieur
#include "tools_img.h" // script de l'img tools
watch->tft->drawXBitmap(155, 183, tools_img_bits, tools_img_width, tools_img_height, TFT_BLUE, TFT_NAVY); // Affichage icone tools

Serial.print("avant x: "); Serial.print(x); Serial.print(" - y: "); Serial.println(y);

while (!watch->getTouch(x, y)) {}
while (watch->getTouch(x, y)) {} // Attend qu'on touche

Serial.print("apres x: "); Serial.print(x); Serial.print(" - y: "); Serial.println(y);
if (x > 10 && x < 120 && y > 20 && y < 95) {
  Serial.println("Lancement Appli Réveil");
  #include "alarme.h"
}
if (x > 120 && x < 240 && y > 20 && y < 95) {
  Serial.println("Lancement Appli Chrono");
  #include "chrono.h"
}
if (x > 10 && x < 120 && y > 95 && y < 165) {
  Serial.println("Lancement Appli Jeux");
  #include "jeux.h"
}
if (x > 120 && x < 240 && y > 95 && y < 165) {
  Serial.println("Lancement Appli Calculatrice");
  #include "calc.h"
}
if (x > 10 && x < 120 && y > 165 && y < 240) {
  Serial.println("Lancement Appli Lampe");
  #include "lampe.h"
}
if (x > 120 && x < 240 && y > 165 && y < 240) {
  Serial.println("Lancement Appli Réglages date & heure");
  #include "set-time.h"
}


Serial.println("");
watch->tft->fillScreen(TFT_BLACK);
