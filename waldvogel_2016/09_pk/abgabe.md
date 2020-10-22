# Lösungen zum 9\. Übungsblatt

# Bamberger, Jannik und Klopfer, Fabian

## Aufgabe 1: Alle Jahre wieder: Pseudocode

```
/**
 * @author Jannik Bamberger
 * @author Fabian Klopfer
 * @credits 40
 */
main() {
	Datum deadline = 12.01.2017 03:00;
	while(1) {
		schlafen();
		essen();

		Nachrichten nachrichten = leseSMS();
		while(nachrichten != NULL) {
			if(vonFreund(nachrichten.first)) {
				Aktion aktion = aktion(nachrichten.first);
				treffeFreund(aktion)
			} else {
				ignoriereNachricht();
			}
			remove(nachrichten, nachrichten.first);
		}

		if(aktuelle Zeit == 25.12.2016) {
			fahreZuGroßeltern();
			while(omaTischtEssenAuf()) { // == 1
				essen();
			}
			fahreHeim();
		}

		if(aktuelle Zeit > deadline - 1 Stunde) {
			for (i = 0; i < 100; i++) {
				rennePanischImKreis();
			}
			if(Übungspartner hat Aufgaben noch nicht committed) {
				while(aktuelle Zeit < deadline - 3 Minuten && !übungsBlattFertig()) {
					schreibeWütendeMailAnÜbungspartner();
					arbeiteAnÜbungsblatt();
					if(ÜbungspartnerHatGeantwortet()) {
						übergebeVerantwortungAnPartner();
					}
				}
				while(!nameAufAllenAbgaben()) {
					schreibeNameAufEineAbgabe();
					committeÜbungsaufgeben();
				}
				break;
			}
		}
	}
}

treffeFreund(Aktion aktion) {
	holeFahrrad();
	fahreFahrrad();
	if(straßeGlatt()) {
		falleHin();
		bemerkeGlätte();
		fahreWeiter();
	}

	macheAktionMitFreund(aktion);

	fahreFahrrad();
	if(straßeGlatt()) {
		falleHin();
		bemerkeGlätte();
		fahreWeiter();
	}
	stelleFahrradAb();
}
```
