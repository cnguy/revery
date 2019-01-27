open Lwt.Infix;
open Cohttp_lwt_unix;

let baseURL = "https://hacker-news.firebaseio.com/v0";
let top = baseURL ++ "/topstories.json";
let new_ = baseURL ++ "/newstories.json";
let show = baseURL ++ "/showstories.json";
let ask = baseURL ++ "/askstories.json";
let jobs = baseURL ++ "/jobstories.json";

let item = (id: int) => baseURL ++ "/item/" ++ string_of_int(id) ++ ".json";

let urlFromRoute = route =>
  Types.(
    switch (route) {
    | Top => top
    | New => new_
    | Show => show
    | Ask => ask
    | Jobs => jobs
    | _ => top
    }
  );

let toString = ((_resp, body)) => body |> Cohttp_lwt.Body.to_string;

let fetchItemIds = url => Client.get(Uri.of_string(url)) >>= toString;
let fetchItemIdsFromRoute = route => route |> urlFromRoute |> fetchItemIds;
let fetchItem = id => Client.get(Uri.of_string(item(id))) >>= toString;

let asyncToString = ((_resp, body)) => body |> Cohttp_async.Body.to_string;

let asyncRun = () => {
  Cohttp_async.(
    Async.(
      Client.get(Uri.of_string(top)) >>= asyncToString >>| (body => body)
    )
  );
};

let asyncRun2 = () => {
  Cohttp_async.(
    Async.(
      Client.get(Uri.of_string(top)) >>= asyncToString >>| (body => body)
    )
  );
};

let asyncFetchItemIds = _url => {
  (); /*  Command.async(~summary="", Command.Spec.(empty), (url => asyncRun(~url)))  |> Command.run;*/
    /*asyncRun(~url);*/
};

let asyncFetchItemIdsFromRoute = route =>
  route |> urlFromRoute |> asyncFetchItemIds;