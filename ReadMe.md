# What

(2024-05 .. )

Arduino library for text menu navigation via Serial.

Work in progress but it's gonna be nice functionality.

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
