qdacco

General installation instructions
=================================
Previous note: *Debian and Ubuntu already have dacco and qdacco packages.*

Just execute:
``apt-get install qdacco``

Or:
``sudo apt-get install qdacco``

So, you don't need to compile, only installing qdacco package is enough.
Other distributions may have the package already done too.

When run for the first time, qdacco will prompt the user for
configuration information (default language, data directory, etc.)

Some qdacco distribution come with the data already provided, in
which case you just have to press "OK" to continue. Otherwise, you
will have to select the directory in which your dacco files are
located (i.e. the 'dictionaries' directory).

If you need to download data files, you can find using:
http://www.catalandictionary.org

GNU/Linux specific instructions
===============================
In order to compile qdacco, in Debian-based distributions you will
need the following packages (which have similar names in other
distributions):
qt5-default
cmake

In order to install, you need to execute (You need to be root to do this):
apt-get install qt5-default cmake

MacOSX specific instructions
===============================
(not tested since the Qt5 migration)
To build qdacco on mac, you will need basically two things:
You have to obtain a copy of xcode tools, you have to register:
http://developer.apple.com/technology/xcode.html

The second thing you will need is to get macports from:
http://www.macports.org/install.php
Once installed macports, type the following command and take a break: 
sudo port install qt4-mac cmake
This will compile qt4 for you, it will take some time, but eventually
it will finish.
NOTE: If cmake can not find qmake-mac (qmake), you can set it with,
this will force it to use macports' qt

cmake -DQT_QMAKE_EXECUTABLE=/opt/local/bin/qmake-mac ../

Compilation
===========
Then you will have to uncompress qdacco file (tar -zxvf qdacco-X.tar.bz2) 
and execute:
cd qdacco
mkdir build
cd build
cmake ../
make

(From now on, you have the binaries inside build/gui/qdacco and
build/text/textqdacco, read to execute)

make install #optionally, if you want to install binaries and lib
             #inside /usr/local/bin and /usr/local/lib
	     #Execute as root

Attention: if you want to execute qdacco installed in /usr/local/bin,
you need that /usr/local/lib directory is listed in /etc/ld.so.conf
(usually it is) and that you execute ldconfig

You might like to add a shortcut to your desktop or Windows Manager.
qdacco executable file is in /usr/local/bin/qdacco

Note
====
To download the dictionaries:
http://prdownloads.sourceforge.net/dacco/dacco-0.9.zip?download

You can check in http://www.catalandictionary.org if there are newer
ones.

Debian, Ubuntu, etc. usually has their own packages.

Festival
========
Festival is a speech synthesis system. Usually it is available in 
"festival" package. If it is installed, qdacco will be able to pronunce
words (check advanced configuration). 

**Read 'General installation instructions'.

PD: first revision of this text has been revised by Linda Oxnard 
and Jonathan Kaye.

Carles Pina i Estany, 2005, 2006, 2007, 2008, 2009, 2011, 2013, 2015
carles@pina.cat