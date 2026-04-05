// Shell: print list of available commands

/*
  Author: Martin Eden
  Last mod.: 2026-04-05
*/

#include <me_Menu.h>

using namespace me_Menu;

#include <me_BaseTypes.h>
#include <me_Console.h>

/*
  List handler: print item
*/
void PrintListNode(
  TUint_2 Data,
  TUint_2 HandlerData [[gnu::unused]]
)
{
  using me_Menu::TMenuItem;
  TMenuItem * Item = (TMenuItem *) Data;

  Console.Write(Item->Command);
  if (Item->Description.Size > 0)
  {
    Console.Write("-");
    Console.Write(Item->Description);
  }
  Console.EndLine();
}

/*
  Print menu
*/
void me_Menu::TMenu::Print()
{
  List.Traverse(PrintListNode);
}

/*
  2024 # # # #
*/
