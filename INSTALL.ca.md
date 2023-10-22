# qdacco: instal�laci�

## Instruccions generals d'instal�laci�
Debian i Ubuntu tenen el paquet de `dacco-common` i `qdacco`. Per instal�lar a Debian i Ubuntu feu:
`apt-get install qdacco`

O:
`sudo apt-get install qdacco`

Quan executeu qdacco per primer cop, demanar� a l'usuari informaci� de configuraci� (idioma per defecte, directori de dades, etc.)

qdacco de Debian i Ubuntu ja instal�la el paquet amb els diccionaris. El primer cop que executeu qdacco us ensenyar� la configuraci� i podeu presionar "D'acord". Altrament cal seleccionar el directori amb el diccionari (directory anomenat `dictionaries`)

Si es necessiten els fitxers de dades, es poden trobar mitjan�ant:
http://www.catalandictionary.org

## Instruccions de compilaci� per GNU/Linux
Per tal de compilar qdacco, en distribucions basades en Debian podeu executar:

```apt install qt6-base-dev cmake
git clone git@github.com:cpina/qdacco.git
cd qdacco
mkdir build
cd build
cmake ../
make
sudo make install # s'instal�lar� a /usr/local/bin
```

En altres distribucions haureu d'instal�lar Qt5 i cmake utilitzant el seu sistema de paquets.

## Descarregar els diccionaris DACCO
Per baixar-se els diccionaris (DACCO):
http://prdownloads.sourceforge.net/dacco/dacco-0.9.zip?download

Podeu comprovar mitjan�ant http://www.catalandictionary.org si
n'hi ha de m�s recents.

A Debian, Ubuntu, etc. no cal ja que qdacco instal�la la depend�ncia dacco-common.

## Festival
Festival �s un sintetitzador de veu. Sol estar disponible al paquet
festival. Si el teniu instal�lat qdacco el pot fer servir (veure la
configuraci�) i pronunciar les paraules.

---
Carles Pina i Estany, 2005, 2006, 2007, 2008, 2011, 2013, 2015, 2017, 2020
carles@pina.cat
