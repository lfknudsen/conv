# conv
CLI utility for simple and intuitive currency conversion, connecting to an online exchange server for up-to-date information. Written in C.

## Requirements
Uses `libcurl` to connect to the internet. You probably have it already, but now you're aware.

## Set-up
1. Go to https://openexchangerates.org/ and create a (free) account to obtain an API key.

2. Edit conv.c where indicated at the top, replacing the placeholder API key with your real one.

3. Compile and run :)

## Compiling
`make`

or

`gcc -o conv conv.c -lcurl`

## Usage
`./conv [<Value>] <From> [to] <To>`

Case insensitive.

### Examples
`./conv 10 DKK JPY`

`./conv 10 GBP to EUR`

`./conv usd dkk`

`./conv usd to dkk`

## Planned Features
1. General unit conversion.
2. Cached currency information to enable faster/offline use.
