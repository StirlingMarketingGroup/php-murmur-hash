dnl $Id$
dnl config.m4 for extension murmur_hash

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(murmur_hash, for murmur_hash support,
dnl Make sure that the comment is aligned:
dnl [  --with-murmur_hash             Include murmur_hash support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(murmur_hash, whether to enable murmur_hash support,
Make sure that the comment is aligned:
[  --enable-murmur-hash           Enable murmur_hash support])

if test "$PHP_MURMUR_HASH" != "no"; then
  dnl Write more examples of tests here...

  dnl # get library FOO build options from pkg-config output
  dnl AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  dnl AC_MSG_CHECKING(for libfoo)
  dnl if test -x "$PKG_CONFIG" && $PKG_CONFIG --exists foo; then
  dnl   if $PKG_CONFIG foo --atleast-version 1.2.3; then
  dnl     LIBFOO_CFLAGS=`$PKG_CONFIG foo --cflags`
  dnl     LIBFOO_LIBDIR=`$PKG_CONFIG foo --libs`
  dnl     LIBFOO_VERSON=`$PKG_CONFIG foo --modversion`
  dnl     AC_MSG_RESULT(from pkgconfig: version $LIBFOO_VERSON)
  dnl   else
  dnl     AC_MSG_ERROR(system libfoo is too old: version 1.2.3 required)
  dnl   fi
  dnl else
  dnl   AC_MSG_ERROR(pkg-config not found)
  dnl fi
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBDIR, MURMUR_HASH_SHARED_LIBADD)
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)

  dnl # --with-murmur_hash -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/murmur_hash.h"  # you most likely want to change this
  dnl if test -r $PHP_MURMUR_HASH/$SEARCH_FOR; then # path given as parameter
  dnl   MURMUR_HASH_DIR=$PHP_MURMUR_HASH
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for murmur_hash files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       MURMUR_HASH_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$MURMUR_HASH_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the murmur_hash distribution])
  dnl fi

  dnl # --with-murmur_hash -> add include path
  dnl PHP_ADD_INCLUDE($MURMUR_HASH_DIR/include)

  dnl # --with-murmur_hash -> check for lib and symbol presence
  dnl LIBNAME=murmur_hash # you may want to change this
  dnl LIBSYMBOL=murmur_hash # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $MURMUR_HASH_DIR/$PHP_LIBDIR, MURMUR_HASH_SHARED_LIBADD)
  AC_DEFINE(HAVE_MURMUR_HASHLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong murmur_hash lib version or lib not found])
  dnl ],[
  dnl   -L$MURMUR_HASH_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(MURMUR_HASH_SHARED_LIBADD)

  PHP_NEW_EXTENSION(murmur_hash, murmur_hash.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
