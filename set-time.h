// Application pr mettre à jour l'horloge
// Pour la liste des couleurs: https://diyprojects.io/ttgo-t-watch-get-started-esp32-tft_espi-library/#.YBvqJOhKhPY
watch->tft->fillScreen(TFT_BLACK); // Efface l'écran
watch->tft->setTextSize(2);
delay(500); // pause afin qu'on relèvre le doigt

int jour = 0;
int mois = 0;
int annee = 0;
int heures = 0;
int minutes = 0;
int annuler = 0;

// Récupérer les informations actuelles
RTC_Date tnow = watch->rtc->getDateTime();

hh = tnow.hour;
mm = tnow.minute;
ss = tnow.second;
dday = tnow.day;
mmonth = tnow.month;
yyear = tnow.year;

watch->tft->setTextColor(TFT_GREEN); // On affiche sur la 1ere ligne JJ.MM.AAAA HH:MM
watch->tft->setCursor(5, 5);
watch->tft->setTextColor(TFT_RED);
watch->tft->print(dday);
watch->tft->setTextColor(TFT_GREEN);
watch->tft->print("."); watch->tft->print(mmonth); watch->tft->print("."); watch->tft->print(yyear); watch->tft->print(" ");
watch->tft->print(hh); watch->tft->print(":"); watch->tft->print(mm);

// Afficher les boutons d'interface fillRect(posX coin ht gauche, posY coin ht gauche, largeur, hauteur, arrondi, couleur);
watch->tft->fillRoundRect(6, 35, 74, 48, 6, TFT_DARKGREY); // touche 1
watch->tft->fillRoundRect(87, 35, 72, 48, 6, TFT_DARKGREY); // touche 2
watch->tft->fillRoundRect(165, 35, 70, 48, 6, TFT_DARKGREY); // touche 3
watch->tft->fillRoundRect(6, 85, 74, 48, 6, TFT_DARKGREY); // touche 4
watch->tft->fillRoundRect(87, 85, 72, 48, 6, TFT_DARKGREY); // touche 5
watch->tft->fillRoundRect(165, 85, 70, 48, 6, TFT_DARKGREY); // touche 6
watch->tft->fillRoundRect(6, 135, 74, 48, 6, TFT_DARKGREY); // touche 7
watch->tft->fillRoundRect(87, 135, 72, 48, 6, TFT_DARKGREY); // touche 8
watch->tft->fillRoundRect(165, 135, 70, 48, 6, TFT_DARKGREY); // touche 9
watch->tft->fillRoundRect(6, 185, 74, 48, 6, TFT_DARKGREY); // touche 0
watch->tft->setTextColor(TFT_WHITE);
watch->tft->drawNumber(1, 30, 40, 2);
watch->tft->drawNumber(2, 110, 40, 2);
watch->tft->drawNumber(3, 190, 40, 2);
watch->tft->drawNumber(4, 30, 90, 2);
watch->tft->drawNumber(5, 110, 90, 2);
watch->tft->drawNumber(6, 190, 90, 2);
watch->tft->drawNumber(7, 30, 140, 2);
watch->tft->drawNumber(8, 110, 140, 2);
watch->tft->drawNumber(9, 190, 140, 2);
watch->tft->drawNumber(0, 30, 190, 2);
watch->tft->fillRoundRect(120, 200, 119, 39, 6, TFT_WHITE);
watch->tft->setTextSize(2);

watch->tft->setCursor(140, 210);
watch->tft->setTextColor(TFT_BLACK);
watch->tft->print("Annuler");
watch->tft->setTextColor(TFT_WHITE);
int wl = 0; // Suivre le numéro actuel sélectionné
byte curnum = 1;  // Suivre sur quel chiffre nous sommes

