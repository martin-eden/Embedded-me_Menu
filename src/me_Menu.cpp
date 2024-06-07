// Text menu navigation via Serial

/*
  Author: Martin Eden
  Last mod.: 2024-06-07
*/

#include "me_Menu.h"

#include <stdio.h> // printf()

#include <me_List.h>
#include <me_MemorySegment.h> // (Reserve/Release)Chunk()
#include <me_SerialTokenizer.h> // GetEntity()
#include <me_BaseTypes.h>

using
  me_Menu::TMenu,
  me_MemorySegment::TMemorySegment,
  me_BaseTypes::TBool,
  me_BaseTypes::TUint_2,
  me_BaseTypes::TChar,
  me_List::TListNode;

/*
  Destructor

  Release memory from list nodes and menu items inside.
*/
TMenu::~TMenu()
{
  Release();
}

/*
  Add menu item to menu

  We are doing these memory allocations:

    1. Structure of menu item
    2. Data of menu item
    3. Structure of list node.

  Memory allocations is done via TMemorySegment.Reserve().
  I found this way more sane and safe than via malloc() or "new".
*/
TBool TMenu::Add(TMenuItem * OuterMenuItem)
{
  TMemorySegment MenuItemSeg;

  if (!MenuItemSeg.Reserve(sizeof(TMenuItem)))
  {
    // No memory for new menu item structure
    return false;
  }
  TMenuItem * MenuItem = (TMenuItem *) MenuItemSeg.Start.Addr;

  if (!MenuItem->Set(OuterMenuItem))
  {
    // No memory to copy data (command and description)
    MenuItemSeg.Release();
    return false;
  }

  TMemorySegment NodeSeg;

  if (!NodeSeg.Reserve(sizeof(TListNode)))
  {
    // No memory for new list node
    MenuItem->Release();
    MenuItemSeg.Release();
    return false;
  }

  TListNode * ListNode = (TListNode *) NodeSeg.Start.Addr;

  ListNode->Data = (TUint_2) MenuItem;

  List.Add(ListNode);

  return true;
}

/*
  Release memory of menu item

  We are releasing

    1. Data of menu item
    2. Structure of menu item
    3. List node structure
*/
TBool KillMenuItem(TListNode * Node)
{
  using me_Menu::TMenuItem;

  TMenuItem * Item = (TMenuItem *) Node->Data;

  Item->Release();

  TMemorySegment ItemSeg;
  ItemSeg.Start.Addr = (TUint_2) Item;
  ItemSeg.Size = sizeof(TMenuItem);
  ItemSeg.Release();

  TMemorySegment ListNodeSeg;
  ListNodeSeg.Start.Addr = (TUint_2) Node;
  ListNodeSeg.Size = sizeof(TListNode);
  ListNodeSeg.Release();

  return true;
}

/*
  Release memory of all items in the list and memory of list.
*/
void TMenu::Release()
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

/*
  Get command from serial and match it to our list
*/
TBool TMenu::GetSelection(TMenuItem * ItemSelected)
{
  const TUint_2 InputBufferSize = 16;
  TChar Buffer[InputBufferSize];

  TMemorySegment BufferSeg;
  BufferSeg.Start.Addr = (TUint_2) &Buffer;
  BufferSeg.Size = sizeof(Buffer);

  using namespace me_SerialTokenizer;

  printf(": ");

  TCapturedEntity Entity;

  while (!GetEntity(&Entity, BufferSeg));

  printf("\n");

  if (Entity.IsTrimmed)
  {
    printf("Too long.\n");
    return false;
  }

  return Match(ItemSelected, Entity.Segment);
}

/*
  Find entity in list

  We are matching string in <Entity> to <.Command> in one of
  our items.
*/
TBool TMenu::Match(
  TMenuItem * ItemFound,
  me_MemorySegment::TMemorySegment Entity
)
{
  TListNode * Cursor = List.Head;
  while (Cursor != 0)
  {
    TMenuItem * CurItem = (TMenuItem *) Cursor->Data;
    TMemorySegment ItemCommand = CurItem->Command.Get();
    if (ItemCommand.IsEqualTo(Entity))
    {
      ItemFound->Set(CurItem);
      return true;
    }
    Cursor = Cursor->Next;
  }
  return false;
}

/*
  2024-05-30
  2024-06-01
  2024-06-02
  2024-06-04
  2024-06-07
*/
