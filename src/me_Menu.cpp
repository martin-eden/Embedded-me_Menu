// Serial commands handler

/*
  Author: Martin Eden
  Last mod.: 2024-12-11
*/

#include "me_Menu.h"

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>
#include <me_List.h>
#include <me_SerialTokenizer.h>
#include <me_Console.h>

using namespace me_Menu;

using
  me_MemorySegment::TMemorySegment,
  me_Menu::CommandHandler::TCommandHandler;

/*
  Structure to hold search criteria and result

  Implementation-specific detail.
*/
struct TSearchAndCatch
{
  TMemorySegment LookingFor;
  TCommandHandler * ItemFound;
};

// ( TMenu

/*
  Release memory at death
*/
TMenu::~TMenu()
{
  Release();
}

/*
  Add menu item to menu
*/
TBool TMenu::AddItem(
  TCommandHandler * MenuItem
)
{
  TAddress ItemAddr = (TAddress) MenuItem;

  if (!List.Add(ItemAddr))
    return false;

  return true;
}

/*
  Wait until we got text word from serial
*/
void TMenu::WaitCommand(
  TMemorySegment * Name,
  TMemorySegment NameBuffer
)
{
  using
    me_SerialTokenizer::TSerialTokenizer;

  TSerialTokenizer Tokenizer;

  Tokenizer.WaitEntity(Name, NameBuffer);
}

/*
  List handler: find entity

  If item's command is equal to what we got from serial then we found it.
*/
void OnListVisit(
  TAddress NodeData,
  TAddress HandlerData
)
{
  using
    me_MemorySegment::Freetown::AreEqual;

  TCommandHandler * Item = (TCommandHandler *) NodeData;

  TSearchAndCatch * State = (TSearchAndCatch *) HandlerData;

  if (AreEqual(Item->GetCommand(), State->LookingFor))
    State->ItemFound = Item;
}

/*
  Find item in our list by command name
*/
TBool TMenu::FindItem(
  TCommandHandler * Item,
  TMemorySegment Name
)
{
  TSearchAndCatch SearchState;

  {
    SearchState.LookingFor = Name;
    SearchState.ItemFound = 0;

    List.Traverse(OnListVisit, (TAddress) &SearchState);
  }

  if (SearchState.ItemFound != 0)
  {
    *Item = *SearchState.ItemFound;

    return true;
  }

  return false;
}

/*
  List handler: print item
*/
void PrintListNode(
  TAddress Data,
  TAddress HandlerData __attribute__((unused))
)
{
  TCommandHandler * Item = (TCommandHandler *) Data;

  Console.Write(Item->GetCommand());
  Console.Write(" ");
}

/*
  Print all available commands
*/
void TMenu::PrintCommands()
{
  Console.Write("( ");

  List.Traverse(PrintListNode);

  Console.Write(")");
}

/*
  Loop of getting data and executing corresponding item for non-empty
  list.

  Empty list is the exit condition.
*/
void TMenu::Run()
{
  using
    me_MemorySegment::Freetown::Reserve,
    me_MemorySegment::Freetown::Release;

  // Buffer for command name
  TMemorySegment NameBuffer;
  // Command name. Is inside of buffer.
  TMemorySegment Name;
  TCommandHandler Item;
  TBool IsOk;

  // Allocate command name buffer
  {
    const TUint_1 MaxNameLen = 32;

    IsOk = Reserve(&NameBuffer, MaxNameLen);

    if (!IsOk)
    {
      // No memory for command name buffer
      return;
    }
  }

  while (true)
  {
    if (List.IsEmpty())
      break;

    WaitCommand(&Name, NameBuffer);

    if (FindItem(&Item, Name))
      Item.RunHandler();
  }

  // Release command name buffer
  Release(&NameBuffer);
}

/*
  List handler: release item memory
*/
void KillItem_Handler(
  TAddress Data,
  TAddress Instance __attribute__((unused))
)
{
  using
    me_Menu::CommandHandler::Destroy;

  TCommandHandler * MenuItem = (TCommandHandler *) Data;

  Destroy(MenuItem);
}

/*
  Release memory of list items and the list
*/
void TMenu::Release()
{
  List.Traverse(KillItem_Handler);
  List.Release();
}

// ) TMenu

/*
  Create and add item from explicit list of values
*/
TBool me_Menu::AddNewItem(
  TMenu * Menu,
  TAsciiz Command,
  TMethod Handler,
  TAddress Instance
)
{
  using
    me_Menu::CommandHandler::Create,
    me_Menu::CommandHandler::Destroy;

  TCommandHandler * Item;
  TBool IsOk;

  IsOk = Create(&Item, Command, Handler, Instance);

  if (!IsOk)
    return false;

  IsOk = Menu->AddItem(Item);

  if (!IsOk)
  {
    Destroy(Item);
    return false;
  }

  return true;
}

/*
  "list" command handler
*/
void ListCommand_Handler(
  TAddress Data __attribute__((unused)),
  TAddress Instance
)
{
  TMenu * Menu = (TMenu *) Instance;

  Menu->PrintCommands();
}

/*
  Add "list" command

  "?" - print all available commands
*/
TBool me_Menu::AddListCommand(
  TMenu * Menu
)
{
  using
    me_Menu::AddNewItem;

  return AddNewItem(Menu, "?", ListCommand_Handler, (TAddress) Menu);
}

/*
  "exit" command handler
*/
void ExitCommand_Handler(
  TAddress Data __attribute__((unused)),
  TAddress Instance
)
{
  TMenu * Menu = (TMenu *) Instance;

  Menu->Release();
}

/*
  Add "exit" command

  "^" - destroy menu items (and so break from "Run()" loop)
*/
TBool me_Menu::AddExitCommand(
  TMenu * Menu
)
{
  using
    me_Menu::AddNewItem;

  return AddNewItem(Menu, "^", ExitCommand_Handler, (TAddress) Menu);
}

/*
  Add "list" and "exit" commands
*/
TBool me_Menu::AddBuiltinCommands(
  TMenu * Menu
)
{
  using
    me_Menu::AddListCommand,
    me_Menu::AddExitCommand;

  return (AddListCommand(Menu) && AddExitCommand(Menu));
}


/*
  2024-05 #
  2024-06 #########
  2024-07 #
  2024-10 ###
  2024-11 ##
  2024-12-11
*/