while (!watch->getTouch(x, y)) {} // Attend qu'on touche
int16_t x, y;
watch->getTouch(x, y); // on récupère où l'on a touché
// Pr rapel fillRect(posX coin ht gauche, posY coin ht gauche, largeur, hauteur, couleur);
// donc on cherche X: entre 'posX coin ht gauche' et 'largeur'
// et Y: entre 'posY coin ht gauche' et (posY coin ht gauche + 'hauteur')
watch->tft->setTextColor(TFT_GREEN);


/*   x:0    80    160   240
 *y:35 +-----+-----+-----+
 *     |  1  |  2  |  3  |
 *  85 +-----+-----+-----+
 *     |  1  |  2  |  3  |
 * 135 +-----+-----+-----+
 *     |  1  |  2  |  3  |
 * 185 +-----+-----+-----+
 * 
*/

//-----------------------------
// On s'occupe du premier chiffre du jour
if (x > 0 && x < 80 && y > 35 && y < 85) {
  Serial.println("Pour le 1er chiffre du jour: Bouton 1");
  jour = 10; // Bouton 1 -> 10
}
if (x > 80 && x < 160 && y > 35 && y < 85) {
  Serial.println("Pour le 1er chiffre du jour: Bouton 2");
  jour = 20; // Bouton 2 -> 20
}
if (x > 160 && x < 240 && y > 35 && y < 85) {
  Serial.println("Pour le 1er chiffre du jour: Bouton 3");
  jour = 30; // Bouton 3 -> 30
}
// Pas besoin des autres boutons car pour les jours on ne peut pas aller à + de 3
if (x > 0 && x < 80 && y > 185 && y < 235) {
  Serial.println("Pour le 1er chiffre du jour: Bouton 0");
  jour = 0; // Bouton 0 -> 0
}
if (x > 120 && x < 240 && y > 199 && y < 238) {
  Serial.println("On a appuyé sur le bouton Annuler..");
  annuler = 1;
}
Serial.print("X = "); Serial.println(x);
Serial.print("Y = "); Serial.println(y);
watch->tft->setCursor(5, 5);
watch->tft->fillRect(0, 0, 200, 20, TFT_BLACK); // rectangle noir pr cacher l'ancienne heure
watch->tft->print((jour / 10)); // on ré-écrit le permier chiffre du jour
while (watch->getTouch(x, y)) {}
while (!watch->getTouch(x, y)) {} // Attend qu'on touche

