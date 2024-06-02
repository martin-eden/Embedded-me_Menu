// Text menu navigation via Serial

/*
  Author: Martin Eden
  Last mod.: 2024-06-02
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
  me_List::TListNode;

/*
  Add menu item to menu

  We allocate memory for TMenuItem and TNode (list).
  Menu item data memory is allocated internally in CloneFrom().

  Memory allocations is done via TMemorySegment.ReserveChunk().
  I found it is more sane way than via malloc() or "new".
*/
TBool TMenu::Add(TMenuItem * OuterMenuItem)
{
  TMemorySegment MenuItemSeg;

  MenuItemSeg.Reserve(sizeof(TMenuItem));
  TMenuItem * MenuItem = (TMenuItem *) MenuItemSeg.Start.Addr;

  MenuItem->CloneFrom(OuterMenuItem);

  TMemorySegment NodeSeg;

  NodeSeg.Reserve(sizeof(TListNode));
  TListNode * ListNode = (TListNode *) NodeSeg.Start.Addr;

  ListNode->Data = MenuItemSeg.Start.Addr;

  List.Add(ListNode);

  return true;
}

/*
  Release memory of menu item
*/
TBool KillMenuItem(TListNode * Node)
{
  using me_Menu::TMenuItem;

  TMenuItem * Item = (TMenuItem *) Node->Data;

  Item->Release();

  return true;
}

/*
  Remove all items from the list and release their memory
*/
void TMenu::RemoveAll()
{
  Traverse(List.Head, KillMenuItem);
  KillList(List.Head);
  List.Head = 0;
}

/*
  Print menu item
*/
TBool PrintListNode(TListNode * ListNode)
{
  using me_Menu::TMenuItem;

  TMenuItem * MenuItem = (TMenuItem *) ListNode->Data;

  MenuItem->Print();

  return true;
}

/*
  Print menu
*/
void TMenu::Print()
{
  printf("--\n");
  me_List::Traverse(List.Head, PrintListNode);
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
  2024-06-02
*/
