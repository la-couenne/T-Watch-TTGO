// Application Médic
// ### Tous les medicaments contenus dans $monde ne sont pas affichés car ils dépassent du bas de l'écran.. ###
Serial.println("Lancement appli medic..");
delay(500); // pause afin qu'on relèvre le doigt
int16_t x, y;
watch->tft->fillScreen(TFT_BLACK);
watch->tft->setTextSize(2);
watch->tft->setTextColor(TFT_DARKGREEN);
watch->tft->setCursor(0, 0);
//watch->tft->print(" Medic");

int ii = 0;
int pos_user_y = 0;
int medic_select = 0; // Contient le médic sélectionné
int nb_medic = 14; // Contient le nb de médic
// Ci-dessous, mettre \n pour des retour ligne
String monde[] = {"xxx", 
"BUSCOPAN", "20mg ds 100ml ivL", "Spasmolytique pr colique nephro, biliaire, spasmes gastro-intestinal", "! si: Enceinte/lait\nTachyary, Myasthenie\nRetention urinaire\n<12ans", 
"ESOMEPRAZOL (Nexium)", "80mg ds 100ml ivL", "Ulcere gastrique,\n hemo. dig. haute", "! si: Enceinte/lait,\n<12ans", 
"IBUPROFEN (Grefen)", "400mg po", "AINS pour dlrs moderees ou si refuse iv", "! si: Enceinte/lait,\nUlcere gastique,\nInsuff. reinale,\n<12ans, >60ans", 
"FENTANYL", "1mcg/kg IN/ivL \n(max 300mcg)", "Si hTA->250ml first", "! si: FR<10, \nAllergie", 
"FLUMAZENIL (Anexate)", "0.1mg/minute iv \n(max 1mg)", "Inhibiteur competitif des benzo", "! si: Intox anti-depresseur, Tri-cycliques, Coke", 
"KETAMINE", "0.3mg/kg ivL", "100mg -> flex 100ml\n -> 1mg/ml\n \nFentanyl first,\n Penser ETCO2,\n Midazolam si agite:\n 1mg (0.5 si vieux)", "! si: HTA, Tachy", 
"KETOROLAC (Toradol)", "30mg ivL \n(Comment? ds 10ml?)", "AINS pour coliques\nneph. et lombalgies", "! si: Enceinte/lait,\nInsuf rein, Insuff.\nhepatique, Ulcere gastrique, <12ans", 
"PARACETAMOL", "1g po/ivL", "Antalgie, Antipyretique", "! si: hTA, Insuff. \nhepatique, \net si deja prit!", 
"MORPHINE et\n ADRENALINE", "1mg/ml -> 9ml NaCl \n-> 0.1mg/ml \n(ou 100mcg/ml)", "", "", 
"NARCAN", "0.1 en 0.1\n (max 0.8?)", "Amp de 0.4mg/ml a\n diluer ds 3ml\n -> 0.1mg/ml", "", 
"ADRENALINE\n pour Choc & Anaphy.", "Choc:20mcg/ttes 2min\nAnaphy: 10mcg/2min\n Amp. 1mg/10ml ->\n flex 100ml ->\n 0.01mg/ml", "Envoyer ds patient:\n 2ml = 0.02mg (ou 20mcg) / ttes 2min", "", 
"CALCUL", "1mcg = 0.001mg\n", "Amg->Bml Cmg->Xml?", "Xml = BmlxCmg / Amg\n \n \nAutonomie =\nBar x Litres / Conso\n \n \n1% = 1g -> 100ml", 
"NOM", "Dosage", "Indications", "! si:", 
"xxx", "xxx", "xxx", "xxx"};
String ligne = "";
bool analyse = true; // Boucle afin de pouvoir quitter l'appli
bool exitMenu = false;

//on affiche le menu
ii = 1;
watch->tft->setCursor(0, 0);
watch->tft->setTextColor(TFT_GREEN); // On met le 1er médic est en vert clair
watch->tft->println(monde[ii]); // watch->tft->println(ii); // On affiche le 1er medic
watch->tft->setTextColor(TFT_DARKGREEN); // On remet en vert foncé
for(int i=1;i<12; i++){ // Puis on affiche les 11 autres (11 car limité par le bas de l'écran)
  ii = (ii + 4);
  watch->tft->println(monde[ii]); // watch->tft->println(ii);
}

while (analyse == true){
  while (!watch->getTouch(x, y)) {} // Attend qu'on touche
  watch->tft->fillScreen(TFT_BLACK);
  if ( watch->getTouch(x,y) ) { // si touche écran
    if (y >= 160) { // vous voulez que la liste du menu soit déplacée vers le haut
      medic_select += 4;
      if (medic_select > 44) medic_select = 44; //### L'écran ne peut pas en afficher + en bas, mais il y a encore des médics dans $monde ###
    }
    if (y <= 80) { // vous voulez que la liste du menu soit déplacée vers le bas
      medic_select -= 4;
      if (medic_select < 0) medic_select = 0;
    }
    if (y > 80 && y < 160) { // Vous avez sélectionné le milieu
      analyse = false;
    }
    delay(50);
  }
  ii = 1;
  watch->tft->setCursor(0, 0);
  for(int i=1;i<13; i++){
    if(ii == (medic_select + 1)){
      watch->tft->setTextColor(TFT_GREEN); // Le médic sélectionné est en vert clair
    }else{
      watch->tft->setTextColor(TFT_DARKGREEN);
    }
    watch->tft->println(monde[ii]); // watch->tft->println(ii);
    ii = (ii + 4);
    if(ii > 48)ii = 1;
  }
}

// On affiche le noms du produit en vert clair et un retour ligne
//Serial.print("Pr ctrl medic_select: "); Serial.println(medic_select);
medic_select++; // On ajoute +1
watch->tft->fillScreen(TFT_BLACK);
watch->tft->setTextColor(TFT_GREEN);
watch->tft->setCursor(0, 0);
watch->tft->println(monde[medic_select]); watch->tft->println("");
// On affiche les dosage, indications et contre-indications
watch->tft->setTextColor(TFT_DARKGREEN);
for(int i=1;i<4; i++){
  medic_select++; // On ajoute +1 pour ne pas afficher le titre
  watch->tft->println(monde[medic_select]); watch->tft->println("");
}

while (!watch->getTouch(x, y)) {} // Attend qu'on touche
while (watch->getTouch(x, y)) {} // Boucle tant qu'on touche

watch->tft->fillScreen(TFT_BLACK);
watch->tft->setCursor(75, 80);
watch->tft->setTextSize(2);
watch->tft->println("Ciao..");
delay(250);
watch->tft->fillScreen(TFT_BLACK); // Efface l'écran
