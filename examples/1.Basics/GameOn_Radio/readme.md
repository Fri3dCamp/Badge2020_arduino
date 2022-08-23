Maak van je Fri3d badge 2022 met gameOn en aangesloten speaker een radio.

Installatie
- Check je ESP32 Arduino core: gebruik 1.0.6 of 2.0.4 (de eerdere 2.X versies hebben onstabiele ondersteuning voor audio)
- Installeer de library ESP8266Audio vanuit bibiotheek beheer in de Arduino IDE
	- versie 1.9.5 als je core 1.0.6 gebruikt
	- versie 1.9.7 als je core 2.0.4 gebruikt
- In de code GameOn_Radio.ino vul je de Wifi-codes in
- Het staat standaard ingesteld op StuBru, maar de URL's van een 10-tal zenders zijn toegevoegd.
- compileren voor ESP32 Wrover module en opladen
