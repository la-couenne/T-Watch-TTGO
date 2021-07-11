// Application Clock
// Création de la page principale avec en paramètre: si 0->mise à jour juste des deux points, 1->MàJ de l'affichage complet
TFT_eSPI *tft = watch->tft;
Serial.println("Mise à jour écran horloge (1x/min)");
byte xpos = 40; // Coordonnée de la position de l'heure
byte ypos = 90;
byte xcolon = 0; // Coordonnée de la position des 2 points

RTC_Date tnow = watch->rtc->getDateTime(); // Récupérons les données actuelles
hh = tnow.hour;
mm = tnow.minute;
ss = tnow.second;
dday = tnow.day;
mmonth = tnow.month;
yyear = tnow.year;

watch->tft->fillScreen(TFT_BLACK); // fond
watch->tft->setTextSize(2);

// Allume le périphérique ADC de la batterie pour lire les valeurs
watch->power->adc1Enable(AXP202_VBUS_VOL_ADC1 | AXP202_VBUS_CUR_ADC1 | AXP202_BATT_CUR_ADC1 | AXP202_BATT_VOL_ADC1, true);
int per = watch->power->getBattPercentage();
if (per > 79) watch->tft->setTextColor(TFT_GREEN);
if (per > 39 && per < 80) watch->tft->setTextColor(TFT_ORANGE);
if (per < 40) watch->tft->setTextColor(TFT_RED);
watch->tft->setCursor(106, 5);
watch->tft->print("Batt: "); watch->tft->print(per); watch->tft->print(" %");

watch->tft->setTextSize(1);
watch->tft->drawFastHLine(0,25,240,TFT_WHITE); // dessine une ligne
// L'écriture 7 est un style 7-segment (/!\ on ne peut utiliser que les caractères: 0 1 2 3 4 5 6 7 8 9 0 : . et espace)
watch->tft->setTextColor(0x39C4, TFT_BLACK); // Définir la couleur souhaitée
watch->tft->drawString("88:88", xpos, ypos, 7);
watch->tft->setTextColor(0xFBE0, TFT_BLACK); // Orange

if (hh < 10) xpos += watch->tft->drawChar('0', xpos, ypos, 7);
xpos += watch->tft->drawNumber(hh, xpos, ypos, 7);
xcolon = xpos + 3;
xpos += watch->tft->drawChar(':', xcolon, ypos, 7);
if (mm < 10) xpos += watch->tft->drawChar('0', xpos, ypos, 7);
watch->tft->drawNumber(mm, xpos, ypos, 7);

watch->tft->setTextSize(3);
watch->tft->setCursor( 10, 160);
watch->tft->setTextSize(2);
watch->tft->print(" Nous sommes le ");
if (dday == 1) {
  watch->tft->print("1er");
} else {
  watch->tft->print(dday); // dday / ss
}
watch->tft->setTextSize(3);

#include "menu_img.h" // script de l'img menu
watch->tft->drawXBitmap(105,200, menu_img_bits, menu_img_width, menu_img_height, TFT_WHITE, TFT_BLACK); // Affichage icone menu
#include "medic_img.h" // script de l'img calc
watch->tft->drawXBitmap(35,200, medic_img_bits, medic_img_width, medic_img_height, TFT_DARKGREY, TFT_BLACK); // Affichage icone médic
#include "memo_img.h" // script de l'img memo
watch->tft->drawXBitmap(170,200, memo_img_bits, memo_img_width, memo_img_height, TFT_DARKGREY, TFT_BLACK); // Affichage icone memo
