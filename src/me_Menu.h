// WIP. Menu navigation

/*
  Author: Martin Eden
  Last mod.: 2024-05-30
*/

#pragma once

#include "MenuItem/Interface.h"

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
    TStack List;

    TBool AddItem(TMenuItem * MenuItem);

    void Print();
    void PrintWrappings();
    void GetSelection();
  };
}

