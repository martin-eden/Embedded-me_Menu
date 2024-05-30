// Text menu navigation via Serial

/*
  Author: Martin Eden
  Last mod.: 2024-05-30
*/

#include "me_Menu.h"

#include <stdio.h> // printf()

#include <me_List.h>
#include <me_MemorySegment.h> // (Reserve/Release)Chunk()
#include <me_BaseTypes.h>

using
  me_Menu::TMenu,
  me_MemorySegment::TMemorySegment,
  me_BaseTypes::TBool;

/*
  Add menu item to menu

  We allocate memory for TMenuItem and TNode (list).
  Menu item data memory is allocated internally in CloneFrom().

  Memory allocations is done via TMemorySegment.ReserveChunk().
  I found it is more sane way than via malloc() or "new".
*/
TBool TMenu::AddItem(TMenuItem * OuterMenuItem)
{
  printf("> AddItem()\n");
  OuterMenuItem->PrintWrappings();

  TMemorySegment MenuItemSeg;
  MenuItemSeg.Size = sizeof(TMenuItem);
  MenuItemSeg.ReserveChunk();

  TMenuItem * MenuItem = (TMenuItem *) MenuItemSeg.Start.Addr;
  MenuItem->CloneFrom(OuterMenuItem);
  MenuItem->PrintWrappings();

  using me_List::TNode;

  TMemorySegment NodeSeg;
  NodeSeg.Size = sizeof(TNode);
  NodeSeg.ReserveChunk();

  TNode * ListNodePtr = (TNode *) NodeSeg.Start.Addr;

  ListNodePtr->DataPtr = MenuItemSeg.Start.Addr;

  List.Add(ListNodePtr);
  ListNodePtr->PrintWrappings();

  printf("\n");

  printf("< AddItem()\n");

  return true;
}

void TMenu::Print()
{
}

void TMenu::PrintWrappings()
{
}

void TMenu::GetSelection()
{
}

/*
  2024-05-30
*/
