# What

(2024-05 .. 2024-06)

Text menu for commands. Arduino library.

Menu is a list. Maybe another month I'll make it a tree.


## Example output

```
[me_Menu] We are here.
--
g - Print last value written
c - Set led LOW
t - Set led HIGH
==
g
State(unknown)
c
g
State(LOW)
t
g
State(HIGH)
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
