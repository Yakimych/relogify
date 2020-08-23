type requestParams = {
  query: string,
  variables: Js.Json.t,
};

type observableType('a) = {
  .
  [@bs.meth]
  "subscribe":
    ReasonRelay.Observable.sink('a) => ReasonRelay.Observable.subscription,
};

type t('a) = {. [@bs.meth] "request": requestParams => observableType('a)};

[@bs.new] [@bs.module "subscriptions-transport-ws"]
external createSubscriptionClient: (string, 'a) => t('b) =
  "SubscriptionClient";

let createSubscriptionClient = createSubscriptionClient;
