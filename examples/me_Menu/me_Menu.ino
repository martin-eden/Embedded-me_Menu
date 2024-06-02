// [me_Menu] test/demo

/*
  Author: Martin Eden
  Last mod.: 2024-06-02
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

void TestMenu()
{
  using
    me_Menu::TMenu,
    me_Menu::TMenuItem;

  TMenu Menu;

  TMenuItem MenuItem;

  MenuItem.Command.CloneFrom("Put");
  MenuItem.Description.CloneFrom("Put data in range");
  Menu.Add(&MenuItem);

  MenuItem.Command.CloneFrom("Get");
  MenuItem.Description.CloneFrom("Get data in range");
  Menu.Add(&MenuItem);

  MenuItem.Command.CloneFrom("SetRange");
  MenuItem.Description.CloneFrom("Set memory range");
  Menu.Add(&MenuItem);

  MenuItem.Command.CloneFrom("GetRange");
  MenuItem.Description.CloneFrom("Get memory range");
  Menu.Add(&MenuItem);

  Menu.Print();

  Menu.RemoveAll();
}

/*
  2024-05-25
  2024-05-29
  2024-05-30
  2024-06-01
  2024-06-02
*/
