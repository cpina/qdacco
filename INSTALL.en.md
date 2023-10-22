# qdacco: installation

## General installation instructions
Debian i Ubuntu have the `dacco-common` and `qdacco` packages. To install it on Debian and Ubuntu you can do:
`apt-get install qdacco`

Or:
`sudo apt-get install qdacco`

When executing qdacco the first time it will show the preferences dialogue. Click "Ok" to continue.

The dictionary files are installed with qdacco on Debian and Ubuntu. The first time that qdacco is executed it will show the preferences dialogue: you can press "Ok". Otherwise you need to select the directory with the dictionary (named `dictionaries`).

If you need hte dictionaries you can find them in:
http://www.catalandictionary.org

## GNU/Linux specific instructions
In order to compile qdacco, in Debian-based distributions you can execute:
```apt install qt6-base-dev cmake
git clone git@github.com:cpina/qdacco.git
cd qdacco
mkdir build
cd build
cmake ../
make
sudo make install # it will be installed in /usr/local/bin
```

In other distributions you will need to install the Qt5 and cmake using their package system.

## Download the DACCO dictionaries
To download the dictionaries:
http://prdownloads.sourceforge.net/dacco/dacco-0.9.zip?download

You can check in http://www.catalandictionary.org if there are newer
ones.

Debian, Ubuntu, etc. is not needed because qdacco installs the dependency dacco-common.

## Festival
Festival is a speech synthesis system. Usually it is available in 
"festival" package. If it is installed, qdacco will be able to pronunce
words (check advanced configuration). 

PD: first revision of this text has been revised by Linda Oxnard 
and Jonathan Kaye.

---
Carles Pina i Estany, 2005-2009, 2011, 2013, 2015, 2017, 2020-2023
carles@pina.cat
