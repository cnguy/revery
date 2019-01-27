open Revery;
open Revery.Core;
open Revery.UI;

open Types;

module Hackernews = {
  let component = React.component("Hackernews_Hackernews");

  let make = () =>
    component(slots => {
      let (route, setRoute, _slots: React.Hooks.empty) =
        React.Hooks.state(Top, slots);
      <View>
        <Header setRoute />
        {switch (route) {
         | Comments(_id) => <View />
         | Profile(_user) => <View />
         | _ => <Listing route />
         }}
      </View>;
      /*
       <Router
         defaultRoute=Top
         view={(~route: route, ~setRoute: route => unit) =>
           <View>
             <Header setRoute />
             {switch (route) {
              | Comments(_id) => <View />
              | Profile(_user) => <View />
              | _ => <Listing route />
              }}
           </View>
         }
       />;*/
    });

  let createElement = (~children as _, ()) => React.element(make());
};

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