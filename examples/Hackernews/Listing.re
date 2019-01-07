open Revery.UI;

open Types;

include (
          val component((render, ~route: route, ~children, ()) =>
                render(
                  () => {
                    let posts =
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
                      |> Decoder.postIds
                      |> ListUtils.firstN(10)
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