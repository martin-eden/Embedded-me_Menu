// Shell: print list of available commands

/*
  Author: Martin Eden
  Last mod.: 2024-10-27
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
  TUint_2 HandlerData __attribute__((unused))
)
{
  using me_Menu::TMenuItem;
  TMenuItem * Item = (TMenuItem *) Data;

  Console.Write(Item->Command);
  if (Item->Description.Size > 0)
  {
    Console.Write(" - ");
    Console.Write(Item->Description);
  }
  Console.EndLine();
}

/*
  Print menu
*/
void me_Menu::TMenu::Print()
{
  Console.Print("--");
  Console.Indent();
  List.Traverse(PrintListNode);
  Console.Unindent();
  Console.Print("==");
}

/*
  2024-06-21 Spliced to standalone file
  2024-10-05
  2024-10-18
  2024-10-27
*/
