// [WIP] Menu navigation

/*
  Author: Martin Eden
  Last mod.: 2024-05-30
*/

#include "me_Menu.h"

#include <stdio.h> // printf()

#include <me_BaseTypes.h>

using
  me_MenuItem::TMenuItem,
  me_BaseTypes::TBool;

// Set fields to data copy of segments
TMenuItem::TMenuItem(
  TMemorySegment OuterCommand,
  TMemorySegment OuterDescription
)
{
  Command = { { 0 }, .Size = 0 };
  SetCommand(OuterCommand);

  Description = { { 0 }, .Size = 0 };
  SetDescription(OuterDescription);
}

// Release memory upon death
TMenuItem::~TMenuItem()
{
  Command.ReleaseChunk();
  Description.ReleaseChunk();
}

// Set .Command to memory copy of argument
TBool TMenuItem::SetCommand(TMemorySegment OuterCommand)
{
  return Command.CloneFrom(OuterCommand);
}

// Set .Description to memory copy of argument
TBool TMenuItem::SetDescription(TMemorySegment OuterDescription)
{
  return Description.CloneFrom(OuterDescription);
}

// Represent data
void TMenuItem::Print()
{
  Command.Print();
  printf(" - ");
  Description.Print();
  printf("\n");
}

// Represent state
void TMenuItem::PrintWrappings()
{
  using me_BaseTypes::TUint_2;

  printf("[0x%04X]", (TUint_2) this);

  printf("(\n");

  printf("  Command ");
  Command.PrintWrappings();
  printf("\n");

  printf("  Description ");
  Description.PrintWrappings();
  printf("\n");

  printf(")\n");
}

/*
  2024-05-25
  2024-05-29
  2024-05-30
*/
