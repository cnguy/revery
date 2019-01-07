open Revery;
open Revery.Core;
open Revery.UI;

open Types;

/*
   `Router` is a simple component that re-renders if the route changes.
   It does not handle history.
 */
module Router = (
  val component((render, ~defaultRoute: route, ~app, ~children, ()) =>
        render(
          () => {
            let (route, setRoute) = useState(defaultRoute);

            app(~route, ~setRoute);
          },
          ~children,
        )
      )
);

module Hackernews = (
  val component((render, ~children, ()) =>
        render(
          () =>
            <Router
              defaultRoute=Top
              app={(~route, ~setRoute) =>
                <view>
                  <Header setRoute />
                  {switch (route) {
                   | Comments(_id) => <view />
                   | Profile(_user) => <view />
                   | _ => <Listing route />
                   }}
                </view>
              }
            />,
          ~children,
        )
      )
);

let init = app => {
  let win =
    App.createWindow(
      app,
      "ReHackernews",
      ~createOptions={
        ...Window.defaultCreateOptions,
        backgroundColor: Themes.currentTheme.contents.overallBackgroundColor,
      },
    );

  UI.start(win, () => <Hackernews />);
};

App.start(init);