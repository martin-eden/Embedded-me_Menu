// Communication channel commands handler

/*
  Author: Martin Eden
  Last mod.: 2024-06-20
*/

#include "me_Menu.h"

#include <stdio.h> // printf()

#include <me_List.h>
#include <me_MemorySegment.h> // (Reserve/Release)Chunk()
#include <me_ManagedMemory.h> // more modern way of managing memseg
#include <me_SerialTokenizer.h> // GetEntity()
#include <me_BaseTypes.h>

using
  me_Menu::TMenu,
  me_Menu::TMenuItem,
  me_MemorySegment::TMemorySegment,
  me_ManagedMemory::TManagedMemory,
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

  if (!List.Add(ItemMem.Start.Addr))
  {
    // No memory for new list node
    Item->Release();
    ItemMem.Release();
    return false;
  }
  return true;
}

/*
  List handler: release item memory

  We are releasing

    1. Data of menu item
    2. Structure of menu item
*/
void KillMenuItem(
  TUint_2 Data,
  TUint_2 HandlerData __attribute__((unused))
)
{
  TMenuItem * Item = (TMenuItem *) Data;

  Item->Release();

  TMemorySegment ItemMem;
  ItemMem.Start.Addr = Data;
  ItemMem.Size = sizeof(TMenuItem);
  ItemMem.Release();
}

/*
  Release memory of list items and the list
*/
void TMenu::Release()
{
  List.Traverse(KillMenuItem);
  List.Release();
}

/*
  Release() wrapper for builtin command

  Release() will empty list and empty list is exit condition
  in Run() loop.
*/
void Release_wrap(TUint_2 Instance)
{
  TMenu * Menu = (TMenu *) Instance;
  Menu->Release();
}

/*
  Loop of getting data and executing corresponding item
  for non-empty list.

  Yeah, there should be exit condition if I want menu trees.
*/
void TMenu::Run()
{
  while (!List.IsEmpty())
  {
    TMenuItem Item;

    while(!GetSelection(&Item));

    Item.Execute();
  }
}

/*
  List handler: print item
*/
void PrintListNode(
  TUint_2 Data,
  TUint_2 HandlerData __attribute__((unused))
)
{
  TMenuItem * Item = (TMenuItem *) Data;

  Item->Command.Print();
  printf(" - ");
  Item->Description.Print();
  printf("\n");
}

/*
  Print menu
*/
void TMenu::Print()
{
  printf("--\n");
  List.Traverse(PrintListNode);
  printf("==\n");
}

/*
  Print() wrapper for built-in command
*/
void Print_wrap(TUint_2 Instance)
{
  TMenu * Menu = (TMenu *) Instance;
  Menu->Print();
}

/*
  Add our internal commands:

    ? - List commands
    ^ - Exit
*/
TBool TMenu::AddBuiltinCommands()
{
  TMenuItem Item;

  Item.Command.Set("?");
  Item.Description.Set("List commands");
  Item.Method.Set((TUint_2) this, (TUint_2) &Print_wrap);
  if (!Add(&Item))
    return false;

  Item.Command.Set("^");
  Item.Description.Set("Exit");
  Item.Method.Set((TUint_2) this, (TUint_2) &Release_wrap);
  if (!Add(&Item))
    return false;

  return true;
}

struct TLookedAndFound
{
  TMemorySegment LookingFor;
  TMenuItem * ItemFound;
};

/*
  List handler: find entity

  We are matching string in <State.LookingFor> to <.Command> in one of
  our items.
*/
void Match(
  TUint_2 NodeData,
  TUint_2 HandlerData
)
{
  TMenuItem * MenuItem = (TMenuItem *) NodeData;
  TLookedAndFound * State = (TLookedAndFound *) HandlerData;

  if (MenuItem->Command.Get().IsEqualTo(State->LookingFor))
    State->ItemFound = MenuItem;
}

/*
  Get command from serial and match it to our list

  If we found menu item in our list with same <.Command>, copy
  that menu item to provided argument. Yes, we are returning copy.
*/
TBool TMenu::GetSelection(TMenuItem * ItemSelected)
{
  // Part one: get string
  TManagedMemory String;
  {
    const TUint_2 InputBufferSize = 32;
    TChar Buffer[InputBufferSize];

    TMemorySegment BufferMem;
    BufferMem.Start.Addr = (TUint_2) &Buffer;
    BufferMem.Size = sizeof(Buffer);

    me_SerialTokenizer::TCapturedEntity Entity;

    me_SerialTokenizer::WaitEntity(&Entity, BufferMem);

    if (Entity.IsTrimmed)
    {
      // Entity was too long for our input buffer
      return false;
    }

    String.Set(Entity.Segment);
  }

  // Part two: search by this string
  TLookedAndFound SearchState;
  {
    SearchState.LookingFor = String.Get();
    SearchState.ItemFound = 0;

    List.Traverse(Match, (TUint_2) &SearchState);
  }

  // Part three: fulfill contract
  {
    if (SearchState.ItemFound != 0)
    {
      ItemSelected->Set(SearchState.ItemFound);
      return true;
    }
    return false;
  }
}

/*
  2024-05-30
  2024-06-01
  2024-06-02
  2024-06-04
  2024-06-07
  2024-06-12
  2024-06-13
  2024-06-14
  2024-06-20
*/
