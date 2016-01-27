all: wedstrijd

Main.class:
	javac Main.java

voorbeeld: Main.class
	cat ../../voorbeeld.invoer | java Main

wedstrijd: Main.class
	cat ../../wedstrijd.invoer | java Main
