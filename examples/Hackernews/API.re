open Lwt.Infix;

open Cohttp_lwt_unix;

let baseURL = "https://hacker-news.firebaseio.com/v0";
let top = baseURL ++ "/topstories.json";
let new_ = baseURL ++ "/newstories.json";
let show = baseURL ++ "/showstories.json";
let ask = baseURL ++ "/askstories.json";
let jobs = baseURL ++ "/jobstories.json";

let item = (id: int) => baseURL ++ "/item/" ++ string_of_int(id) ++ ".json";

let toString = ((_resp, body)) => body |> Cohttp_lwt.Body.to_string;

let fetchItemIds = url => Client.get(Uri.of_string(url)) >>= toString;
let fetchItem = id => Client.get(Uri.of_string(item(id))) >>= toString;