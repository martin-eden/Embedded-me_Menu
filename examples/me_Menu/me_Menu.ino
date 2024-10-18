// [me_Menu] test/demo

/*
  Author: Martin Eden
  Last mod.: 2024-10-18
*/

#include <me_Menu.h>

#include <me_UartSpeeds.h>
#include <me_InstallStandardStreams.h>
#include <me_BaseTypes.h>
#include <me_MemorySegment.h>
#include <me_StoredCall.h>

// Forwards:
class TBuiltinLed;

void setup()
{
  Serial.begin(me_UartSpeeds::Arduino_Normal_Bps);

  // Serial timeout (ms) is essential when reading from stream
  Serial.setTimeout(15);

  InstallStandardStreams();

  printf("[me_Menu] We are here.\n");
  Test();
  printf("[me_Menu] Done.\n");
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

    g - (g)et - PrintState() - Print led state
    c - (c)lear - SetLow() - Set led LOW
    s - (s)et - SetHigh() - Set led HIGH
    t - (t)oggle - Toggle() - Toggle state

  Commands are strings, they don't need to be one character.

  Design intention of [me_Menu] is program-to-program channel,
  so commands should be short to minimize transmission time.
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
  printf("State(");

  if (State == 0)
    printf("unknown");
  else if (State == 1)
    printf("LOW");
  else if (State == 2)
    printf("HIGH");
  else
    printf("?"); // WTF?

  printf(")\n");
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
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TBuiltinLed * LedManager = (TBuiltinLed *) Instance;
  LedManager->PrintState();
}

void SetLow_Handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TBuiltinLed * LedManager = (TBuiltinLed *) Instance;
  LedManager->SetLow();
}

void SetHigh_Handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TBuiltinLed * LedManager = (TBuiltinLed *) Instance;
  LedManager->SetHigh();
}

void Toggle_Handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
{
  TBuiltinLed * LedManager = (TBuiltinLed *) Instance;
  LedManager->Toggle();
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

  TUint_2 InstanceAddr = (TUint_2) &LedManager;

  Menu->AddItem(ToItem("g", "Print led state", PrintState_Handler, InstanceAddr));
  Menu->AddItem(ToItem("c", "Set led LOW", SetLow_Handler, InstanceAddr));
  Menu->AddItem(ToItem("s", "Set led HIGH", SetHigh_Handler, InstanceAddr));
  Menu->AddItem(ToItem("t", "Toggle led", Toggle_Handler, InstanceAddr));
}

// --

/*
  Menu list life
*/
void Test()
{
  me_Menu::TMenu Menu;
  TBuiltinLed LedManager;

  AddItems(&Menu, &LedManager);

  Menu.AddBuiltinCommands();
  Menu.Print();
  Menu.Run();
}

/*
  2024-05 3
  2024-06 6
  2024-10-05
  2024-10-18
*/