//-----------------------------
if (annuler != 1) {
  // On s'occupe du 2eme chiffre du jour
  watch->getTouch(x, y); // on récupère où l'on a touché
  if (x > 0 && x < 80 && y > 35 && y < 85) {
    Serial.println("Pour le 2eme chiffre du jour: Bouton 1");
    watch->tft->print("1"); // on ré-écrit le 2eme chiffre du jour
    jour = (jour + 1); // Bouton 1 -> +1
  }
  if (x > 80 && x < 160 && y > 35 && y < 85) {
    Serial.println("Pour le 2eme chiffre du jour: Bouton 2");
    watch->tft->print("2"); // on ré-écrit le 2eme chiffre du jour
    jour = (jour + 2); // Bouton 2 -> +2
  }
  if (x > 160 && x < 240 && y > 35 && y < 85) {
    Serial.println("Pour le 2eme chiffre du jour: Bouton 3");
    watch->tft->print("3"); // on ré-écrit le 2eme chiffre du jour
    jour = (jour + 3); // Bouton 3 -> +3
  }
  if (x > 0 && x < 80 && y > 85 && y < 135) {
    Serial.println("Pour le 2eme chiffre du jour: Bouton 4");
    watch->tft->print("4"); // on ré-écrit le 2eme chiffre du jour
    jour = (jour + 4); // Bouton 4 -> +4
  }
  if (x > 80 && x < 160 && y > 85 && y < 135) {
    Serial.println("Pour le 2eme chiffre du jour: Bouton 5");
    watch->tft->print("5"); // on ré-écrit le 2eme chiffre du jour
    jour = (jour + 5); // Bouton 5 -> +5
  }
  if (x > 160 && x < 240 && y > 85 && y < 135) {
    Serial.println("Pour le 2eme chiffre du jour: Bouton 6");
    watch->tft->print("6"); // on ré-écrit le 2eme chiffre du jour
    jour = (jour + 6); // Bouton 6 -> +6
  }
  if (x > 0 && x < 80 && y > 135 && y < 185) {
    Serial.println("Pour le 2eme chiffre du jour: Bouton 7");
    watch->tft->print("7"); // on ré-écrit le 2eme chiffre du jour
    jour = (jour + 7); // Bouton 7 -> +7
  }
  if (x > 80 && x < 160 && y > 135 && y < 185) {
    Serial.println("Pour le 2eme chiffre du jour: Bouton 8");
    watch->tft->print("8"); // on ré-écrit le 2eme chiffre du jour
    jour = (jour + 8); // Bouton 8 -> +8
  }
  if (x > 160 && x < 240 && y > 135 && y < 185) {
    Serial.println("Pour le 2eme chiffre du jour: Bouton 9");
    watch->tft->print("9"); // on ré-écrit le 2eme chiffre du jour
    jour = (jour + 9); // Bouton 9 -> +9
  }
  if (x > 0 && x < 80 && y > 185 && y < 235) {
    Serial.println("Pour le 2eme chiffre du jour: Bouton 0");
    watch->tft->print("0"); // on ré-écrit le 2eme chiffre du jour
    jour = (jour + 0); // Bouton 0 -> +0
  }
  if (x > 120 && x < 240 && y > 199 && y < 238) {
    Serial.println("On a appuyé sur le bouton Annuler..");
    annuler = 1;
  }
  Serial.print("X = "); Serial.println(x);
  Serial.print("Y = "); Serial.println(y);
  watch->tft->print(".");
  while (watch->getTouch(x, y)) {}
  while (!watch->getTouch(x, y)) {} // Attend qu'on touche
}

//-----------------------------
// On s'occupe du premier chiffre du mois
if (x > 0 && x < 80 && y > 35 && y < 85) {
  Serial.println("Pour le 1er chiffre du mois: Bouton 1");
  mois = 10; // Bouton 1 -> 10
}
// Pas besoin des autres boutons car pour les mois on ne peut pas aller à + de 1
if (x > 0 && x < 80 && y > 185 && y < 235) {
  Serial.println("Pour le 1er chiffre du mois: Bouton 0");
  mois = 0; // Bouton 0 -> 0
}
if (x > 120 && x < 240 && y > 199 && y < 238) {
  Serial.println("On a appuyé sur le bouton Annuler..");
  annuler = 1;
}
Serial.print("X = "); Serial.println(x);
Serial.print("Y = "); Serial.println(y);
watch->tft->print((mois / 10)); // on ré-écrit le permier chiffre du mois
while (watch->getTouch(x, y)) {}
while (!watch->getTouch(x, y)) {} // Attend qu'on touche

