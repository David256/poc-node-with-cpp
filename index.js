const addon = require("./build/Release/addon");

console.log(addon.testAddon());

const result = addon.processArrays(
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
  [3, 3, 3, 3, 3, 3, 3, 3, 3, 3],
  0.4
);

console.info("results:", result);
