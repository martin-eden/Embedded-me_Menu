// [me_Menu] test/demo

/*
  Author: Martin Eden
  Last mod.: 2024-12-15
*/

#include <me_Menu.h>

#include <me_BaseTypes.h>
#include <me_Uart.h>
#include <me_Console.h>

// Forwards:
class TBuiltinLed;

void setup()
{
  me_Uart::Init(me_Uart::Speed_115k_Bps);

  Console.Print("[me_Menu] We are here.");
  RunTest();
  Console.Print("[me_Menu] Done.");
}

void loop()
{
}

// --

/*
  Sample class that is used for menu demonstration

  For illustration I thought about something very simple
  but with it's own state.

  I came with OUTPUT_LED manager:

    PrintState() - Print led state
    SetLow() - Set led LOW
    SetHigh() - Set led HIGH
    Toggle() - Toggle state
*/
class TBuiltinLed
{
  private:
    TUint_1 State = 0; // 0 - unknown, 1 - LOW, 2 - HIGH

  public:
    TBuiltinLed() { pinMode(LED_BUILTIN, OUTPUT); };
    void PrintState();
    void ApplyState();
    void SetLow();
    void SetHigh();
    void Toggle();
};

void TBuiltinLed::PrintState()
{
  Console.Write("State ( ");

  if (State == 0)
    Console.Write("unknown");
  else if (State == 1)
    Console.Write("LOW");
  else if (State == 2)
    Console.Write("HIGH");
  else
    Console.Write("?"); // WTF?

  Console.Write(" )");
  Console.EndLine();
}

void TBuiltinLed::ApplyState()
{
  if (State == 1)
    digitalWrite(LED_BUILTIN, LOW);

  if (State == 2)
    digitalWrite(LED_BUILTIN, HIGH);
}

void TBuiltinLed::SetLow()
{
  State = 1;

  ApplyState();
}

void TBuiltinLed::SetHigh()
{
  State = 2;

  ApplyState();
}

void TBuiltinLed::Toggle()
{
  // We can do fancy modular arithmetic here. But we won't
  if (State == 1)
    State = 2;
  else
    State = 1;

  ApplyState();
}

// --

/*
  Wrappers for class methods

  Because I did not find a way to get pointer to member function.

  We are using universal

    handler data instance
    ~~~~~~~ ~~~~ ~~~~~~~~
      ui2    ui2   ui2

  approach to call function with data and pointer to state.

  In this case we have nothing for "data". Menu does not use it.
*/
void PrintState_Handler(
  TAddress Data [[gnu::unused]],
  TAddress Instance
)
{
  TBuiltinLed * LedManager = (TBuiltinLed *) Instance;
  LedManager->PrintState();
}

void SetLow_Handler(
  TAddress Data [[gnu::unused]],
  TAddress Instance
)
{
  TBuiltinLed * LedManager = (TBuiltinLed *) Instance;
  LedManager->SetLow();
}

void SetHigh_Handler(
  TAddress Data [[gnu::unused]],
  TAddress Instance
)
{
  TBuiltinLed * LedManager = (TBuiltinLed *) Instance;
  LedManager->SetHigh();
}

void Toggle_Handler(
  TAddress Data [[gnu::unused]],
  TAddress Instance
)
{
  TBuiltinLed * LedManager = (TBuiltinLed *) Instance;
  LedManager->Toggle();
}

// --

/*
  Print human-friendly text about commands
*/
void PrintHelp()
{
  static const TAsciiz HelpText =
    R"(
Hello traveler!

This is a menu system for other programs.

It contains list of commands. Each command is just string.
Entering that string executes command. (Which may read
additional data if needed.)

Stock menu provides two commands:

  ^ - exit menu
  ? - print list of available commands

There are no human-friendly description for command.
Because command may be added to menu at run-time.
And description have no purpose in program-program
communication.

List of additional commands for this demo:

  t - toggle LED
  n - set LED on
  f - set LED off
  p - print state of LED

Actually this game is more challenging when
you figuring out it by yourself.

We're not malevolent. We're just not storing
data we don't use.

-- Martin, 2024-12-15
)";

  Console.Print(HelpText);
}

// --

/*
  Populate menu

  When wiring item handlers we need class instance,
  <TBuiltinLed> in this case.
*/
void AddItems(
  me_Menu::TMenu * Menu,
  TBuiltinLed * LedManager
)
{
  using
    me_Menu::AddNewItem,
    me_Menu::AddBuiltinCommands;

  TAddress InstanceAddr = (TAddress) &LedManager;

  AddNewItem(Menu, "p", PrintState_Handler, InstanceAddr);
  AddNewItem(Menu, "f", SetLow_Handler, InstanceAddr);
  AddNewItem(Menu, "n", SetHigh_Handler, InstanceAddr);
  AddNewItem(Menu, "t", Toggle_Handler, InstanceAddr);

  AddBuiltinCommands(Menu);
}

// --

/*
  Menu list life
*/
void RunTest()
{
  me_Menu::TMenu Menu;
  TBuiltinLed LedManager;

  AddItems(&Menu, &LedManager);

  PrintHelp();

  Menu.PrintCommands();

  Menu.Run();
}

/*
  2024-05 ###
  2024-06 ######
  2024-10 ###
  2024-11 #
  2024-12-11
  2024-12-15
*/
