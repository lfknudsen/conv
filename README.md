# conv
CLI utility for simple and intuitive unit conversion. Written in C. Tested on (GNU/)Linux.

## Dependencies
In addition to the C standard library, this program uses `libcurl` to connect
to the online exchange server for currency conversion.

If you don't wish to use this feature, there will be no set-up required, but the
program still expects the library. To remove this (in addition to potentially editing Makefile to remove `-lcurl`):
   * In `curr.c`:
      Delete anything involving `curl`.
   * In `conv.c`:
      Remove `#include <curl/curl.h>`.

## Currency Conversion Set-up
1. Go to https://openexchangerates.org/ and create a (free) account to obtain an API key.

2. Provide your API key to the program. There are two ways to do so:

   1. Edit `conv.c` where indicated at the top of the file, replacing the placeholder API key with your real one.

   OR

   2. Execute the program once to have a config file `conv.ini` generated in your home directory. Insert your API key in here.\
      If you elect to create it yourself instead, it should look like this:

      api_key=XXXXXX

5. Compile and run :)

## Compiling
### On PATH
I recommend compiling to somewhere on your PATH for ease of use. To do this directly:\
`$ make path`\
or\
`$ sudo gcc -o //usr/local/bin/conv conv.c parse.c curr.c temperature.c length.c -lcurl`

Alternatively, use the regular compilation, and add a fitting alias to your shell configuration.

### In current directory
`$ make`\
or\
`$ gcc -o conv conv.c parse.c curr.c temperature.c length.c -lcurl`

## Usage
Assuming the executable is called with `conv`:\
`$ conv [<Value>] <From> [to] <To>`\
Case insensitive.

### Examples
```
conv 10 DKK JPY
```
```
conv 10 GBP to EUR
```
```
conv usd dkk
```
```
conv usd to dkk
```
```
conv 10 c f
```
```
conv 10 kelvin rankine
```
```
conv 10 Rømer to Delisle
```
```
conv 10 Ro to CELSIUS
```
```
conv 10 picas to points
```
```
conv 17 yards to ft
```

## Supported temperature scales
Matches greedily to smallest required info, so ***R*** = ***R***ankine, ***Re*** = ***Re***aumur, and ***Re***nkine = ***Re***aumur.

Celsius, Kelvin, Fahrenheit, Rankine, Newton, Delisle, Réaumur/Reaumur, Rømer/Roemer/Romer.

## Supported units of length
Unless otherwise specified, units follow the international definition.

### SI units:
All metre-based units from yoctometres (10<sup>-24</sup>) to ronnametres (10<sup>27</sup>)
are implemented. Note that the output is limited to six decimal places.

### U.S. customary/British imperial units:
Miles, thous, inches, feet, yards, statute miles, chains, furlongs, rods.

### Typographical units:
Picas, points, twips.

### Nautical units:
Fathoms, cable lengths, (U.S.) nautical miles.

### Misc.:
Hand.

## Features considered for the future
1. Cached currency information to enable faster/offline use.
