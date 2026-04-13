// Menu's utility functions

/*
  Author: Martin Eden
  Last mod.: 2026-04-13
*/

#include <me_Menu.h>

#include <me_BaseTypes.h>
#include <me_StoredCall.h>
#include <me_WorkmemTools.h>

using namespace me_Menu;

/*
  [Handy] Return item structure from arguments

  No heap allocations here.
*/
TMenuItem Freetown::ToItem(
  TAddressSegment Command,
  TAddressSegment Description,
  me_StoredCall::TStoredCall Handler
)
{
  return
    {
      .Command = Command,
      .Description = Description,
      .Handler = Handler,
    };
}

/*
  [Handy] Create item from list of values

  Memory allocated here depends of length of ASCIIZs.
*/
TMenuItem Freetown::ToItem(
  const TAsciiz Command,
  const TAsciiz Description,
  TCallback Method,
  TAddress Instance
)
{
  using
    me_WorkmemTools::Reserve,
    me_WorkmemTools::CopyMemTo,
    me_WorkmemTools::Release,
    me_StoredCall::Freetown::ToStoredCall;

  TMenuItem Result; // I hope it is zeroed, we can return it early

  /*
    Allocate memory and copy ASCIIZ. But first we need to describe
    them as memory segments.
  */
  TAddressSegment CommandCopy;
  TAddressSegment DescriptionCopy;
  {
    TAddressSegment CommandOrig =
      me_WorkmemTools::FromAsciiz(Command);

    TAddressSegment DescriptionOrig =
      me_WorkmemTools::FromAsciiz(Description);

    if (!Reserve(&CommandCopy, CommandOrig.Size))
      return Result;

    CopyMemTo(CommandCopy, CommandOrig);

    if (!Reserve(&DescriptionCopy, DescriptionOrig.Size))
    {
      Release(&CommandCopy);

      return Result;
    }

    CopyMemTo(DescriptionCopy, DescriptionOrig);
  }

  // Using existing shortcut. Because someone should use it
  return
    ToItem(
      CommandCopy,
      DescriptionCopy,
      ToStoredCall(Method, Instance)
    );
}

/*
  Release memory from:
    * menu item strings (variable)
    * menu item structure (12 bytes)
*/
void Freetown::KillItem(
  TMenuItem * Item
)
{
  TAddressSegment ItemSeg = M_AsAddrSeg(*Item);

  // Release item strings
  me_WorkmemTools::Release(&Item->Command);
  me_WorkmemTools::Release(&Item->Description);

  // Release item structure (12 bytes)
  me_WorkmemTools::Release(&ItemSeg);
}

/*
  2024 # # # # #
  2026-04-05
*/