//-----------------------------
if (annuler != 1) {
  // On s'occupe du 2eme chiffre du mois
  watch->getTouch(x, y); // on récupère où l'on a touché
  if (x > 0 && x < 80 && y > 35 && y < 85) {
    Serial.println("Pour le 2eme chiffre du mois: Bouton 1");
    watch->tft->print("1"); // on ré-écrit le 2eme chiffre du mois
    mois = (mois + 1); // Bouton 1 -> +1
  }
  if (x > 80 && x < 160 && y > 35 && y < 85) {
    Serial.println("Pour le 2eme chiffre du mois: Bouton 2");
    watch->tft->print("2"); // on ré-écrit le 2eme chiffre du mois
    mois = (mois + 2); // Bouton 2 -> +2
  }
  if (x > 160 && x < 240 && y > 35 && y < 85) {
    Serial.println("Pour le 2eme chiffre du mois: Bouton 3");
    watch->tft->print("3"); // on ré-écrit le 2eme chiffre du mois
    mois = (mois + 3); // Bouton 3 -> +3
  }
  if (x > 0 && x < 80 && y > 85 && y < 135) {
    Serial.println("Pour le 2eme chiffre du mois: Bouton 4");
    watch->tft->print("4"); // on ré-écrit le 2eme chiffre du mois
    mois = (mois + 4); // Bouton 4 -> +4
  }
  if (x > 80 && x < 160 && y > 85 && y < 135) {
    Serial.println("Pour le 2eme chiffre du mois: Bouton 5");
    watch->tft->print("5"); // on ré-écrit le 2eme chiffre du mois
    mois = (mois + 5); // Bouton 5 -> +5
  }
  if (x > 160 && x < 240 && y > 85 && y < 135) {
    Serial.println("Pour le 2eme chiffre du mois: Bouton 6");
    watch->tft->print("6"); // on ré-écrit le 2eme chiffre du mois
    mois = (mois + 6); // Bouton 6 -> +6
  }
  if (x > 0 && x < 80 && y > 135 && y < 185) {
    Serial.println("Pour le 2eme chiffre du mois: Bouton 7");
    watch->tft->print("7"); // on ré-écrit le 2eme chiffre du mois
    mois = (mois + 7); // Bouton 7 -> +7
  }
  if (x > 80 && x < 160 && y > 135 && y < 185) {
    Serial.println("Pour le 2eme chiffre du mois: Bouton 8");
    watch->tft->print("8"); // on ré-écrit le 2eme chiffre du mois
    mois = (mois + 8); // Bouton 8 -> +8
  }
  if (x > 160 && x < 240 && y > 135 && y < 185) {
    Serial.println("Pour le 2eme chiffre du mois: Bouton 9");
    watch->tft->print("9"); // on ré-écrit le 2eme chiffre du mois
    mois = (mois + 9); // Bouton 9 -> +9
  }
  if (x > 0 && x < 80 && y > 185 && y < 235) {
    Serial.println("Pour le 2eme chiffre du mois: Bouton 0");
    watch->tft->print("0"); // on ré-écrit le 2eme chiffre du mois
    mois = (mois + 0); // Bouton 0 -> +0
  }
  if (x > 120 && x < 240 && y > 199 && y < 238) {
    Serial.println("On a appuyé sur le bouton Annuler..");
    annuler = 1;
  }
  Serial.print("X = "); Serial.println(x);
  Serial.print("Y = "); Serial.println(y);
  watch->tft->print(".202"); // On affiche l'année sans le dernier chiffre
  while (watch->getTouch(x, y)) {}
  while (!watch->getTouch(x, y)) {} // Attend qu'on touche
}

