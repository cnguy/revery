open Revery.UI;

let component = React.component("Hackernews_Listing");

 let doNow = () => {
   open Async;
   open Core_kernel;
   let run = () =>
     Async.(
       API.asyncRun2()
       >>= (
         itemIds => {
           let vals: list(int) = itemIds |> Decoder.postIds;
           print_int(vals |> List.length);
           Deferred.return();
         }
       )
     );
     ignore(run());
     never_returns(Scheduler.go());
 };

let make = (~route, ()) =>
  component((_slots: React.Hooks.empty) => {
    let _ = () => route;
    let _ = doNow();
    let posts = [];
    /*
      route
      |> API.fetchItemIdsFromRoute
      |> Lwt_main.run
      |> Decoder.postIds
      |> ListUtils.firstN(10)
      |> List.map(id => id |> API.fetchItem |> Lwt_main.run |> Decoder.post);
*/
    let postsToElements = posts => posts |> List.map(post => <Post post />);

    <View> ...{postsToElements(posts)} </View>;
  });

let createElement = (~children as _, ~route, ()) =>
  React.element(make(~route, ()));