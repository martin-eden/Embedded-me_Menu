// [me_Menu] test/demo

/*
  Author: Martin Eden
  Last mod.: 2024-06-04
*/

#include <me_Menu.h>

#include <me_UartSpeeds.h>
#include <me_InstallStandardStreams.h>
#include <me_BaseTypes.h>

void setup()
{
  Serial.begin(me_UartSpeeds::Arduino_Normal_Bps);
  InstallStandardStreams();
  printf("[me_MenuItem] We are here.\n");

  TestMenu();

  printf("Done.\n");
}

void loop()
{
}

// Forwards:
void Test_BasicUsage();

void TestMenu()
{
  Test_BasicUsage();
}

void Test_BasicUsage()
{
  using
    me_Menu::TMenu,
    me_Menu::TMenuItem;

  TMenu Menu;

  TMenuItem Item;

  Item.Command.Set("Put");
  Item.Description.Set("Put data in range");
  Menu.Add(&Item);

  Item.Command.Set("Get");
  Item.Description.Set("Get data in range");
  Menu.Add(&Item);

  Item.Command.Set("SetRange");
  Item.Description.Set("Set memory range");
  Menu.Add(&Item);

  Item.Command.Set("GetRange");
  Item.Description.Set("Get memory range");
  Menu.Add(&Item);

  Menu.Print();
}

/*
  2024-05-25
  2024-05-29
  2024-05-30
  2024-06-01
  2024-06-02
  2024-06-04
*/
