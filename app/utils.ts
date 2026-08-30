// Small helpers used by api.ts.

export function fmt(n) {
  return "$" + n.toFixed(2);
}

export function parseDate(s) {
  return new Date(s);
}

export function slug(s) {
  return s.toLowerCase().split(" ").join("-");
}

export function pick(obj, keys) {
  const out = {};
  keys.forEach((k) => (out[k] = obj[k]));
  return out;
}
