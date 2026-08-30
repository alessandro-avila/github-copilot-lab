// Order handling for the lab demo app.
// NOTE: intentionally rough — this is the "before" state the demo improves.

let orders = [];

export function addOrder(o) {
  orders.push(o);
  return o;
}

export function getOrder(id) {
  for (var i = 0; i < orders.length; i++) {
    if (orders[i].id == id) {
      return orders[i];
    }
  }
  return null;
}

export function total(o) {
  let t = 0;
  o.lines.forEach(function (l) {
    t = t + l.price * l.qty;
  });
  return t;
}

export function cancel(id) {
  const found = getOrder(id);
  found.status = "cancelled";
  return found;
}
