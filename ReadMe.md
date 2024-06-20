# What

(2024-05 .. 2024-06)

Text menu and handler for commands. Arduino library.

Build your device handler with this!

No infinite "if-else" code spans to handle command.

You populate list (aka "menu") at your pace and at your places.

Each item is command, description and handler.

Then call "Run()" and it will handle input and call your handlers.

## Example interaction

```
[me_Menu] We are here.
--
g - Print last value written
c - Set led LOW
t - Set led HIGH
? - List commands
^ - Exit
==
g
State(unknown)
t g
State(HIGH)
c g
State(LOW)
^
[me_Menu] Done.
```

## Requirements

  * arduino-cli
  * bash


## Install

Run [Install.sh](Install.sh).


## Remove

Run [Remove.sh](Remove.sh).


# Compile

Zero-warnings compilation:

```bash
arduino-cli compile --fqbn arduino:avr:uno --quiet --warnings all . --build-property compiler.cpp.extra_flags="-std=c++1z"
```

# Code

* [Example](examples/me_Menu/me_Menu.ino)
* [Interface](src/me_Menu.h)
* [Implementation](src/me_Menu.cpp)


# See also

* [My other repositories](https://github.com/martin-eden/contents)
