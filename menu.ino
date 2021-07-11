#include "config.h"
#include <time.h>
#include <soc/rtc.h>
TTGOClass *ttgo;
#include "esp_sleep.h"
#include <LilyGoWatch.h>
#include <pgmspace.h> // On ajoute cette bibliothèque pour la gestion des img

// Variables pour la mise en veille:
TTGOClass *watch = nullptr;
AXP20X_Class *power;
TFT_eSPI *tft = nullptr;
bool KeyPressed = false;
bool lenergy = false; // sert a déterminer si on est deja en veille
int eveil = 0;
int seconde = 0;
static bool irq_axp202 = false; // Utilisé pour le bouton pour l'interruption qui permet de mettre/sortir de la veille
#define temps_avant_veille  3*1000 // Temps avant veille automatique
// Variables pour l'heure:
uint8_t hh, mm, ss, mmonth, dday; // H, M, S variables
uint16_t yyear; // Year is 16 bit int
// Variables pour le menu
const int maxApp = 6; // nombre d'applications
String appName[maxApp] = {"Retour", "Alarme", "Mémo", "Battery", "Jeux", "Set Time"}; // noms des applications
String memorum = ""; // Utilisé dans l'appli "memorum"

void mise_veille() // Mise en veille légère (On/Off)
{
    if ( watch->bl->isOn()) { // Si le rétro-éclairage est actif >> passe en mode light sleep. Le Core de l'ESP32 reste actif
        Serial.println("Rétro-éclairage actif -> activation du light sleep");
        watch->closeBL(); // Eteint le rétro-éclairage
        watch->displaySleep(); // Eteint l'écran
        lenergy = true; // sert a déterminer si on est deja en veille
        setCpuFrequencyMhz(10); // Diminue la fréquence du CPU à 10MHz pour réduire la consommation
        Serial.println("Diminution du CPU à 10Mhz");
        Serial.println("ENTER IN LIGHT SLEEP MODE");
        Serial.println(" ");
        delay(50);
        gpio_wakeup_enable ((gpio_num_t)AXP202_INT, GPIO_INTR_LOW_LEVEL); // On prévoit de faire le réveil avec le bouton principal
        esp_sleep_enable_gpio_wakeup(); // Active le réveille depuis le GPIO
        esp_light_sleep_start(); // Met en veille légère. Le Core du CPU continue de fonctionner
    } else { // Si le rétro-éclairage est éteint -> réveil
      lenergy = false; // sert a déterminer si on est deja en veille
      setCpuFrequencyMhz(160); // Relance de la fréquence du CPU à 160MHz (utile si haut? On peut aller jusqu'à 240)
      Serial.println("Augmentation du CPU à 160Mhz");
      resetChrono(); // On remet à 0 le chronomètre pour la mise en veille automatique de l'écran
      Serial.println("Reveil ESP32 and accessories");
      Serial.println(" ");
      watch->displayWakeup(); // Allume l'écran
      watch->openBL(); // Allume le rétro-éclairage
      watch->rtc->syncToSystem(); // Mise à jour de l'heure du système sur le module RTC
      delay(100);
    }
}


void setMenuDisplay(int mSel) // Affichage du menu
{
    int curSel = 0;
    // En-tête du mode d'affichage
    watch->tft->fillScreen(TFT_BLUE);
    watch->tft->fillRect(0, 80, 239, 80, TFT_BLACK);

    // Afficher les applications
    if (mSel == 0) curSel = maxApp - 1;
    else curSel = mSel - 1;

    watch->tft->setTextSize(2);
    watch->tft->setTextColor(TFT_GREEN);
    watch->tft->setCursor(50, 30);
    watch->tft->println(appName[curSel]);

    watch->tft->setTextSize(3);
    watch->tft->setTextColor(TFT_RED);
    watch->tft->setCursor(40, 110);
    watch->tft->println(appName[mSel]);

    if (mSel == maxApp - 1) curSel = 0;
    else curSel = mSel + 1;

    watch->tft->setTextSize(2);
    watch->tft->setTextColor(TFT_GREEN);
    watch->tft->setCursor(50, 190);
    watch->tft->print(appName[curSel]);
}


