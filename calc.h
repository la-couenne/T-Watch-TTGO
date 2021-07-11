// Application Calculatrice
delay(500); // pause afin qu'on relèvre le doigt
watch->tft->fillScreen(TFT_BLUE);
watch->tft->setTextSize(2);
watch->tft->setCursor(130, 200);
watch->tft->print(" Calcul");

int16_t x, y;
while (!watch->getTouch(x, y)) {} // Attend qu'on touche
while (watch->getTouch(x, y)) {} // Boucle tant qu'on touche
watch->tft->fillScreen(TFT_BLACK); // Efface l'écran
