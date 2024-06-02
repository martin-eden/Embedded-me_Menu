// Menu item, text Serial

/*
  Author: Martin Eden
  Last mod.: 2024-05-30
*/

#include "MenuItem.h"

#include <stdio.h> // printf()

#include <me_BaseTypes.h>

using
  me_MenuItem::TMenuItem,
  me_BaseTypes::TUint_2,
  me_BaseTypes::TBool;

// Release memory upon death
TMenuItem::~TMenuItem()
{
  PrintTag();

  printf(" ");
  printf("Destructor is here.\n");
  PrintWrappings();

  Command.ReleaseChunk();
  Description.ReleaseChunk();
}

// Set <.Command> to memory copy of argument
TBool TMenuItem::SetCommand(TMemorySegment * OuterCommand)
{
  return Command.CloneFrom(OuterCommand);
}

// Set <.Description> to memory copy of argument
TBool TMenuItem::SetDescription(TMemorySegment * OuterDescription)
{
  return Description.CloneFrom(OuterDescription);
}

// Set fields to copies from <Src>
TBool TMenuItem::CloneFrom(TMenuItem * Src)
{
  if (!SetCommand(&Src->Command))
    return false;
  if (!SetDescription(&Src->Description))
    return false;
  return true;
}

// Represent data
void TMenuItem::Print()
{
  Command.Print();
  printf(" - ");
  Description.Print();
  printf("\n");
}

void TMenuItem::PrintTag()
{
  printf("[TMenuItem 0x%04X]", (TUint_2) this);
}

// Represent state
void TMenuItem::PrintWrappings()
{
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
  2024-06-02
*/
