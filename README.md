# Kurzanleitung zur Benutzung Ihres Git-Repositoriums
Im Labor `cen1112` werden Änderungen an Ihrem Repositorium über
die Eingabe von `git`-Befehlen auf der Kommandozeile verwendet.
Als Kommandozeile wird `konsole` verwendet.

## Inbetriebnahme
### Klonen
Zu Beginn müssen Sie das Repositorium auf den Laborrechner übertragen:

	git clone git@gitlab.hs-pforzheim.de:cen1112_ws2223/student/sejdiuer.git ~/labor

### Arbeitsverzeichnis
Um Git-Befehle verwenden zu können, müssen in das Arbeitsverzeichnis wechseln:

	cd ~/labor

### Identität
Bei der ersten Benutzung Ihres Klones müssen Sie dem Repositorium Ihre Identität mitteilen:

	git config user.name  "sejdiuer"
	git config user.email "sejdiuer@hs-pforzheim.de"

### Hinzufügen Ihrer ersten Datei
Öffnen Sie den Texteditor `kate` und kopieren Sie folgenden Code

	int main() {
		return 0;
	}

in das Editorfenster. Speichern Sie nun diese Datei unter:

	~/labor/main.c

Wenn Sie nun in Ihrer `konsole` den Befehl `ls` eingeben, dann sollten Sie
Ihre soeben erstellte Datei sehen.

Der aktuelle Projektstand soll nun abgegeben werden. Hierfür wird zunächst
die Datei `main.c` für die Abgabe markiert:

	git add main.c

Da wir nur die Datei `main.c` abgeben wollen, können wir nun die Abgabe als
abgeschlossen markieren und mit der Beschreibung `Meine erste Abgabe` versehen:

	git commit -m "Meine erste Abgabe"

Nun endlich können wir die Abgabe an den Git-Server übertragen:

	git push

## Umgang mit dem Git-Server im Laboralltag
### Sichern von Änderungen
Keine Panik! In diesem Abschnitt werden Sie nichts neues Lernen.
Oder anders herum: Sie können Ihr bisheriges Wissen anwenden.

Falls Sie Ihre Änderungen an der Datei `main.c` auf dem Git-Server sichern wollen, dann
brauchen Sie nur die Schritte
	cd ~/labor
	git add main.c
	git commit -m "Sinnvolle Beschreibung der Änderung..."
	git push

wiederholen.


### Abgeben einer Lösung zu einer Laboraufgabe
Die einzelnen Laboraufgaben werden Ihnen unter

	https://gitlab.hs-pforzheim.de/cen1112_ws2223/student/sejdiuer/-/issues/

in Form sogenannter `issue`s zur Verfügung gestellt. Jede einzelne Aufgabe bzw. jeder einzelne `issue` hat eine Nummer.
Die Aufgabennummer erkennen Sie am vorangestellten Zeichen #.
So wird die Aufgabe 2 im Git beispielsweise als `#2` angezeigt.
Zur Abgabe der Lösung einer Aufgabe muss die Beschreibung der Änderung die Zeichenfolge

	close #AUFGABEN_NUMMER

enthalten. Soll also z.B. die Lösung der Aufgabe 2 abgegeben werden, so lauten die notwendigen Befehle:

	cd ~/labor
	git add main.c
	git commit -m "close #2"
	git push

