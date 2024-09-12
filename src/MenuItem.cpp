// Menu item, text Serial

/*
  Author: Martin Eden
  Last mod.: 2024-09-12
*/

#include "MenuItem.h"

#include <stdio.h> // printf()

#include <me_MemorySegment.h> // (Reserve/Release)()

using
  me_MenuItem::TMenuItem,
  me_MemorySegment::TMemorySegment;

/*
  Copy data from our specie
*/
TBool TMenuItem::Set(TMenuItem * Src)
{
  TBool IsFullyCopied =
    (Command.Set(Src->Command)) &&
    (Description.Set(Src->Description));

  if (!IsFullyCopied)
  {
    // No memory to fully copy item. No partial results allowed.
    Release();
    return false;
  }

  Handler = Src->Handler;

  return true;
}

/*
  Check for equality

  Current implementation is return true when our command is the same
  as in external data.
*/
TBool TMenuItem::ItsMe(TMemorySegment Data)
{
  return Command.IsEqualTo(Data);
}

/*
  Run item's handler
*/
void TMenuItem::Execute()
{
  Handler.Run();
};

/*
  Release fields memory
*/
void TMenuItem::Release()
{
  Command.Release();
  Description.Release();
}

/*
  Represent state
*/
void TMenuItem::PrintWrappings()
{
  printf("[TMenuItem 0x%04X]", (TUint_2) this);
  printf(" ");
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
  Allocate memory for item structure and copy data

  Memory allocations are done via TMemorySegment.Reserve().
  I found this way more sane and safe than via malloc() or "new".
*/
TBool me_MenuItem::SpawnItem(TMenuItem * * Item, TMenuItem * Value)
{
  TMemorySegment ItemMem;

  if (!ItemMem.Reserve(sizeof(TMenuItem)))
    return false;

  *Item = (TMenuItem *) ItemMem.Start.Addr;

  if (!(*Item)->Set(Value))
  {
    KillItem(*Item);
    return false;
  }

  return true;
}

/*
  Release memory of menu item
*/
void me_MenuItem::KillItem(TMenuItem * Item)
{
  Item->Release();

  TMemorySegment ItemMem;

  ItemMem.Start.Addr = (TUint_2) Item;
  ItemMem.Size = sizeof(TMenuItem);

  ItemMem.Release();
}

/*
  2024-05-25
  2024-05-29
  2024-05-30
  2024-06-02
  2024-06-15
  2024-06-23
  2024-07-06
*/
