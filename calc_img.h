// l'img du menu (Le .png a été enregistrée en .xbm et collée ici)
#include <pgmspace.h> // On ajoute cette bibliothèque (elle est aussi en début de programme)

#define calc_img_width 30
#define calc_img_height 39
// On ajoute aussi PROGMEM ci-dessous
PROGMEM static unsigned char calc_img_bits[] = {
   0xf8, 0xff, 0xff, 0x07, 0xfe, 0xff, 0xff, 0x1f, 0xfe, 0xff, 0xff, 0x1f,
   0x0f, 0x00, 0x00, 0x38, 0x07, 0x00, 0xe0, 0x38, 0x07, 0x00, 0xf0, 0x39,
   0x07, 0x00, 0x18, 0x3b, 0x07, 0x00, 0x18, 0x3b, 0x07, 0x00, 0x18, 0x3b,
   0x07, 0x00, 0x18, 0x3b, 0x07, 0x00, 0xf8, 0x3b, 0x07, 0x00, 0xf0, 0x39,
   0x07, 0x00, 0x00, 0x38, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0x3f,
   0xff, 0xff, 0xff, 0x3f, 0x0f, 0x1f, 0x3e, 0x3c, 0x07, 0x0e, 0x1c, 0x38,
   0x07, 0x0e, 0x1c, 0x38, 0x07, 0x0e, 0x1c, 0x38, 0x0f, 0x1f, 0x3e, 0x3c,
   0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0x3f,
   0x0f, 0x1f, 0x3e, 0x3c, 0x07, 0x0e, 0x1c, 0x38, 0x07, 0x0e, 0x1c, 0x38,
   0x0f, 0x1f, 0x3e, 0x3c, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0x3f,
   0xff, 0xff, 0xff, 0x3f, 0x0f, 0x1f, 0x3e, 0x3c, 0x07, 0x0e, 0x1c, 0x38,
   0x07, 0x0e, 0x1c, 0x38, 0x07, 0x0e, 0x1c, 0x38, 0x0f, 0x1f, 0x3e, 0x3c,
   0xfe, 0xff, 0xff, 0x1f, 0xfe, 0xff, 0xff, 0x1f, 0xf8, 0xff, 0xff, 0x07 };
