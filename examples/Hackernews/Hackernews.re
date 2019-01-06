open Revery;
open Revery.Core;
open Revery.UI;

open Types;

module Router = (
  val component((render, ~route, ~children, ()) =>
        render(
          () =>
            switch (route) {
            | Comments(_id) => <text> "Comments" </text>
            | Profile(_user) => <text> "Profile" </text>
            | _ =>
              let newList =
                (
                  switch (route) {
                  | Top => API.top
                  | New => API.new_
                  | Show => API.show
                  | Ask => API.ask
                  | Jobs => API.jobs
                  | _ => API.top
                  }
                )
                |> API.fetchItemIds
                |> Lwt_main.run
                |> Decoder.postIds;
              let finalList =
                List.[
                  nth(newList, 0),
                  nth(newList, 1),
                  nth(newList, 2),
                  nth(newList, 3),
                  nth(newList, 4),
                ];
              let posts =
                finalList
                |> List.map(id =>
                     id |> API.fetchItem |> Lwt_main.run |> Decoder.post
                   );

              let postsToElements = posts =>
                posts |> List.map(post => <Post post />);

              <view> ...{postsToElements(posts)} </view>;
            },
          ~children,
        )
      )
);

module Hackernews = (
  val component((render, ~children, ()) =>
        render(
          () => {
            let (route, setRoute) = useState(Top);

            <view> <Header setRoute /> <Router route /> </view>;
          },
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