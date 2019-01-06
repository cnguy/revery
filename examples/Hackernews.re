open Revery;
open Revery.Core;
open Revery.UI;
open Revery.UI.Components;

type user = {id: int};

type route =
  | Top
  | New
  | Show
  | Ask
  | Jobs
  | Comments(int)
  | Profile(user);

type post = {
  title: string,
  url: option(string),
  author: string,
  votes: int,
  time: int,
  numberOfComments: option(int),
};

module Themes = {
  type theme = {
    overallBackgroundColor: Color.t,
    postBackgroundColor: Color.t,
    postTextColor: Color.t,
  };

  let regular = () => {
    overallBackgroundColor: Color.hex("#f2f3f5"),
    postBackgroundColor: Colors.white,
    postTextColor: Colors.black,
  };

  let dark = () => {
    overallBackgroundColor: Colors.black,
    postBackgroundColor: Color.hex("#111111"),
    postTextColor: Colors.white,
  };

  let generalFontSize = 13;
  let currentTheme = ref(dark());
};

module Styles = {
  module Header = {
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

  module Post = {
    let view =
      Style.make(
        ~flexDirection=LayoutTypes.Row,
        ~backgroundColor=Themes.currentTheme.contents.postBackgroundColor,
        ~fontFamily="Roboto-Regular.ttf",
        ~marginBottom=1,
        (),
      );
    let numberOfVotes =
      Style.make(
        ~color=Colors.darkOrange,
        ~fontFamily="Roboto-Bold.ttf",
        ~fontSize=Themes.generalFontSize,
        ~margin=20,
        (),
      );
    let contentContainer = Style.make(~margin=10, ());
    let content =
      Style.make(
        ~backgroundColor=Themes.currentTheme.contents.postBackgroundColor,
        ~color=Themes.currentTheme.contents.postTextColor,
        ~fontFamily="Roboto-Regular.ttf",
        ~fontSize=Themes.generalFontSize,
        (),
      );
    let contentTitleContainer =
      Style.make(~flexDirection=LayoutTypes.Row, ());
    let contentTitleURL =
      Style.make(
        ~backgroundColor=Themes.currentTheme.contents.postBackgroundColor,
        ~color=Colors.lightSlateGray,
        ~fontFamily="Roboto-Regular.ttf",
        ~fontSize=Themes.generalFontSize,
        (),
      );
    let subcontent =
      Style.make(
        ~color=Colors.lightSlateGray,
        ~fontFamily="Roboto-Regular.ttf",
        ~fontSize=Themes.generalFontSize,
        (),
      );
  };
};

module API = {
  open Lwt.Infix;
  open Cohttp_lwt_unix;

  let baseURL = "https://hacker-news.firebaseio.com/v0";
  let top = baseURL ++ "/topstories.json";
  let new_ = baseURL ++ "/newstories.json";
  let show = baseURL ++ "/showstories.json";
  let ask = baseURL ++ "/askstories.json";
  let jobs = baseURL ++ "/jobstories.json";

  let item = (id: int) =>
    baseURL ++ "/item/" ++ string_of_int(id) ++ ".json";

  let toString = ((_resp, body)) => body |> Cohttp_lwt.Body.to_string;

  let fetchItemIds = url => Client.get(Uri.of_string(url)) >>= toString;
  let fetchItem = id => Client.get(Uri.of_string(item(id))) >>= toString;
};

module Decoder = {
  open Yojson.Basic;
  open Yojson.Basic.Util;

  let postId = json => json |> to_int;
  let postIds = json => json |> from_string |> to_list |> List.map(postId);

  let post = json =>
    json
    |> from_string
    |> (
      json => {
        title: json |> member("title") |> to_string,
        url: json |> member("url") |> to_string_option,
        author: json |> member("by") |> to_string,
        votes: json |> member("score") |> to_int,
        time: json |> member("time") |> to_int,
        numberOfComments: {
          let kids = json |> member("kids");
          switch (to_list(kids)) {
          | list => Some(List.length(list))
          | exception (Yojson.Basic.Util.Type_error(_, _)) => None
          };
        },
      }
    );
};

module Post = (
  val component((render, ~post: post, ~children, ()) =>
        render(
          () => {
            let subcontentText =
              "by "
              ++ post.author
              ++ " some time ago"
              ++ (
                switch (post.numberOfComments) {
                | None => ""
                | Some(count) => " | " ++ string_of_int(count) ++ " comments"
                }
              );

            let url =
              switch (post.url) {
              | Some(url) => " (" ++ url ++ ")"
              | None => ""
              };

            <view style=Styles.Post.view>
              <text style=Styles.Post.numberOfVotes>
                {string_of_int(post.votes)}
              </text>
              <view style=Styles.Post.contentContainer>
                <view style=Styles.Post.contentTitleContainer>
                  <text style=Styles.Post.content> {post.title} </text>
                  <text style=Styles.Post.contentTitleURL> url </text>
                </view>
                <text style=Styles.Post.subcontent> subcontentText </text>
              </view>
            </view>;
          },
          ~children,
        )
      )
);

module Header = (
  val component((render, ~setRoute, ~children, ()) =>
        render(
          () =>
            <view style=Styles.Header.container>
              <view style=Styles.Header.view>
                <Clickable onClick={() => setRoute(Top)}>
                  <text style=Styles.Header.item> "HN" </text>
                </Clickable>
                <Clickable onClick={() => setRoute(Top)}>
                  <text style=Styles.Header.item> "Top" </text>
                </Clickable>
                <Clickable onClick={() => setRoute(New)}>
                  <text style=Styles.Header.item> "New" </text>
                </Clickable>
                <Clickable onClick={() => setRoute(Show)}>
                  <text style=Styles.Header.item> "Show" </text>
                </Clickable>
                <Clickable onClick={() => setRoute(Ask)}>
                  <text style=Styles.Header.item> "Ask" </text>
                </Clickable>
                <Clickable onClick={_ => setRoute(Jobs)}>
                  <text style=Styles.Header.item> "Jobs" </text>
                </Clickable>
              </view>
              <view>
                <text style=Styles.Header.item>
                  "Built with ReasonML and Revery"
                </text>
              </view>
            </view>,
          ~children,
        )
      )
);

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

module Page = (
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

  UI.start(win, () => <Page />);
};

App.start(init);