//-----------------------------
if (annuler != 1) {
  // On s'occupe du 1er chiffre de l'année
  watch->getTouch(x, y); // on récupère où l'on a touché
  if (x > 0 && x < 80 && y > 35 && y < 85) {
    Serial.println("Pour le 1er chiffre de l'année: Bouton 1");
    watch->tft->print("1"); // on ré-écrit le 2eme chiffre de l'année
    annee = 2021;
  }
  if (x > 80 && x < 160 && y > 35 && y < 85) {
    Serial.println("Pour le 2eme chiffre de l'année: Bouton 2");
    watch->tft->print("2"); // on ré-écrit le 2eme chiffre de l'année
    annee = 2022;
  }
  if (x > 160 && x < 240 && y > 35 && y < 85) {
    Serial.println("Pour le 2eme chiffre de l'année: Bouton 3");
    watch->tft->print("3"); // on ré-écrit le 2eme chiffre de l'année
    annee = 2023;
  }
  if (x > 0 && x < 80 && y > 85 && y < 135) {
    Serial.println("Pour le 2eme chiffre de l'année: Bouton 4");
    watch->tft->print("4"); // on ré-écrit le 2eme chiffre de l'année
    annee = 2024;
  }
  if (x > 80 && x < 160 && y > 85 && y < 135) {
    Serial.println("Pour le 2eme chiffre de l'année: Bouton 5");
    watch->tft->print("5"); // on ré-écrit le 2eme chiffre de l'année
    annee = 2025;
  }
  if (x > 160 && x < 240 && y > 85 && y < 135) {
    Serial.println("Pour le 2eme chiffre de l'année: Bouton 6");
    watch->tft->print("6"); // on ré-écrit le 2eme chiffre de l'année
    annee = 2026;
  }
  if (x > 0 && x < 80 && y > 135 && y < 185) {
    Serial.println("Pour le 2eme chiffre de l'année: Bouton 7");
    watch->tft->print("7"); // on ré-écrit le 2eme chiffre de l'année
    annee = 2027;
  }
  if (x > 80 && x < 160 && y > 135 && y < 185) {
    Serial.println("Pour le 2eme chiffre de l'année: Bouton 8");
    watch->tft->print("8"); // on ré-écrit le 2eme chiffre de l'année
    annee = 2028;
  }
  if (x > 160 && x < 240 && y > 135 && y < 185) {
    Serial.println("Pour le 2eme chiffre de l'année: Bouton 9");
    watch->tft->print("9"); // on ré-écrit le 2eme chiffre de l'année
    annee = 2029;
  }
  if (x > 0 && x < 80 && y > 185 && y < 235) {
    Serial.println("Pour le 2eme chiffre de l'année: Bouton 0");
    watch->tft->print("0"); // on ré-écrit le 2eme chiffre de l'année
    annee = 2020;
  }
  if (x > 120 && x < 240 && y > 199 && y < 238) {
    Serial.println("On a appuyé sur le bouton Annuler..");
    annuler = 1;
  }
  Serial.print("X = "); Serial.println(x);
  Serial.print("Y = "); Serial.println(y);
  watch->tft->print(" ");
  while (watch->getTouch(x, y)) {}
  while (!watch->getTouch(x, y)) {} // Attend qu'on touche
}

//-----------------------------
if (annuler != 1) {
  // On s'occupe du premier chiffre de l'heure
  if (x > 0 && x < 80 && y > 35 && y < 85) {
    Serial.println("Pour le 1er chiffre de l'heure: Bouton 1");
    heures = 10; // Bouton 1 -> 10
  }
  if (x > 80 && x < 160 && y > 35 && y < 85) {
    Serial.println("Pour le 1er chiffre de l'heure: Bouton 2");
    heures = 20; // Bouton 2 -> 20
  }
  // Pas besoin des autres boutons car pour les heures on ne peut pas aller à + de 2
  if (x > 0 && x < 80 && y > 185 && y < 235) {
    Serial.println("Pour le 1er chiffre de l'heure: Bouton 0");
    heures = 0; // Bouton 0 -> 0
  }
  if (x > 120 && x < 240 && y > 199 && y < 238) {
    Serial.println("On a appuyé sur le bouton Annuler..");
    annuler = 1;
  }
  Serial.print("X = "); Serial.println(x);
  Serial.print("Y = "); Serial.println(y);
  watch->tft->print((heures / 10)); // on ré-écrit le permier chiffre de l'heure
  while (watch->getTouch(x, y)) {}
  while (!watch->getTouch(x, y)) {} // Attend qu'on touche
}

