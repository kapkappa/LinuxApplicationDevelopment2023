SUBDIRS = src tests

demo: all
	./src/buf

gcov:	check
		$(MAKE) $(MAKEFLAGS) -C src gcov

gitclean:
	git clean -df
