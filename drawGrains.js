//DATA- connecting cpp script
const data = require('./drawGrid.js');
//module.exports = require("bindings")("addon");
const addon = require('./build/Release/addon.node');

//DATA- variables
const stepButton=document.querySelector('#step');

const context=data.getCanvas().c;

const grainsTable=[];


function drawGrains(){
    console.log(data.getCanvas());
    console.log(data.getCanvas().width);

    context.fillStyle='rgba(255,0,0,0.5)';
    context.fillRect(100,100, 100,100);
}

stepButton.addEventListener('click', function(e){
    console.log(data.getData());
    console.log(addon.hello());
    drawGrains();
})