//-----------------------------
if (annuler != 1) {
  // On s'occupe du 2eme chiffre de l'heure
  watch->getTouch(x, y); // on récupère où l'on a touché
  if (x > 0 && x < 80 && y > 35 && y < 85) {
    Serial.println("Pour le 2eme chiffre de l'heure: Bouton 1");
    watch->tft->print("1"); // on ré-écrit le 2eme chiffre de l'heure
    heures = (heures + 1); // Bouton 1 -> +1
  }
  if (x > 80 && x < 160 && y > 35 && y < 85) {
    Serial.println("Pour le 2eme chiffre de l'heure: Bouton 2");
    watch->tft->print("2"); // on ré-écrit le 2eme chiffre de l'heure
    heures = (heures + 2); // Bouton 2 -> +2
  }
  if (x > 160 && x < 240 && y > 35 && y < 85) {
    Serial.println("Pour le 2eme chiffre de l'heure: Bouton 3");
    watch->tft->print("3"); // on ré-écrit le 2eme chiffre de l'heure
    heures = (heures + 3); // Bouton 3 -> +3
  }
  if (x > 0 && x < 80 && y > 85 && y < 135) {
    Serial.println("Pour le 2eme chiffre de l'heure: Bouton 4");
    watch->tft->print("4"); // on ré-écrit le 2eme chiffre de l'heure
    heures = (heures + 4); // Bouton 4 -> +4
  }
  if (x > 80 && x < 160 && y > 85 && y < 135) {
    Serial.println("Pour le 2eme chiffre de l'heure: Bouton 5");
    watch->tft->print("5"); // on ré-écrit le 2eme chiffre de l'heure
    heures = (heures + 5); // Bouton 5 -> +5
  }
  if (x > 160 && x < 240 && y > 85 && y < 135) {
    Serial.println("Pour le 2eme chiffre de l'heure: Bouton 6");
    watch->tft->print("6"); // on ré-écrit le 2eme chiffre de l'heure
    heures = (heures + 6); // Bouton 6 -> +6
  }
  if (x > 0 && x < 80 && y > 135 && y < 185) {
    Serial.println("Pour le 2eme chiffre de l'heure: Bouton 7");
    watch->tft->print("7"); // on ré-écrit le 2eme chiffre de l'heure
    heures = (heures + 7); // Bouton 7 -> +7
  }
  if (x > 80 && x < 160 && y > 135 && y < 185) {
    Serial.println("Pour le 2eme chiffre de l'heure: Bouton 8");
    watch->tft->print("8"); // on ré-écrit le 2eme chiffre de l'heure
    heures = (heures + 8); // Bouton 8 -> +8
  }
  if (x > 160 && x < 240 && y > 135 && y < 185) {
    Serial.println("Pour le 2eme chiffre de l'heure: Bouton 9");
    watch->tft->print("9"); // on ré-écrit le 2eme chiffre de l'heure
    heures = (heures + 9); // Bouton 9 -> +9
  }
  if (x > 0 && x < 80 && y > 185 && y < 235) {
    Serial.println("Pour le 2eme chiffre de l'heure: Bouton 0");
    watch->tft->print("0"); // on ré-écrit le 2eme chiffre de l'heure
    heures = (heures + 0); // Bouton 0 -> +0
  }
  if (x > 120 && x < 240 && y > 199 && y < 238) {
    Serial.println("On a appuyé sur le bouton Annuler..");
    annuler = 1;
  }
  Serial.print("X = "); Serial.println(x);
  Serial.print("Y = "); Serial.println(y);
  watch->tft->print(":");
  while (watch->getTouch(x, y)) {}
  while (!watch->getTouch(x, y)) {} // Attend qu'on touche
}

