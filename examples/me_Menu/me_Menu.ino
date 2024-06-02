// [me_Menu] test/demo

/*
  Author: Martin Eden
  Last mod.: 2024-06-01
*/

#include <me_Menu.h>

#include <me_InstallStandardStreams.h>
#include <me_UartSpeeds.h>
#include <me_BaseTypes.h>

// Forwards:
void TestMenu();

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
    me_Menu::TMenuItem,
    me_MemorySegment::FromAsciiz,
    me_MemorySegment::TMemorySegment,
    me_BaseTypes::TUint_2;

  TMenu Menu;

  TMenuItem Command;

  /*
    DON'T do so.

    TMenuItem owns fields memory and will try to free temporary
    strings from FromAsciiz() casts.

    Command =
      {
        .Command = FromAsciiz("Put"),
        .Description = FromAsciiz("Put data in range"),
      };
  */


  TMemorySegment MemSeg;
  MemSeg = FromAsciiz("Put");
  Command.SetCommand(&MemSeg);
  MemSeg = FromAsciiz("Put data in range");
  Command.SetDescription(&MemSeg);
  Menu.AddItem(&Command);

  /*
  Command.SetCommand(&FromAsciiz("Get"));
  Command.SetDescription(&FromAsciiz("Get data in range"));
  Menu.AddItem(&Command);

  Command.SetCommand(&FromAsciiz("SetRange"));
  Command.SetDescription(&FromAsciiz("Set memory range"));
  Menu.AddItem(&Command);

  Command.SetCommand(&FromAsciiz("GetRange"));
  Command.SetDescription(&FromAsciiz("Get memory range"));
  Menu.AddItem(&Command);
  */

  Menu.Print();
}

/*
  2024-05-25
  2024-05-29
  2024-05-30
*/
