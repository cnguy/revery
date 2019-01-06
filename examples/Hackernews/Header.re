open Revery.Core;
open Revery.UI;
open Revery.UI.Components;

open Types;

module Styles = {
  let container =
    Style.make(
      ~flexDirection=LayoutTypes.Row,
      ~justifyContent=LayoutTypes.JustifySpaceBetween,
      ~backgroundColor=Colors.darkOrange,
      (),
    );
  let view = Style.make(~flexDirection=LayoutTypes.Row, ());
  let item =
    Style.make(
      ~color=Colors.white,
      ~fontFamily="Roboto-Regular.ttf",
      ~fontSize=Themes.generalFontSize,
      ~margin=12,
      (),
    );
};

include (
          val component((render, ~setRoute, ~children, ()) =>
                render(
                  () =>
                    <view style=Styles.container>
                      <view style=Styles.view>
                        <Clickable onClick={() => setRoute(Top)}>
                          <text style=Styles.item> "HN" </text>
                        </Clickable>
                        <Clickable onClick={() => setRoute(Top)}>
                          <text style=Styles.item> "Top" </text>
                        </Clickable>
                        <Clickable onClick={() => setRoute(New)}>
                          <text style=Styles.item> "New" </text>
                        </Clickable>
                        <Clickable onClick={() => setRoute(Show)}>
                          <text style=Styles.item> "Show" </text>
                        </Clickable>
                        <Clickable onClick={() => setRoute(Ask)}>
                          <text style=Styles.item> "Ask" </text>
                        </Clickable>
                        <Clickable onClick={_ => setRoute(Jobs)}>
                          <text style=Styles.item> "Jobs" </text>
                        </Clickable>
                      </view>
                      <view>
                        <text style=Styles.item>
                          "Built with ReasonML and Revery"
                        </text>
                      </view>
                    </view>,
                  ~children,
                )
              )
        );