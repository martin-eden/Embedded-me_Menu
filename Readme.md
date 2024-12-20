## What

(2024-05/2024-06, 2024-10)

Text menu and handler for commands. Arduino library.

Build your device handler with this!

No infinite "if-else" code spans to handle command.

You populate list (aka "menu") at your pace and at your places.

Each item is command, description and handler.

Then call "Run()" and it will handle input and call your handlers.


## Adding commands

That's adapted excerpt from [example][Example] showing how to add items
to menu. `g`, `c`, `s`, `t` are menu items commands. When code gets one
of them from UART, it executes item handler.

In our case `PrintState_Handler` calls object method to print LED state
to UART.

```C++
#include <me_Menu.h>
// ...
void PrintState_Handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TBuiltinLed * LedManager = (TBuiltinLed *) Instance;
  LedManager->PrintState();
}
// ...
me_Menu::TMenu Menu;
TBuiltinLed LedManager;
// ...
using
  me_Menu::Freetown::ToItem;

TUint_2 InstanceAddr = (TUint_2) &LedManager;

Menu.AddItem(ToItem("g", "Print led state", PrintState_Handler, InstanceAddr));
Menu.AddItem(ToItem("c", "Set led LOW", SetLow_Handler, InstanceAddr));
Menu.AddItem(ToItem("s", "Set led HIGH", SetHigh_Handler, InstanceAddr));
Menu.AddItem(ToItem("t", "Toggle led", Toggle_Handler, InstanceAddr));
// ...
Menu.Run();
```

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


## Install/remove

Easy way is to clone [GetLibs][GetLibs] repo and run it's code.


## Compile

Zero-warnings compilation:

```bash
arduino-cli compile --fqbn arduino:avr:uno --quiet --warnings all . --build-property compiler.cpp.extra_flags="-std=c++1z"
```

## Code

* [Example][Example]
* [Interface][Interface]
* [Implementation][Implementation]


## See also

* [My other embedded C++ libraries][Embedded]
* [My other repositories][Repos]

[Example]: examples/me_Menu/me_Menu.ino
[Interface]: src/me_Menu.h
[Implementation]: src/me_Menu.cpp

[GetLibs]: https://github.com/martin-eden/Embedded-Framework-GetLibs

[Embedded]: https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts
[Repos]: https://github.com/martin-eden/contents
