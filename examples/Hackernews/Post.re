open Revery.Core;
open Revery.UI;

open Types;

module Styles = {
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
  let contentTitleContainer = Style.make(~flexDirection=LayoutTypes.Row, ());
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

include (
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
                        | Some(count) =>
                          " | " ++ string_of_int(count) ++ " comments"
                        }
                      );

                    let url =
                      switch (post.url) {
                      | Some(url) => " (" ++ url ++ ")"
                      | None => ""
                      };

                    <view style=Styles.view>
                      <text style=Styles.numberOfVotes>
                        {string_of_int(post.votes)}
                      </text>
                      <view style=Styles.contentContainer>
                        <view style=Styles.contentTitleContainer>
                          <text style=Styles.content> {post.title} </text>
                          <text style=Styles.contentTitleURL> url </text>
                        </view>
                        <text style=Styles.subcontent> subcontentText </text>
                      </view>
                    </view>;
                  },
                  ~children,
                )
              )
        );