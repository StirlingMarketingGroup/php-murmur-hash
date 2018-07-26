# php-murmur-hash

This is essentially the Percona murmur hash function ported/wrapped in a PHP extension that you can find here https://github.com/percona/build-test/blob/master/plugin/percona-udf/murmur_udf.cc

Mainly this exists so that you can get the exact same output in PHP as you do in MySQL with `murmur_hash`.

## Installation 

Clone this repo somewhere with the following and enter the new folder

    git clone https://github.com/StirlingMarketingGroup/php-murmur-hash.git
    cd php-murmur-hash

Then run the following commands to build the extension and install it

    phpize
    ./configure --enable-murmur-hash
    make
    make install
    
This should place the module into your PHP extensions directory (which you can find by running `php-config --extension-dir`).

Lastly, add `extension=murmur_hash` to the end of your php.ini file, which will be /etc/php/7.2/apache2/php.ini for PHP 7.2.

**Note that this plugin doesn't function exactly the same as the MySQL version from Percona, and only accepts a single input, unlike the MySQL version which accepts infinite inputs. Only single-argument use will be the same.**

## Example output

In MySQL, the Percona extension is used like 

    select`murmur_hash`('Yeet')
    -- -7850704420789372250
    
And in PHP

    php -r 'echo murmur_hash("Yeet");'
    // -7850704420789372250

Note that those are getting treated as signed integers for both environments, which you can solve in MySQL by using ``cast(`murmur_hash`('Yeet')as unsigned)``, but PHP doesn't support unsigned integers.

In MySQL, you can convert this integer to a binary string (`conv` in MySQL already treats it as unsigned, unless you give the "to base" a negative sign, like "-16")

    unhex(conv(`murmur_hash`('Yeet'),10,16))
    -- 0x930CB1EC9242BAA6

In PHP, you can get to the same output by using the `pack` function. The "J" option sepcifies "unsigned long long (always 64 bit, big endian byte order)", which is what I needed to use to get the same output, but for some reason if I used Q, or "unsigned long long (always 64 bit, machine byte order)", I get something different than MySQL, even if I do these things on the same machine as the MySQL server. (Maybe MySQL forces big endian onwith `conv`?)

    echo bin2hex(pack("J",murmur_hash("Yeet")));
    // 930cb1ec9242baa6