//-----------------------------
if (annuler != 1) {
  // On s'occupe du 1er chiffre des minutes
  watch->getTouch(x, y); // on récupère où l'on a touché
  if (x > 0 && x < 80 && y > 35 && y < 85) {
    Serial.println("Pour le 1er chiffre des minutes: Bouton 1");
    minutes = 10; // Bouton 1 -> 10
  }
  if (x > 80 && x < 160 && y > 35 && y < 85) {
    Serial.println("Pour le 1er chiffre des minutes: Bouton 2");
    minutes = 20; // Bouton 2 -> 20
  }
  if (x > 160 && x < 240 && y > 35 && y < 85) {
    Serial.println("Pour le 1er chiffre des minutes: Bouton 3");
    minutes = 30; // Bouton 3 -> 30
  }
  if (x > 0 && x < 80 && y > 85 && y < 135) {
    Serial.println("Pour le 1er chiffre des minutes: Bouton 4");
    minutes = 40; // Bouton 4 -> 40
  }
  if (x > 80 && x < 160 && y > 85 && y < 135) {
    Serial.println("Pour le 1er chiffre des minutes: Bouton 5");
    minutes = 50; // Bouton 5 -> 50
  }
  if (x > 160 && x < 240 && y > 85 && y < 135) {
    Serial.println("Pour le 1er chiffre des minutes: Bouton 6");
    minutes = 60; // Bouton 6 -> 60
  }
  if (x > 0 && x < 80 && y > 135 && y < 185) {
    Serial.println("Pour le 1er chiffre des minutes: Bouton 7");
    minutes = 70; // Bouton 7 -> 70
  }
  if (x > 80 && x < 160 && y > 135 && y < 185) {
    Serial.println("Pour le 1er chiffre des minutes: Bouton 8");
    minutes = 80; // Bouton 8 -> 80
  }
  if (x > 160 && x < 240 && y > 135 && y < 185) {
    Serial.println("Pour le 1er chiffre des minutes: Bouton 9");
    minutes = 90; // Bouton 9 -> 90
  }
  if (x > 0 && x < 80 && y > 185 && y < 235) {
    Serial.println("Pour le 1er chiffre des minutes: Bouton 0");
    minutes = 0; // Bouton 0 -> 0
  }
  if (x > 120 && x < 240 && y > 199 && y < 238) {
    Serial.println("On a appuyé sur le bouton Annuler..");
    annuler = 1;
  }
  Serial.print("X = "); Serial.println(x);
  Serial.print("Y = "); Serial.println(y);
  watch->tft->print((minutes / 10)); // on ré-écrit le 1er chiffre des minutes
  while (watch->getTouch(x, y)) {}
  while (!watch->getTouch(x, y)) {} // Attend qu'on touche
}

//-----------------------------
if (annuler != 1) {
  // On s'occupe du 2eme chiffre des minutes
  watch->getTouch(x, y); // on récupère où l'on a touché
  if (x > 0 && x < 80 && y > 35 && y < 85) {
    Serial.println("Pour le 2eme chiffre des minutes: Bouton 1");
    watch->tft->print("1"); // on ré-écrit le 2eme chiffre des minutes
    minutes = (minutes + 1); // Bouton 1 -> +1
  }
  if (x > 80 && x < 160 && y > 35 && y < 85) {
    Serial.println("Pour le 2eme chiffre des minutes: Bouton 2");
    watch->tft->print("2"); // on ré-écrit le 2eme chiffre des minutes
    minutes = (minutes + 2); // Bouton 2 -> +2
  }
  if (x > 160 && x < 240 && y > 35 && y < 85) {
    Serial.println("Pour le 2eme chiffre des minutes: Bouton 3");
    watch->tft->print("3"); // on ré-écrit le 2eme chiffre des minutes
    minutes = (minutes + 3); // Bouton 3 -> +3
  }
  if (x > 0 && x < 80 && y > 85 && y < 135) {
    Serial.println("Pour le 2eme chiffre des minutes: Bouton 4");
    watch->tft->print("4"); // on ré-écrit le 2eme chiffre des minutes
    minutes = (minutes + 4); // Bouton 4 -> +4
  }
  if (x > 80 && x < 160 && y > 85 && y < 135) {
    Serial.println("Pour le 2eme chiffre des minutes: Bouton 5");
    watch->tft->print("5"); // on ré-écrit le 2eme chiffre des minutes
    minutes = (minutes + 5); // Bouton 5 -> +5
  }
  if (x > 160 && x < 240 && y > 85 && y < 135) {
    Serial.println("Pour le 2eme chiffre des minutes: Bouton 6");
    watch->tft->print("6"); // on ré-écrit le 2eme chiffre des minutes
    minutes = (minutes + 6); // Bouton 6 -> +6
  }
  if (x > 0 && x < 80 && y > 135 && y < 185) {
    Serial.println("Pour le 2eme chiffre des minutes: Bouton 7");
    watch->tft->print("7"); // on ré-écrit le 2eme chiffre des minutes
    minutes = (minutes + 7); // Bouton 7 -> +7
  }
  if (x > 80 && x < 160 && y > 135 && y < 185) {
    Serial.println("Pour le 2eme chiffre des minutes: Bouton 8");
    watch->tft->print("8"); // on ré-écrit le 2eme chiffre des minutes
    minutes = (minutes + 8); // Bouton 8 -> +8
  }
  if (x > 160 && x < 240 && y > 135 && y < 185) {
    Serial.println("Pour le 2eme chiffre des minutes: Bouton 9");
    watch->tft->print("9"); // on ré-écrit le 2eme chiffre des minutes
    minutes = (minutes + 9); // Bouton 9 -> +9
  }
  if (x > 0 && x < 80 && y > 185 && y < 235) {
    Serial.println("Pour le 2eme chiffre des minutes: Bouton 0");
    watch->tft->print("0"); // on ré-écrit le 2eme chiffre des minutes
    minutes = (minutes + 0); // Bouton 0 -> +0
  }
  if (x > 120 && x < 240 && y > 199 && y < 238) {
    Serial.println("On a appuyé sur le bouton Annuler..");
    annuler = 1;
  }
  Serial.print("X = "); Serial.println(x);
  Serial.print("Y = "); Serial.println(y);
  delay(300);
}

