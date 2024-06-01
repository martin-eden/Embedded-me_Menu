// Text menu navigation via Serial

/*
  Author: Martin Eden
  Last mod.: 2024-06-01
*/

#include "me_Menu.h"

#include <stdio.h> // printf()

#include <me_List.h>
#include <me_MemorySegment.h> // (Reserve/Release)Chunk()
#include <me_BaseTypes.h>

using
  me_Menu::TMenu,
  me_MemorySegment::TMemorySegment,
  me_BaseTypes::TBool,
  me_List::TNode,
  me_List::Traverse;

/*
  Add menu item to menu

  We allocate memory for TMenuItem and TNode (list).
  Menu item data memory is allocated internally in CloneFrom().

  Memory allocations is done via TMemorySegment.ReserveChunk().
  I found it is more sane way than via malloc() or "new".
*/
TBool TMenu::AddItem(TMenuItem * OuterMenuItem)
{
  TMemorySegment MenuItemSeg;

  MenuItemSeg.Size = sizeof(TMenuItem);
  MenuItemSeg.ReserveChunk();
  TMenuItem * MenuItem = (TMenuItem *) MenuItemSeg.Start.Addr;

  MenuItem->CloneFrom(OuterMenuItem);

  using me_List::TNode;

  TMemorySegment NodeSeg;
  NodeSeg.Size = sizeof(TNode);
  NodeSeg.ReserveChunk();
  TNode * ListNode = (TNode *) NodeSeg.Start.Addr;

  ListNode->DataPtr = MenuItemSeg.Start.Addr;

  List.Add(ListNode);

  return true;
}

/*
  Print menu item
*/
TBool PrintListNode(TNode * ListNode)
{
  using
    me_Menu::TMenuItem;

  TMenuItem * MenuItem = (TMenuItem *) ListNode->DataPtr;

  MenuItem->Print();

  return true;
}

/*
  Print menu
*/
void TMenu::Print()
{
  printf("--\n");
  Traverse(List.HeadPtr, PrintListNode);
  printf("==\n");
}

void TMenu::PrintWrappings()
{
}

void TMenu::GetSelection()
{
}

/*
  2024-05-30
  2024-06-01
*/