void setup() {
  Serial.begin(115200);
  watch = TTGOClass::getWatch();
  watch->begin(); // Initialisation du matériel
  power = watch->power; // Enregistre les pointeurs
  watch->openBL(); // Allume le rétro-éclairage
  
  // Active les IRQ utilisés
  watch->power->adc1Enable(AXP202_BATT_VOL_ADC1 | AXP202_BATT_CUR_ADC1 | AXP202_VBUS_VOL_ADC1 | AXP202_VBUS_CUR_ADC1, AXP202_ON);
  watch->power->enableIRQ(AXP202_VBUS_REMOVED_IRQ | AXP202_VBUS_CONNECT_IRQ | AXP202_CHARGING_FINISHED_IRQ, AXP202_ON);
  watch->power->clearIRQ();
  
  // Éteindre l'alimentation non utilisée
  watch->power->setPowerOutPut(AXP202_EXTEN, AXP202_OFF);
  watch->power->setPowerOutPut(AXP202_DCDC2, AXP202_OFF);
  watch->power->setPowerOutPut(AXP202_LDO3, AXP202_OFF);
  watch->power->setPowerOutPut(AXP202_LDO4, AXP202_OFF);   
  
  // Interruption qui permet de mettre en veille légère ou réveiller l'écran (ici avec le bouton, ajouter le toucher de l'écran??)
  pinMode(AXP202_INT, INPUT);
  attachInterrupt(AXP202_INT, [] {
      irq_axp202 = true;
  }, FALLING);
  watch->power->enableIRQ(AXP202_PEK_SHORTPRESS_IRQ | AXP202_VBUS_REMOVED_IRQ | AXP202_VBUS_CONNECT_IRQ | AXP202_CHARGING_IRQ, true);
  watch->power->clearIRQ();

  // Démarre le chronomètre pour la mise en veille automatique
  eveil = millis(); // millis() retourne le nb de sec depuis la mise sous tension
  resetChrono();
  
  watch->rtc->check(); //Vérifiez si l'horloge RTC correspond, sinon utilisez l'heure de la compilation du programme
  watch->rtc->syncToSystem(); //Synchroniser l'heure avec l'heure du système

  #include "clock.h" // Crée la page horloge
}


void loop() {
  int16_t x, y;  
  if ( watch->getTouch(x,y) ) { // si touche écran
    if (x > 100 && x < 240 && y > 0 && y < 30) { // Si au meme endroit qu'où le nivo de batterie est affiché
      delay(200);
      #include "batterie.h" // Lancement appli "batterie stat"
      lenergy = false; // afin que l'affichage de l'heure se mette à jour
    }
    
    if (x > 0 && x < 80 && y > 170 && y < 240) { // Si au meme endroit que l'img calc
      #include "medic_img.h" // script de l'img medic
      watch->tft->drawXBitmap(35,200, medic_img_bits, medic_img_width, medic_img_height, TFT_RED, TFT_BLACK); // Affichage icone calc en Rouge car touchée
      delay(200);
      #include "medic.h" // Lancement appli "medic"
      lenergy = false; // afin que l'affichage de l'heure se mette à jour
    }

  if (x > 80 && x < 160 && y > 170 && y < 240) { // Si au meme endroit que l'img menu
    #include "menu.h" // Affichage du menu
    lenergy = false; // afin que l'affichage de l'heure se mette à jour
  }
  
  if (x > 160 && x < 240 && y > 170 && y < 240) { // Si au meme endroit que l'img memo
    #include "memo_img.h" // script de l'img memo
    watch->tft->drawXBitmap(170,200, memo_img_bits, memo_img_width, memo_img_height, TFT_RED, TFT_BLACK); // Affichage icone memo en Rouge car touchée
    delay(200);
    #include "memo.h" // Lancement appli "Memo"
    lenergy = false; // afin que l'affichage de l'heure se mette à jour
  }
  eveil = millis(); // initalisation du timing avant la veille quand on relâche
  } // fin si touche écran
  
  if ( millis() - eveil > temps_avant_veille) { // Lorsqu'on dépasse le temps d'inactivité -> met en veille l'écran et les périphériques de la montre
    if ( !lenergy) { // si pas deja en veille
      eveil = millis();
      mise_veille(); // appelle fonction veille
    }  
  }

  // L'utilisateur vient d'appuyer sur le bouton principal pour la sortie de veille
  if (irq_axp202 && lenergy) { // si interuption irq & lenergy=false (donc pas deja en veille)
    Serial.println("Interuption détectée..");
    irq_axp202 = false;
    watch->power->readIRQ();
    if ( watch->power->isPEKShortPressIRQ() ) {
      Serial.println("Bouton enfoncé -> lancement de la mise en veille");
      mise_veille();
    }     
    watch->power->clearIRQ();
  }
}
// Reset du chronomètre pour la mise en veille automatique de l'écran (mode light sleep)
void resetChrono()
{
  seconde = millis();
  eveil = millis();
  #include "clock.h" // Crée la page horloge
}
