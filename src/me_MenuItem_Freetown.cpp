// Menu item, free functions

/*
  Author: Martin Eden
  Last mod.: 2024-10-05
*/

#include "me_MenuItem.h"

#include <me_MemorySegment.h>
#include <me_ManagedMemory.h> // Freetown::(Reserve/Release)()

using
  me_MemorySegment::TMemorySegment;

using namespace me_MenuItem;

/*
  Allocate memory for item structure and copy data

  I don't know why we're using double pointer..
*/
TBool me_MenuItem::Freetown::SpawnItem(
  TMenuItem * * Item,
  TMenuItem * Value
)
{
  /*
    Memory allocations are done via me_ManagedMemory::Freetown::Reserve().
    It's malloc() wrapper that stores allocated block parameters.
    I found this way more sane and safe than direct malloc() or "new".
  */

  TMemorySegment ItemMem;

  if (!me_ManagedMemory::Freetown::Reserve(&ItemMem, sizeof(TMenuItem)))
    return false;

  *Item = (TMenuItem *) ItemMem.Start.Addr;

  if (!(*Item)->Set(Value))
  {
    Freetown::KillItem(*Item);
    return false;
  }

  return true;
}

/*
  Release memory of menu item
*/
void me_MenuItem::Freetown::KillItem(
  TMenuItem * Item
)
{
  /*
    Generally item is two strings and container.

    We're freeing strings memory via Item->Release() and
    container via me_ManagedMemory::Freetown::Release().
  */

  Item->Release();

  TMemorySegment ItemSeg;

  ItemSeg.Start.Addr = (TUint_2) Item;
  ItemSeg.Size = sizeof(TMenuItem);

  me_ManagedMemory::Freetown::Release(&ItemSeg);
}

/*
  2024-05-25
  2024-05-29
  2024-05-30
  2024-06-02
  2024-06-15
  2024-06-23
  2024-07-06
  2024-10-05
*/
