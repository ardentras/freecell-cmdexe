# FreeCell (for cmd.exe)

(c) 2017 Shaun Rasmusen

---

## Description

This is a gimmicky version of the classic card game FreeCell that runs within
the Windows `cmd.exe` runtime. It includes a full UI interface with click
interactions for gameplay.

_Originally written in 2017 by Shaun Rasmusen for a Data Structures lab._

---

## How to Run

The project spec for this program was created in Visual Studio 2015, but has
been confirmed to be compatible with at least Visual Studio Community 2019.

To ensure proper rendering of the cards' ASCII glyphs, the command prompt must
be configured to run in `Legacy Mode` or else the suits and colors will render
improperly due to a mismatch of the loaded character page and the way that the
modern command prompt handles color settings.

If the click actions are not working, also ensure that you are allowed to make
selections within the command prompt window.

---

## How to Play

The game is played identically to the standard rules of FreeCell. To select a
card, click the card once. Cards are highlighted by inverting their colors.

To deselect a card, click anywhere in game field that is not the currently
selected card.

To automatically send a card to the foundations in top right corner, double 
click the card. If there is not a valid spot in the foundations for that card,
nothing will happen. Once a card has been placed on a foundation, it cannot be
brought back in to play.

To move a stack of cards, select the top most card you would like and it will
auto select all cards below it if the run is valid. The maximum size of a stack
that can be moved is limited to movement logic of FreeCell, i.e. a stack maximum
of 5 can be moved if no cascades are free and all four open cells are free.

To start a new game, select the replay button in the bottom right of the screen.
