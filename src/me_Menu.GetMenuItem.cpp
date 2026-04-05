// Locate item in menu by command

/*
  Author: Martin Eden
  Last mod.: 2026-04-05
*/

#include <me_Menu.h>

#include <me_BaseTypes.h>

using namespace me_Menu;

/*
  Structure to hold search criteria and result

  Implementation-specific detail.
*/
struct TSearchAndCatch
{
  TAddressSegment LookingFor;
  TMenuItem * ItemFound;
};

/*
  [Internal] List handler: find entity

  If item says "It's me!", that's it.
*/
static void OnListVisit(
  TUint_2 NodeData,
  TUint_2 HandlerData
)
{
  TMenuItem * Item = (TMenuItem *) NodeData;
  TSearchAndCatch * State = (TSearchAndCatch *) HandlerData;

  if (Item->ItsMe(State->LookingFor))
    State->ItemFound = Item;
}

/*
  Find menu item by command
*/
TBool TMenu::GetMenuItem(
  TMenuItem * MenuItem,
  TAddressSegment Command
)
{
  TSearchAndCatch SearchState;

  SearchState.LookingFor = Command;
  SearchState.ItemFound = 0;

  List.Traverse(OnListVisit, (TUint_2) &SearchState);

  if (SearchState.ItemFound == 0)
    return false;

  *MenuItem = *SearchState.ItemFound;

  return true;
}

/*
  2024 # # #
  2025-09-04
  2026-04-05
*/
