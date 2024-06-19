// [me_Menu] test/demo

/*
  Author: Martin Eden
  Last mod.: 2024-06-20
*/

#include <me_Menu.h>

#include <me_UartSpeeds.h>
#include <me_InstallStandardStreams.h>
#include <me_BaseTypes.h>

using
  me_BaseTypes::TUint_1,
  me_BaseTypes::TUint_2;

void setup()
{
  delay(4000);
  Serial.begin(me_UartSpeeds::Arduino_Normal_Bps);
  Serial.setTimeout(15);
  InstallStandardStreams();
  printf("[me_Menu] We are here.\n");

  Test();

  printf("Done.\n");
}

void loop()
{
}

/*
  Sample class that is used for menu demonstration

  For illustration I thought about something very simple
  but with it's own state.

  I came with OUTPUT_LED manager:

    g - (g)et - PrintState() - Print last value written
    c - (c)lear - SetLow() - Set led LOW
    t - se(t) - SetHigh() - Set led HIGH

  Commands are strings, they don't need to be one character.
  But main intention of [me_Menu] is program-to-program channel,
  so commands should be as short as possible to minimize channel
  transmission time.
*/
class TBuiltinLed
{
  TUint_1 State = 0; // 0 - unknown, 1 - LOW, 2 - HIGH

  public:
    TBuiltinLed() { pinMode(LED_BUILTIN, OUTPUT); };
    void PrintState();
    void SetLow();
    void SetHigh();
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

void TBuiltinLed::SetLow()
{
  digitalWrite(LED_BUILTIN, LOW);
  State = 1;
}

void TBuiltinLed::SetHigh()
{
  digitalWrite(LED_BUILTIN, HIGH);
  State = 2;
}

/*
  Ugly wrappers for class methods

  Because I did not find a way to get pointer to member function
  when we are setting <.Method>.

  <TMethodCall> knows nothing about fancy classes it stores.
  And should know nothing. It's job just to call routine with
  TUint_2 argument.
*/
void PrintState_wrap(TUint_2 Instance)
{
  TBuiltinLed * LedManager = (TBuiltinLed *) Instance;
  LedManager->PrintState();
}

void SetLow_wrap(TUint_2 Instance)
{
  TBuiltinLed * LedManager = (TBuiltinLed *) Instance;
  LedManager->SetLow();
}

void SetHigh_wrap(TUint_2 Instance)
{
  TBuiltinLed * LedManager = (TBuiltinLed *) Instance;
  LedManager->SetHigh();
}

TBuiltinLed LedManager;

/*
  Populate menu

  When wiring item handlers we need to see class instance,
  <LedManager> in this case.
*/
void AddItems(me_Menu::TMenu * Menu)
{
  me_Menu::TMenuItem Item;

  Item.Command.Set("g");
  Item.Description.Set("Print last value written");
  Item.Method.Set((TUint_2) &LedManager, (TUint_2) &PrintState_wrap);
  Menu->Add(&Item);

  Item.Command.Set("c");
  Item.Description.Set("Set led LOW");
  Item.Method.Set((TUint_2) &LedManager, (TUint_2) &SetLow_wrap);
  Menu->Add(&Item);

  Item.Command.Set("t");
  Item.Description.Set("Set led HIGH");
  Item.Method.Set((TUint_2) &LedManager, (TUint_2) &SetHigh_wrap);
  Menu->Add(&Item);
}

/*
  Menu list life

  This function never returns, there are no "exit" command
  in Menu.Run() so far.
*/
void Test()
{
  me_Menu::TMenu Menu;

  AddItems(&Menu);
  Menu.Print();
  Menu.Run();
}

/*
  2024-05-25
  2024-05-29
  2024-05-30
  2024-06-01
  2024-06-02
  2024-06-04
  2024-06-16
  2024-06-20
*/
