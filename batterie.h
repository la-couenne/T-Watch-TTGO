// Application Batterie pour afficher les infos de consommation
delay(500); // pause afin qu'on relèvre le doigt
watch->tft->setTextSize(2);
watch->tft->fillScreen(TFT_BLACK);
watch->tft->setTextColor(TFT_YELLOW, TFT_BLACK);
watch->tft->drawString("BATT STATS",  35, 30, 2);
watch->tft->setTextColor(TFT_GREEN, TFT_BLACK);

// Allume le périphérique ADC de la batterie pour lire les valeurs
watch->power->adc1Enable(AXP202_VBUS_VOL_ADC1 | AXP202_VBUS_CUR_ADC1 | AXP202_BATT_CUR_ADC1 | AXP202_BATT_VOL_ADC1, true);
// récupérer les valeurs
float vbus_v = watch->power->getVbusVoltage();
float vbus_c = watch->power->getVbusCurrent();
float batt_v = watch->power->getBattVoltage();
int per = watch->power->getBattPercentage();

watch->tft->setCursor(0, 100);
watch->tft->print("In: "); watch->tft->print((vbus_v/1000)); watch->tft->println(" V");
watch->tft->setCursor(0, 130);
watch->tft->print("Vbus: "); watch->tft->print(vbus_c); watch->tft->println(" mA");
watch->tft->setCursor(0, 160);
watch->tft->print("Batt: "); watch->tft->print((batt_v/1000)); watch->tft->println(" V");
watch->tft->setCursor(0, 190);
watch->tft->print("Statut: "); watch->tft->print(per); watch->tft->println(" %");

int16_t x, y;
while (!watch->getTouch(x, y)) {} // Attend qu'on touche
while (watch->getTouch(x, y)) {} // Boucle tant qu'on touche
watch->tft->fillScreen(TFT_BLACK); // Efface l'écran
