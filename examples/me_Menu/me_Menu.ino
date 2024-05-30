// [me_Menu] test/demo

/*
  Author: Martin Eden
  Last mod.: 2024-05-30
*/

#include <me_Menu.h>

#include <me_InstallStandardStreams.h>
#include <me_UartSpeeds.h>

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
    me_MenuItem::TMenuItem,
    me_MemorySegment::FromAsciiz;

  // "Get data" command
  TMenuItem Get_Cmd =
    {
      .Command = FromAsciiz("G"),
      .Description = FromAsciiz("Get data in range"),
    };

  Get_Cmd.PrintWrappings();
  Get_Cmd.Print();
}

/*
  2024-05-25
  2024-05-29
  2024-05-30
*/
