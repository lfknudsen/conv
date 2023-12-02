# conv
CLI utility for simple and intuitive currency conversion, connecting to an online exchange server for up-to-date information. Works on UNIX. Written in C.

## Requirements
Uses `libcurl` to connect to the internet. You probably have it already. If not, look for lcurl or similar in your favourite package manager.

## Set-up
1. Go to https://openexchangerates.org/ and create a (free) account to obtain an API key.

2. Provide your API key to the program. Two ways:

   Either edit conv.c where indicated at the top, replacing the placeholder API key with your real one.
   
   OR

   Use the program once, to have a config file `conv.ini` generated in your home directory. Insert your API key in here.\
   If you elect to create it yourself instead, it should look like this:
   
   api_key=XXXXXX

5. Compile and run :)

## Compiling
### On PATH
I recommend compiling to somewhere on your PATH for ease of use. To do this directly:\
`$ make path`\
or\
`$ sudo gcc -o //usr/local/bin/conv conv.c -lcurl`

### In current directory
`$ make`\
or\
`$ gcc -o conv conv.c -lcurl`

## Usage
Assuming the executable is saved to a directory that's an environment variable:\
`$ conv [<Value>] <From> [to] <To>`\
Case insensitive.

### Examples
`$ conv 10 DKK JPY`\
`$ conv 10 GBP to EUR`\
`$ conv usd dkk`\
`$ conv usd to dkk`

## Planned Features
1. General unit conversion.
2. Cached currency information to enable faster/offline use.
