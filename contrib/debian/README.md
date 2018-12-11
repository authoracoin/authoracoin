
Debian
====================
This directory contains files used to package authoracoind/authoracoin-qt
for Debian-based Linux systems. If you compile authoracoind/authoracoin-qt yourself, there are some useful files here.

## authoracoin: URI support ##


authoracoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install authoracoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your authoracoinqt binary to `/usr/bin`
and the `../../share/pixmaps/authoracoin128.png` to `/usr/share/pixmaps`

authoracoin-qt.protocol (KDE)

