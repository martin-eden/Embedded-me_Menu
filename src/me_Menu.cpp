// Text menu navigation via Serial

/*
  Author: Martin Eden
  Last mod.: 2024-06-12
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

  Release memory at death.
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
  TMemorySegment ItemMem;

  if (!ItemMem.Reserve(sizeof(TMenuItem)))
  {
    // No memory for new menu item structure
    return false;
  }
  TMenuItem * Item = (TMenuItem *) ItemMem.Start.Addr;

  if (!Item->Set(OuterMenuItem))
  {
    // No memory to copy data (command and description)
    ItemMem.Release();
    return false;
  }

  TMemorySegment NodeMem;

  if (!NodeMem.Reserve(sizeof(TListNode)))
  {
    // No memory for new list node
    Item->Release();
    ItemMem.Release();
    return false;
  }

  TListNode * ListNode = (TListNode *) NodeMem.Start.Addr;

  ListNode->Data = (TUint_2) Item;

  List.Add(ListNode);

  return true;
}

/*
  Release memory of menu item

  We are releasing

    1. Data of menu item
    2. Structure of menu item

  List node structure is released in KillList().
*/
TBool KillMenuItem(TUint_2 Data)
{
  using me_Menu::TMenuItem;

  TMenuItem * Item = (TMenuItem *) Data;

  Item->Release();

  TMemorySegment ItemMem;
  ItemMem.Start.Addr = Data;
  ItemMem.Size = sizeof(TMenuItem);
  ItemMem.Release();

  return true;
}

/*
  Release memory of list items and the list
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
TBool PrintListNode(TUint_2 Data)
{
  using me_Menu::TMenuItem;

  TMenuItem * Item = (TMenuItem *) Data;

  Item->Print();

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
  Find entity in list

  We are matching string in <Entity> to <.Command> in one of
  our items.
*/
TBool TMenu::Match(
  TMenuItem * ItemFound,
  TMemorySegment Entity
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
  Get command from serial and match it to our list
*/
TBool TMenu::GetSelection(TMenuItem * ItemSelected)
{
  const TUint_2 InputBufferSize = 16;
  TChar Buffer[InputBufferSize];

  TMemorySegment BufferMem;
  BufferMem.Start.Addr = (TUint_2) &Buffer;
  BufferMem.Size = sizeof(Buffer);

  using namespace me_SerialTokenizer;

  printf(": ");

  TCapturedEntity Entity;

  while (!GetEntity(&Entity, BufferMem));

  printf("\n");

  if (Entity.IsTrimmed)
  {
    printf("Too long.\n");
    return false;
  }

  return Match(ItemSelected, Entity.Segment);
}

/*
  2024-05-30
  2024-06-01
  2024-06-02
  2024-06-04
  2024-06-07
  2024-06-12
*/
