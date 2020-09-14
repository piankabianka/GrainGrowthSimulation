//DATA
const data = require('./drawGrid.js');
//module.exports = require("bindings")("addon");
const addon = require('./build/Release/addon.node');

const stepButton=document.querySelector('#step');


stepButton.addEventListener('click', function(e){
    console.log(addon.hello());
})