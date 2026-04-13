// [me_Menu] test/demo

/*
  Author: Martin Eden
  Last mod.: 2026-04-13
*/

#include <me_Menu.h>

#include <me_BaseTypes.h>
#include <me_Console.h>
#include <me_Pins.h>

/*
  Sample class that is used for menu demonstration

  For illustration I thought about something very simple
  but with it's own state.

  I came with OUTPUT_LED manager:

    g - (g)et - PrintState() - Print led state
    c - (c)lear - SetLow() - Set led LOW
    s - (s)et - SetHigh() - Set led HIGH

  Commands are strings, they don't need to be one character.

  Design intention of [me_Menu] is program-to-program channel,
  so commands should be short to minimize transmission time.
*/
class TBuiltinLed
{
  public:
    TBuiltinLed();
    void PrintState();
    void ApplyState(TUint_1 State);
    void SetLow();
    void SetHigh();

  private:
    TUint_1 State; // 0 - LOW, 1 - HIGH
    me_Pins::TOutputPin Led;
};

TBuiltinLed::TBuiltinLed()
{
  const TUint_1 LedPinNumber = LED_BUILTIN;
  Led.Init(LedPinNumber);

  SetLow();
}

void TBuiltinLed::PrintState()
{
  Console.Write("State (");

  if (State == 0)
    Console.Write("LOW");
  else
    Console.Write("HIGH");

  Console.Write(")");
  Console.EndLine();
}

void TBuiltinLed::ApplyState(TUint_1 State)
{
  if (State == 0)
    Led.Write(0);
  else
    Led.Write(1);

  this->State = State;
}

void TBuiltinLed::SetLow()
{
  ApplyState(0);
}

void TBuiltinLed::SetHigh()
{
  ApplyState(1);
}

// --

/*
  Wrappers for class methods
*/
void PrintState_Handler(
  TAddress InstanceAddr
)
{
  TBuiltinLed * LedManager = (TBuiltinLed *) InstanceAddr;
  LedManager->PrintState();
}

void SetLow_Handler(
  TAddress InstanceAddr
)
{
  TBuiltinLed * LedManager = (TBuiltinLed *) InstanceAddr;
  LedManager->SetLow();
}

void SetHigh_Handler(
  TAddress InstanceAddr
)
{
  TBuiltinLed * LedManager = (TBuiltinLed *) InstanceAddr;
  LedManager->SetHigh();
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
    me_Menu::Freetown::ToItem;

  TAddress InstanceAddr = (TAddress) LedManager;

  Menu->AddItem(ToItem("g", "Print led state", PrintState_Handler, InstanceAddr));
  Menu->AddItem(ToItem("c", "Set led LOW", SetLow_Handler, InstanceAddr));
  Menu->AddItem(ToItem("s", "Set led HIGH", SetHigh_Handler, InstanceAddr));
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

  Menu.AddBuiltinCommands();
  Menu.Print();

  Menu.Run();
}

void setup()
{
  Console.Init();

  Console.Print("( [me_Menu] test");
  RunTest();
  Console.Print(") Done");
}

void loop()
{
}

// --

/*
  2024 # # # # # # # # # # # #
  2025-08-30
  2025-09-19
*/
