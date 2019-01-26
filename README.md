This is a simple fork to show a basic Hackernews implementation. Not meant to be merged, I just needed the build setup.

Hackernews implementation: https://github.com/cnguy/revery/tree/hackernews/examples/Hackernews

Implemented so far:
- [x] A basic router module similar to ReasonReact's [ReRoute](https://github.com/callstackincubator/reroute) is implemented
    - Note, it doesn't handle history. It's just a simple way to show / hide components based on state.
- [x] Show 10 posts depending on page
    - [ ] Pagination
- [ ] User profile
- [ ] Comments
    - This one is probably tough and really bad bandwidth-wise.
- [ ] Scrollable view (this will wait on `revery`)

## Light theme

![Light theme](https://i.imgur.com/PhdtgTs.png)

## Dark theme

![Dark theme](https://i.imgur.com/EMim05Y.png)
