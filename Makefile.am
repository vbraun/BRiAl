ACLOCAL_AMFLAGS = -I m4

SUBDIRS = Cudd/cudd libbrial . groebner pyroot

lib_LTLIBRARIES = libbrial.la

libbrial_la_SOURCES =
libbrial_la_LIBADD = \
	Cudd/cudd/libcudd.la \
	libbrial/src/libbrial_base.la

EXTRA_DIST = \
	Cudd/LICENSE \
	LICENSE \
	README
