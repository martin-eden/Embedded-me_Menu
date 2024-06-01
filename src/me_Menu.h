// WIP. Menu navigation

/*
  Author: Martin Eden
  Last mod.: 2024-05-30
*/

#pragma once

#include "Item/Item.h"

#include <me_List.h>

#include <me_BaseTypes.h>

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

    TBool AddItem(TMenuItem * MenuItem);

    void Print();
    void PrintWrappings();
    void GetSelection();
  };
}

