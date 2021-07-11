// Application Mémo
watch->tft->fillScreen(TFT_BLACK);
watch->tft->setTextSize(2);
//watch->tft->print(" Mémo");
Serial.println("Lancement de l'application Memorum");
/*
 * On doit dessiner les lettres dans une "grille" de 6 cases
 *   x:0    80    160   240
 * y:0 +-----+-----+-----+
 *     |     |     |     |
 *     |  1  |  2  |  3  |
 *     |     |     |     |
 * 120 +-----+-----+-----+
 *     |     |     |     |
 *     |  4  |  5  |  6  |
 *     |     |     |     |
 * 199 +-----+-----+-----+
 *                 | ESC |
 * 240             +-----+
 * 
*/
String recup = "0"; // Les cases touchées par le doigt sont notées dans la variable "recup" (je mets recup=0 car il ne doit pas être vide car on fait un length ensuite)
//String memorum = ""; // On va écrire les caractères reconnus dans la variable "memorum"
int tmp = 0;
bool analyse = true; // Boucle tant que analyse est true
int16_t x, y;
String boutons[4]={"cls", "123", "draw", "esc"}; // Les 4 boutons en bas
int pos_user_x = 5; // Positions X des boutons

while (analyse == true){
  watch->tft->drawFastHLine(0,120,240,TFT_DARKGREY); // dessine des lignes de repère
  watch->tft->drawFastVLine(80,0,240,TFT_DARKGREY);
  watch->tft->drawFastVLine(160,0,240,TFT_DARKGREY);
  
  // Affichage des 4 boutons - fillRect(posX coin ht gauche, posY coin ht gauche, largeur, hauteur, arrondi, couleur);
  watch->tft->setTextSize(2);
  watch->tft->setTextColor(TFT_LIGHTGREY);
  for(int i=0; i<4; i++){
    watch->tft->fillRoundRect(pos_user_x, 200, 50, 39, 6, TFT_DARKGREY); // Dessine bouton
    if(boutons[i]=="draw"){
      watch->tft->setCursor(pos_user_x + 2, 210); // On écrit + à gauche car "draw" à + de lettres..
    }else{
      watch->tft->setCursor(pos_user_x + 6, 210);
    }
    watch->tft->print(boutons[i]);
    pos_user_x = pos_user_x + 60;
  }
  pos_user_x = 5; // RàZ les positions X des boutons
  
  watch->tft->setCursor(0, 0);
  watch->tft->setTextSize(2);
  watch->tft->println(memorum); // On affiche les mots reconnus
  while (watch->getTouch(x, y)) {} // Boucle tant qu'on touche
  while (!watch->getTouch(x, y)) {} // Attend qu'on touche
  //Serial.println(""); Serial.print("$recup avant le toucher de l'ecran: "); Serial.println(recup);
  while (watch->getTouch(x, y)) { // Boucle tant qu'on touche l'écran
    watch->getTouch(x, y); // on récupère où l'on a touché
    // On met la case touchée dans "recup", comme on ne peut la mettre qu'une fois (111112222->12) on check le dernier caractère contenu dans "recup"
    tmp = recup.length(); // contient la longueur de "recup"
    tmp = (tmp - 1);
    if (x > 0 && x < 80 && y > 0 && y < 120) {
      //Serial.println("On a touché la case 1");
      if (recup.substring(tmp) != "1") recup = recup + "1"; // Si le dernier caractère de "recup" n'est pas 1, on ajout 1 a la fin de "recup"
    }
    if (x > 79 && x < 160 && y > 0 && y < 120) {
      //Serial.println("On a touché la case 2");
      if (recup.substring(tmp) != "2") recup = recup + "2"; // Si le dernier caractère de "recup" n'est pas 2, on ajout 2 a la fin de "recup"
    }
    if (x > 159 && x < 240 && y > 0 && y < 120) {
      //Serial.println("On a touché la case 3");
      if (recup.substring(tmp) != "3") recup = recup + "3"; // Si le dernier caractère de "recup" n'est pas 3, on ajout 3 a la fin de "recup"
    }
    if (x > 0 && x < 80 && y > 119 && y < 240) {
      //Serial.println("On a touché la case 4");
      if (recup.substring(tmp) != "4") recup = recup + "4"; // Si le dernier caractère de "recup" n'est pas 4, on ajout 4 a la fin de "recup"
    }
    if (x > 79 && x < 160 && y > 119 && y < 240) {
      //Serial.println("On a touché la case 5");
      if (recup.substring(tmp) != "5") recup = recup + "5"; // Si le dernier caractère de "recup" n'est pas 5, on ajout 5 a la fin de "recup"
    }
    if (x > 159 && x < 240 && y > 119 && y < 240) {
      //Serial.println("On a touché la case 6");
      if (recup.substring(tmp) != "6") recup = recup + "6"; // Si le dernier caractère de "recup" n'est pas 6, on ajout 6 a la fin de "recup"
    }

    // Appui sur les boutons:
    if (recup.length() < 3 && x > 0 && x < 60 && y > 199 && y < 240) { // Si la longeur de "recup" < 3 c'est qu'on à rien dedans (qu'il n'y a pas eu de lettre saisie)
      Serial.println("Appui sur CLS");
      if(boutons[0]=="cls"){ // On change l'intitulé du bouton de cls en CLS, sur un 2e appui -> Efface $memorum
        boutons[0]="CLS";
        delay(250); // délai pr voir le bouton en rouge et comme anti-rebond du bouton
      }else{
        boutons[0]="cls";
        memorum = ""; // Efface $memorum
        delay(250); // délai pr voir le bouton en rouge et comme anti-rebond du bouton
      }      
      watch->tft->fillRoundRect(5, 200, 50, 39, 6, TFT_RED); // Dessine le bouton en rouge
    }
    if (recup.length() < 3 && x > 60 && x < 120 && y > 199 && y < 240) { // Si la longeur de "recup" < 3 c'est qu'on à rien dedans
      // Si on appuye sur le bouton "123/ABC" -> bascule en mode reconnaissance de chiffres
      Serial.println("Appui sur 123/ABC (A faire)");
      watch->tft->fillRoundRect(65, 200, 50, 39, 6, TFT_RED); // Dessine le bouton en rouge
      if(boutons[1]=="123"){ // On change l'intitulé du bouton entre le mode de reconnaissance ABC / 123
        boutons[1]="abc";
        delay(250); // délai pr voir le bouton en rouge et comme anti-rebond du bouton
      }else{
        boutons[1]="123";
        delay(250); // délai pr voir le bouton en rouge et comme anti-rebond du bouton
      }
    }
    if (recup.length() < 3 && x > 120 && x < 180 && y > 199 && y < 240) { // Si la longeur de "recup" < 3 c'est qu'on à rien dedans
      // Si on appuye sur le bouton "Draw" -> dessine la trajectoire faite par le doigt sur l'écran ### A FAIRE ###
      Serial.println("Appui sur Draw (A faire)");
      watch->tft->fillRoundRect(125, 200, 50, 39, 6, TFT_RED); // Dessine le bouton en rouge
      delay(50); // délai pr voir le bouton en rouge
    }
    if (recup.length() < 3 && x > 180 && x < 240 && y > 199 && y < 240) { // Si la longeur de "recup" < 3 c'est qu'on à rien dedans
      analyse = false; // Si on appuye sur le bouton "annuler" -> casse la boucle analyse pour sotrir de l'appli memo
      Serial.println("Appui sur ESC");
      watch->tft->fillRoundRect(185, 200, 50, 39, 6, TFT_RED); // Dessine le bouton en rouge
      delay(50); // délai pr voir le bouton en rouge
    }
  
  } // Fin de la boucle tant qu'on touche l'écran
  Serial.print("$recup apres le toucher de l'ecran: "); Serial.println(recup);

  // Si on ne touche plus l'écran: on analyse la variable "recup" pr définir une lettre reconnue
  //watch->tft->fillScreen(TFT_BLACK); // Efface l'écran
  if(boutons[1]=="123"){ // Si le bouton affiche 123 c'est qu'on est en mode de reconnaissance ABC lettres
    if(recup.indexOf("012325") == 0)recup = "T";
    if((recup.indexOf("01236545") == 0)||(recup.indexOf("012325456") == 0)||(recup.indexOf("012321456") == 0))recup = "Z";
    if(recup.indexOf("056") == 0)recup = ".";
    if(recup.indexOf("0123") == 0)recup = "-";
    if((recup.indexOf("0126") == 0)||(recup.indexOf("0153") == 0)||(recup.indexOf("0156") == 0)||(recup.indexOf("0456") == 0)||(recup.indexOf("0423") == 0)||(recup.indexOf("0453") == 0)||(recup.indexOf("0426") == 0))recup = " ";
    if((recup.indexOf("0412563") == 0)||(recup.indexOf("0412363") == 0))recup = "N";
    if((recup.indexOf("041236") == 0)||(recup.indexOf("041256") == 0)||(recup.indexOf("04126") == 0)||(recup.indexOf("04236") == 0)||(recup.indexOf("04256") == 0)||(recup.indexOf("0426") == 0)||(recup.indexOf("045236") == 0)||(recup.indexOf("045256") == 0)||(recup.indexOf("04526") == 0))recup = "A";
    if(recup.indexOf("01452563") == 0)recup = "W";
    if((recup.indexOf("0141232565") == 0)||(recup.indexOf("01412565") == 0)||(recup.indexOf("014123654565") == 0)||(recup.indexOf("0141254") == 0)||(recup.indexOf("014123254565") == 0)||(recup.indexOf("014525") == 0))recup = "B";
    if((recup.indexOf("032145") == 0)||(recup.indexOf("032456") == 0)||(recup.indexOf("032156") == 0))recup = "C";
    if((recup.indexOf("01412365") == 0)||(recup.indexOf("0141265") == 0)||(recup.indexOf("01412354") == 0))recup = "D";
    if((recup.indexOf("0321232145") == 0)||(recup.indexOf("0321452545") == 0)||(recup.indexOf("032545") == 0)||(recup.indexOf("03212145") == 0)||(recup.indexOf("03214545") == 0)||(recup.indexOf("05632145") == 0)||(recup.indexOf("0232145") == 0))recup = "E";
    if((recup.indexOf("041236") == 0)||(recup.indexOf("04125236") == 0)||(recup.indexOf("04125636") == 0))recup = "M";
    if((recup.indexOf("014123215") == 0)||(recup.indexOf("01412325") == 0))recup = "R";
    if((recup.indexOf("0141232") == 0)||(recup.indexOf("014125") == 0)||(recup.indexOf("01412365") == 0))recup = "P";
    if((recup.indexOf("01412") == 0)||(recup.indexOf("014123") == 0)||(recup.indexOf("0412") == 0))recup = "F";
    if((recup.indexOf("0214565") == 0))recup = "G";
    if((recup.indexOf("0145636") == 0)||(recup.indexOf("0141236") == 0))recup = "H";
    if(recup.indexOf("0254") == 0)recup = "J";
    if(recup.indexOf("025") == 0)recup = "I";
    if((recup.indexOf("01412") == 0)||(recup.indexOf("01452") == 0))recup = "K";
    if(recup.indexOf("0214563") == 0)recup = "O";
    if((recup.indexOf("0214525") == 0)||(recup.indexOf("02125") == 0)||(recup.indexOf("03236") == 0)||(recup.indexOf("0325636") == 0))recup = "Q";
    if((recup.indexOf("03214565") == 0)||(recup.indexOf("03212365") == 0)||(recup.indexOf("0321254") == 0))recup = "S";
    if(recup.indexOf("014563") == 0)recup = "U";
    if((recup.indexOf("012523") == 0)||(recup.indexOf("012563") == 0))recup = "V";
    if((recup.indexOf("0145") == 0)||(recup.indexOf("01456") == 0))recup = "L";
    if((recup.indexOf("01456545") == 0)||(recup.indexOf("0145452") == 0)||(recup.indexOf("0125654") == 0)||(recup.indexOf("012541") == 0))recup = "X";
    if((recup.indexOf("0145636") == 0)||(recup.indexOf("0145235") == 0)||(recup.indexOf("0145236") == 0)||(recup.indexOf("0125636") == 0)||(recup.indexOf("0125235") == 0))recup = "Y";
  }else{ // sinon on est en mode de reconnaissance 123 chiffres
    if((recup.indexOf("02145632") == 0)||(recup.indexOf("0214563") == 0))recup = "0";
    if((recup.indexOf("0125") == 0)||(recup.indexOf("025") == 0)||(recup.indexOf("04125") == 0))recup = "1";
    if((recup.indexOf("0126") == 0)||(recup.indexOf("0153") == 0)||(recup.indexOf("0156") == 0)||(recup.indexOf("0456") == 0)||(recup.indexOf("0423") == 0)||(recup.indexOf("0453") == 0)||(recup.indexOf("0426") == 0))recup = " ";
    if((recup.indexOf("01236545") == 0)||(recup.indexOf("012325456") == 0)||(recup.indexOf("012321456") == 0))recup = "2";
    if((recup.indexOf("01232365") == 0)||(recup.indexOf("01236565") == 0)||(recup.indexOf("0232365") == 0)||(recup.indexOf("0236565") == 0))recup = "3";
    if((recup.indexOf("0145") == 0)||(recup.indexOf("0256") == 0))recup = "4";
    if((recup.indexOf("03214565") == 0)||(recup.indexOf("03212365") == 0)||(recup.indexOf("0321254") == 0))recup = "5";
    if(recup.indexOf("02145") == 0)recup = "6";
    if((recup.indexOf("01236") == 0)||(recup.indexOf("0125") == 0)||(recup.indexOf("0236") == 0))recup = "7";
    if(recup.indexOf("021232") == 0)recup = "8";
    if((recup.indexOf("02125") == 0)||(recup.indexOf("021236") == 0)||(recup.indexOf("02145636") == 0)||(recup.indexOf("0323") == 0))recup = "9";
    if(recup.indexOf("056") == 0)recup = ".";
    if(recup.indexOf("0123") == 0)recup = "-";
  }
  if(recup.indexOf("0365") == 0)recup = "\n"; // Retour à la ligne
  if((recup.indexOf("0321") == 0)||(recup.indexOf("0654") == 0))recup = "*"; // Effacer dernier caractère
  
  if((recup.length() > 1) || (recup == "0"))recup = "??"; // Si "recup" est + long que 1 caractère, c'est qu'il n'y a pas de correspondance à une lettre A B C..

  Serial.print("Lettre reconnue: "); Serial.println(recup);
  watch->tft->setTextColor(TFT_RED);
  watch->tft->setCursor(80, 80);
  if (recup == "\n"){ // si retour ligne
    watch->tft->setTextSize(5);
    watch->tft->println("<-'"); // On affiche "retour" car le "\n" ne s'affichera pas
  }else{
    watch->tft->setTextSize(7);
    watch->tft->println(recup); // On affiche la lettre reconnue (ou ?? si pas de correspondance)
  }
  if (recup == "*"){ // Effacer dernier caractère
    Serial.println("On effacer dernier caractère");
    memorum = memorum.substring(0, (memorum.length()-1)); recup = "";
  }
  delay(200);
  watch->tft->fillScreen(TFT_BLACK);
  if (recup != "??") memorum = memorum + recup; // On ajoute la lettre reconnue au mots dans "memorum"
  recup = "0"; // On remet "recup" à 0
}

// ### afficher le mot entier ###
// ### ajouter un bouton "123/ABC" (et "calc"?) ###
Serial.println("");
//while (!watch->getTouch(x, y)) {} // Attend qu'on touche
//while (watch->getTouch(x, y)) {} // Boucle tant qu'on touche
watch->tft->fillScreen(TFT_BLACK); // Efface l'écran
