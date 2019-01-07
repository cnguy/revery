open Revery.UI;

open Types;

include (
          val component((render, ~route: route, ~children, ()) =>
                render(
                  () => {
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