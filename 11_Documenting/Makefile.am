#AM_CFLAGS = -g -Wall -Wextra

bin_PROGRAMS=guess
pkgdata_DATA=ru/LC_MESSAGES/guess.mo

#guess_SOURCES=guess.c

#guess.mo: ru.po
#	msgfmt $< -o $@

ru/LC_MESSAGES/guess.mo: ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

ru.po:	messages.pot
	msgmerge -U $@ $<

messages.pot:	guess.pot guess.c
	xgettext -k_ -c guess.c -o messages.new.pot
	cp guess.pot messages.pot
	msgmerge -U messages.pot messages.new.pot

gitclean:
	git clean -df
