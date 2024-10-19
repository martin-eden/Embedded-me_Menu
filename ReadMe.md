# What

(2024-05/2024-06, 2024-10)

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
  g - Print led state
  c - Set led LOW
  s - Set led HIGH
  t - Toggle led
  ? - List commands
  ^ - Exit
==
g t g
State(?)
State(LOW)
g t g
State(LOW)
State(HIGH)
c ^
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
