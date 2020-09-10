/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_murmur_hash.h"
#include "murmur_udf.cc"

/* If you declare any globals in php_murmur_hash.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(murmur_hash)
*/

/* True global resources - no need for thread safety here */
static int le_murmur_hash;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("murmur_hash.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_murmur_hash_globals, murmur_hash_globals)
    STD_PHP_INI_ENTRY("murmur_hash.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_murmur_hash_globals, murmur_hash_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_murmur_hash_compiled(string arg)
   Return a string to confirm that the module is compiled in */
// PHP_FUNCTION(confirm_murmur_hash_compiled)
// {
// 	char *arg = NULL;
// 	size_t arg_len, len;
// 	zend_string *strg;

// 	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
// 		return;
// 	}

// 	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "murmur_hash", arg);

// 	RETURN_STR(strg);
// }
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/

/* {{{ proto string murmur_hash(string arg)
   Return a 64bit unsigned murmur hash */
PHP_FUNCTION(murmur_hash)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

    RETURN_LONG(MurmurHash2((const void*) arg, arg_len, HASH_64_INIT));
}
/* }}} */

/* {{{ php_murmur_hash_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_murmur_hash_init_globals(zend_murmur_hash_globals *murmur_hash_globals)
{
	murmur_hash_globals->global_value = 0;
	murmur_hash_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(murmur_hash)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(murmur_hash)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(murmur_hash)
{
#if defined(COMPILE_DL_MURMUR_HASH) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(murmur_hash)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(murmur_hash)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "murmur_hash support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ murmur_hash_functions[]
 *
 * Every user visible function must have an entry in murmur_hash_functions[].
 */
const zend_function_entry murmur_hash_functions[] = {
	// PHP_FE(confirm_murmur_hash_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(murmur_hash, NULL)
	PHP_FE_END	/* Must be the last line in murmur_hash_functions[] */
};
/* }}} */

/* {{{ murmur_hash_module_entry
 */
zend_module_entry murmur_hash_module_entry = {
	STANDARD_MODULE_HEADER,
	"murmur_hash",
	murmur_hash_functions,
	PHP_MINIT(murmur_hash),
	PHP_MSHUTDOWN(murmur_hash),
	PHP_RINIT(murmur_hash),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(murmur_hash),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(murmur_hash),
	PHP_MURMUR_HASH_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MURMUR_HASH
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(murmur_hash)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
