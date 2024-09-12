// Shell: print list of available commands

/*
  Author: Martin Eden
  Last mod.: 2024-09-12
*/

#include "me_Menu.h"

#include <stdio.h> // printf()

#include <me_BaseTypes.h>

using
  me_Menu::TMenu,
  me_Menu::TMenuItem;

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
  2024-06-21 Spliced to standalone file
*/
