// Menu item, text Serial

/*
  Author: Martin Eden
  Last mod.: 2024-06-02
*/

#include "MenuItem.h"

#include <stdio.h> // printf()

#include <me_BaseTypes.h>

using
  me_MenuItem::TMenuItem,
  me_ManagedMemory::TManagedMemory,
  me_BaseTypes::TUint_2,
  me_BaseTypes::TBool;

/*
  Copy data from our specie
*/
TBool TMenuItem::Set(TMenuItem * Src)
{
  if (!Command.Set(&Src->Command))
    return false;
  if (!Description.Set(&Src->Description))
    return false;
  return true;
}

// Release memory of fields
void TMenuItem::Release()
{
  Command.Release();
  Description.Release();
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
