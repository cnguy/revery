open Revery.UI;

open Types;

/*
 let doNow = () => {
   open Cohttp_async;
   open Async;
   Command.async(
     ~summary:"Test for async http request",
     Command.Spec.(empty),
     () => (Top |> API.asyncFetchItemIdsFromRoute)
   )
   |> Command.run;
 };*/

/*
 let doNow = cb => {
   open Async;
   open Core_kernel;
   let run = () =>
     Async.(
       API.asyncRun2()
       >>= (
         itemIds => {
           let vals: list(int) = itemIds |> Decoder.postIds;
           cb(vals);
           Deferred.return(vals);
         }
       )
     );
   ignore(run());
   never_returns(Scheduler.go());
 };*/

include (
          val component((render, ~route: route, ~children, ()) =>
                render(
                  () => {
                    /*
                     let _ =
                       doNow(vals =>
                         vals |> ListUtils.firstN(1) |> List.hd |> print_int
                       );*/
                    let posts =
                      route
                      |> API.fetchItemIdsFromRoute
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