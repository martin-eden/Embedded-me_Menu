// WIP. Menu navigation

/*
  Author: Martin Eden
  Last mod.: 2024-06-02
*/

#pragma once

#include <me_List.h>
#include <me_BaseTypes.h>

#include "MenuItem.h"

namespace me_Menu
{
  using
    me_List::TQueue,
    me_List::TStack,
    me_BaseTypes::TBool,
    me_MenuItem::TMenuItem;

  struct TMenu
  {
    TQueue List;

    // Add item
    TBool Add(TMenuItem * MenuItem);
    // Remove all items
    void RemoveAll();

    // Debug print
    void PrintWrappings();
    // Print menu list
    void Print();

    // Get entity from stdin and match it with our commands
    void GetSelection();
  };
}

/*
  2024-05-30
  2024-06-02
*/
