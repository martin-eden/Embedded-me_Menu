// Shell: print list of available commands

/*
  Author: Martin Eden
  Last mod.: 2024-11-30
*/

#include "me_Menu.h"

using namespace me_Menu;

#include <me_BaseTypes.h>
#include <me_Console.h>

/*
  List handler: print item
*/
void PrintListNode(
  TUint_2 Data,
  TUint_2 HandlerData __attribute__((unused))
)
{
  using
    me_Menu::CommandHandler::TCommandHandler;

  TCommandHandler * Item = (TCommandHandler *) Data;

  Console.Print(Item->GetCommand());
}

/*
  Print menu
*/
void me_Menu::TMenu::Print()
{
  Console.Print("(");

  Console.Indent();

  List.Traverse(PrintListNode);

  Console.Unindent();

  Console.Print(")");
}

/*
  2024-06 #
  2024-10 ###
  2024-11-29
  2024-11-30
*/