//-----------------------------
if (jour < 1 || jour > 31) annuler = 1; // Gestion des erreurs
if (mois < 1 || mois > 12) annuler = 1;
if (annee < 2020 || annee > 2029) annuler = 1;
if (heures < 0 || heures > 23) annuler = 1;
if (minutes < 0 || minutes > 59) annuler = 1;
Serial.print("Pr ctrl $annuler: "); Serial.println(annuler);

if (annuler != 1) { // Si on avait pas pressé le bouton annuler -> mise à jour de l'heure dans le module RTC
  Serial.print("Nouvelle date: "); Serial.print(jour); Serial.print("."); Serial.print(mois); Serial.print("."); Serial.println(annee);
  Serial.print("Nouvelle heure: "); Serial.print(heures); Serial.print(":"); Serial.println(minutes);
  watch->tft->fillScreen(TFT_BLACK); // Efface l'écran
  watch->tft->setCursor(0, 80);
  watch->tft->setTextColor(TFT_GREEN);
  watch->tft->println("  Nouvelle heure:");
  watch->tft->println(" ");
  watch->tft->print("     "); watch->tft->print(jour); watch->tft->print("."); watch->tft->print(mois); watch->tft->print("."); watch->tft->print(annee);
  watch->tft->println(" ");
  watch->tft->print("        "); watch->tft->print(heures); watch->tft->print(":"); watch->tft->print(minutes);
  watch->rtc->setDateTime(annee, mois, jour, heures, minutes, 0); // setDateTime(AAAA, MM, JJ, HH, MM, SS);
} else {
  Serial.print("Le changement d'heure a été annulé");
  watch->tft->fillScreen(TFT_BLACK); // Efface l'écran
  watch->tft->setCursor(0, 85);
  watch->tft->setTextColor(TFT_RED);
  watch->tft->println("     Annulation");
  while (!watch->getTouch(x, y)) {} // Attend qu'on touche
  while (watch->getTouch(x, y)) {} // Boucle tant qu'on touche
}
Serial.print(" ");

//int16_t x, y;
while (!watch->getTouch(x, y)) {} // Attend qu'on touche
while (watch->getTouch(x, y)) {} // Boucle tant qu'on touche
watch->tft->fillScreen(TFT_BLACK); // Efface l'écran
