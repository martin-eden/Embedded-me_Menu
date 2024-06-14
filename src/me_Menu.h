// WIP. Menu navigation

/*
  Author: Martin Eden
  Last mod.: 2024-06-04
*/

#pragma once

#include <me_List.h>
#include <me_BaseTypes.h>
#include <me_MemorySegment.h> // for definition of entity to match

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

    ~TMenu();

    // Add item
    TBool Add(TMenuItem * MenuItem);
    // Remove all items
    void Release();

    // Debug print
    void PrintWrappings();
    // Print menu list
    void Print();

    // Get entity from stdin and match it with our commands
    TBool GetSelection(TMenuItem * ItemSelected);
  };
}

/*
  2024-05-30
  2024-06-02
  2024-06-04
*/
